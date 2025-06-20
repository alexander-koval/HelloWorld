#ifndef SHARER_PRINTF_HPP
#define SHARER_PRINTF_HPP

#include <Grafit/Graphics/GL/glad.h>

// MIT License
//
// Copyright(c) 2017 Pauli Kemppinen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <string>
#include <vector>

// creates a shader storage buffer object to be used with the print functionality.
// any SSBO can be used, this is just for convenience and does nothing special.
inline GLuint createPrintBuffer(unsigned size = 16 * 1024 * 1024) {
        GLuint printBuffer;
        glCreateBuffers(1, &printBuffer);
        glNamedBufferData(printBuffer, size * sizeof(unsigned), nullptr, GL_STREAM_READ);
        return printBuffer;
}

// deletes the given buffer
inline void deletePrintBuffer(GLuint printBuffer) {
        glDeleteBuffers(1, &printBuffer);
}

// binds a print buffer to the current program; call anywhere between glUseProgram and the draw/dispatch call
inline void bindPrintBuffer(GLuint program, GLuint printBuffer) {
        // reset the buffer; only first value relevant (writing position / size of output), rest is filled up to the index this states
        unsigned beginIterator = 1u;
        glNamedBufferSubData(printBuffer, 0, sizeof(unsigned), &beginIterator);

        // bind to whatever slot we happened to get
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, glGetProgramResourceIndex(program, GL_SHADER_STORAGE_BLOCK, "printBuffer"), printBuffer);
}

// fetches the printed buffer from VRAM and turns it into an std::string
inline std::string getPrintBufferString(GLuint printBuffer) {

        // get the size of what we want to read and the size of the print buffer
        unsigned printedSize; int bufferSize;
        glGetNamedBufferSubData(printBuffer, 0, sizeof(unsigned), &printedSize);
        glGetNamedBufferParameteriv(printBuffer, GL_BUFFER_SIZE, &bufferSize);
        bufferSize /= sizeof(unsigned);

        // make sure we're not reading past the maximum size
        if (printedSize > bufferSize)
                printedSize = bufferSize;

        // this vector will hold the CPU copy of the print buffer
        std::vector<unsigned> printfData(printedSize + 1);
        printfData[0] = printedSize;

        // get the rest of the buffer data (the actual text)
        glGetNamedBufferSubData(printBuffer, sizeof(unsigned), GLsizei((printfData.size()-1) * sizeof(unsigned)), printfData.data()+1);

        // the final string we're going to build
        std::string result;

        // to hold the temporary results of formatting
        char intermediate[1024];

        // this loop parses the formatting of the result
        for (size_t i = 1; i < printfData[0]; ++i) {
                // % indicates the beginning of a formatted input
                if (printfData[i] == '%')
                        // if followed by another %, we're actually supposed to print '%'
                        if (printfData[i + 1] == '%') {
                                result += "%";
                                i++;
                        }
                        // otherwise we'll be printing numbers
                        else {
                                // first parse out the possible vector size
                                int vecSize = 1;
                                std::string format;
                                while (std::string(1, printfData[i]).find_first_of("eEfFgGdiuoxXaA") == std::string::npos) {
                                        if (printfData[i] == '^') {
                                                vecSize = printfData[i + 1] - '0';
                                                i += 2;
                                        }
                                        else {
                                                format = format + std::string(1, printfData[i]);
                                                i++;
                                        }
                                }
                                format += printfData[i];

                                // determine whether we'll have to do type conversion
                                bool isFloatType = std::string(1, printfData[i]).find_first_of("diuoxX") == std::string::npos;

                                // print to a temporary buffer, add result to string (for vectors add parentheses and commas as in "(a, b, c)")
                                if (vecSize > 1) result += "(";

                                for (int j = 0; j < vecSize; ++j) {
                                        i++;
                                        if (isFloatType)
                                                snprintf(intermediate, 1024, format.c_str(), *((float*)&printfData[i]));
                                        else
                                                snprintf(intermediate, 1024, format.c_str(), printfData[i]);
                                        result += std::string(intermediate);
                                        if (vecSize > 1 && j < vecSize - 1) result += ", ";
                                }

                                if (vecSize > 1) result += ")";
                        }
                else // otherwise it's a single character, just add it to the result
                        result += std::string(1, printfData[i]);
        }
        // ... and we're done.
        return result;
}

#include <cctype>

// helper function that finds a function call
inline size_t findCall(const std::string& source, const std::string& function) {
        // search for any occurrence of function name
        size_t tentative = source.find(function);
        if (tentative == std::string::npos)
                return std::string::npos;

        // see if it's inside a comment
        bool commentLong = false;
        bool commentRow = false;
        for (size_t i = 0; i < tentative; ++i) {
                if (source[i] == '/' && source[i + 1] == '*') commentLong = true;
                if (source[i] == '*' && source[i + 1] == '/') commentLong = false;
                if (source[i] == '/' && source[i + 1] == '/') commentRow = true;
                if (source[i] == '\n') commentRow = false;
        }
        size_t tentativeEnd = tentative + function.length();
        // if the tentative instance is not good...
        if (commentRow || commentLong || // comment
                (tentative > 0 && !std::isspace(source[tentative - 1])) || // is a part of a longer string
                tentativeEnd >= source.length() || // is the end of the file
                !(std::isspace(source[tentativeEnd]) || source[tentativeEnd] == '(')) { // is a part of a longer string
                // ... find the next one
                size_t result = findCall(source.substr(tentative + 1), function);
                if (result == std::string::npos)
                        return std::string::npos;
                else
                        return tentative + 1 + result;
        }
        else // otherwise return it
                return tentative;
}

// a preprocessor for shader source
inline std::string addPrintToSource(std::string source) {

        // get rid of comments beforehand
        std::string commentedSource = "";
        std::swap(source, commentedSource);

        bool commentLong = false;
        bool commentRow = false;
        bool inString = false;
        for (size_t i = 0; i < commentedSource.length(); ++i) {
                if (commentedSource[i] == '"' && (i==0||commentedSource[i-1]!='\\')) inString = !inString;
                if (!inString) {
                        if (i < commentedSource.length() - 1 && commentedSource[i] == '/' && commentedSource[i + 1] == '*') { commentLong = true; i++; continue; }
                        if (i < commentedSource.length() - 1 && commentedSource[i] == '*' && commentedSource[i + 1] == '/') { commentLong = false; i++; continue; }
                        if (i < commentedSource.length() - 1 && commentedSource[i] == '/' && commentedSource[i + 1] == '/') { commentRow = true; i++; continue; }
                        if (commentedSource[i] == '\n') commentRow = false;
                }
                if (!commentLong && !commentRow)
                        source += std::string(1, commentedSource[i]);
        }

        // insert our buffer definition after the glsl version define
        size_t version = source.find("#version");
        size_t lineAfterVersion = 2, bufferInsertOffset = 0;

        if (version != std::string::npos) {
                ++bufferInsertOffset;

                for (size_t i = 0; i < version; ++i)
                        if (source[i] == '\n')
                                ++lineAfterVersion;

                for (size_t i = version; i < source.length(); ++i)
                        if (source[i] == '\n')
                                break;
                        else
                                bufferInsertOffset += 1;
        }

        // go through all printfs in the shader
        size_t printfLoc = findCall(source, "printf");
        while (printfLoc != std::string::npos) {

                size_t printfEndLoc = printfLoc;

                int parentheses = 0;
                bool inString = false;

                // gather the arguments
                std::vector<std::string> args;
                while (true) {

                        printfEndLoc++;

                        if (!inString && parentheses == 1 && source[printfEndLoc] == ',') {
                                std::string arg;

                                size_t argLoc = printfEndLoc + 1;
                                int argParentheses = 0;
                                while (argParentheses > 0 || source[argLoc] != ',') {
                                        if (source[argLoc] == '(') ++argParentheses;
                                        if (source[argLoc] == ')') --argParentheses;
                                        if (argParentheses < 0) break;
                                        if (source[argLoc] != ' ')
                                                arg = arg + std::string(1, source[argLoc]);
                                        ++argLoc;
                                }
                                args.emplace_back(arg);
                        }

                        if (source[printfEndLoc] == '"')
                                inString = !inString;
                        if (source[printfEndLoc] == '\\')
                                ++printfEndLoc;
                        if (!inString && source[printfEndLoc] == '(')
                                parentheses++;
                        if (!inString && source[printfEndLoc] == ')') {
                                parentheses--;
                                if (!parentheses) {
                                        do { printfEndLoc++; } while (source[printfEndLoc] != ';');
                                        break;
                                }
                        }
                }

                // come up with a list of data insertions that match the printf call
                std::string replacement = "";
                size_t argumentIndex = 0, writeSize = 0;
                inString = false;
                for (size_t i = printfLoc; i < printfEndLoc; ++i) {

                        if (source[i] == '"')
                                inString = !inString;
                        if (inString && source[i] == '\\') {
                                char ch = '\\';
                                switch (source[i + 1]) {
                                case '\'': ch = '\''; break;
                                case '\"': ch = '\"'; break;
                                case '?': ch = '\?'; break;
                                case '\\': ch = '\\'; break;
                                case 'a': ch = '\a'; break;
                                case 'b': ch = '\b'; break;
                                case 'f': ch = '\f'; break;
                                case 'n': ch = '\n'; break;
                                case 'r': ch = '\r'; break;
                                case 't': ch = '\t'; break;
                                case 'v': ch = '\v'; break;
                                default: ch = ' ';
                                }
                                replacement += "printData[printIndex++]=" + std::to_string(ch) + ";";
                                writeSize++;
                                i++;
                        }
                        else if (inString && source[i] != '"') {
                                replacement += "printData[printIndex++]=" + std::to_string(unsigned(source[i])) + ";";
                                writeSize++;
                        }
                        if (inString && source[i] == '%')
                                if (source[i + 1] == '%') {
                                        i++;
                                        replacement += "printData[printIndex++]=" + std::to_string(unsigned(source[i])) + ";";
                                        writeSize++;
                                }
                                else {
                                        int vecSize = 1;
                                        while (std::string(1, source[i]).find_first_of("eEfFgGdiuoxXaA") == std::string::npos) {
                                                // a special feature to support vector prints
                                                if (source[i] == '^')
                                                        vecSize = source[i + 1] - '0';
                                                i++;
                                                replacement += "printData[printIndex++]=" + std::to_string(unsigned(source[i])) + ";";
                                                writeSize++;
                                        }
                                        // store the actual data in the element after the format string
                                        for (int j = 0; j < vecSize; ++j) {
                                                std::string arg = args[argumentIndex];
                                                if (vecSize > 1)
                                                        arg = "(" + arg + ")." + std::string("xyzw")[j];
                                                switch (source[i]) {
                                                case 'e': case 'E': case 'f': case 'F': case 'g': case 'G': case 'x': case 'X':
                                                        replacement += "printData[printIndex++]=floatBitsToUint(" + arg + ");"; break;
                                                default:
                                                        replacement += "printData[printIndex++]=" + arg + ";"; break;
                                                }
                                                writeSize++;
                                        }
                                        argumentIndex++;
                                }
                }

                source = source.substr(0, printfLoc) + "if(printfWriter){" + "uint printIndex=min(atomicAdd(printData[0]," + std::to_string(writeSize) + "u),printData.length()-" + std::to_string(writeSize) + "u);" + replacement + "}" + source.substr(printfEndLoc + 1);

                printfLoc = findCall(source, "printf");
        }

        // insert the ssbo definition and some helper functions after the #version line
        return source.substr(0, bufferInsertOffset) + "\nbuffer printBuffer{uint printData[];};bool printfWriter = false;void enablePrintf(){printfWriter=true;}void disablePrintf(){printfWriter=false;}\n#line " + std::to_string(lineAfterVersion) + "\n" + source.substr(bufferInsertOffset);
}

// replacement for glShaderSource that parses printf commands into buffer insertions
inline void glShaderSourcePrint(GLuint shader, GLsizei count, const GLchar **string, const GLint *length) {
        // first combine all of the potential source files to a single string
        std::string source;
        for (int i = 0; i < count; ++i) {
                if (!length || length[i] < 0)
                        source += std::string(string[i]);
                else
                        source += std::string(string[i], length[i]);
        }
        // parse
        source = addPrintToSource(source);
        // do the compilation
        auto* finalString = source.c_str();
        glShaderSource(shader, 1, &finalString, nullptr);
}
#endif // SHARER_PRINTF_HPP
