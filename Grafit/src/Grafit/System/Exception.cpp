#include <Grafit/System/Exception.hpp>


#include <Grafit/System/Exception.hpp>
#include <typeinfo>


namespace gf {


Exception::Exception(int otherCode)
: m_nested(nullptr)
, m_code(otherCode) {

}


Exception::Exception(const std::string& msg, int otherCode)
: m_msg(msg)
, m_nested(nullptr)
, m_code(otherCode) {
}


Exception::Exception(const std::string& msg, const std::string& arg, int otherCode)
: m_msg(msg)
, m_nested(nullptr)
, m_code(otherCode) {
    if (!arg.empty()) {
        m_msg.append(": ");
        m_msg.append(arg);
    }
}


Exception::Exception(const std::string& msg, const Exception& nestedException, int otherCode)
: m_msg(msg)
, m_nested(nestedException.clone())
, m_code(otherCode) {
}


Exception::Exception(const Exception& exc)
: std::exception(exc),
m_msg(exc.m_msg),
m_code(exc.m_code) {
    m_nested = exc.m_nested ? exc.m_nested->clone() : nullptr;
}


Exception::~Exception() noexcept {
    delete m_nested;
}


Exception& Exception::operator = (const Exception& exc) {
    if (&exc != this) {
        Exception* newPNested = exc.m_nested ? exc.m_nested->clone() : nullptr;
        delete m_nested;
        m_msg     = exc.m_msg;
        m_nested = newPNested;
        m_code    = exc.m_code;
    }
    return *this;
}


const char* Exception::name() const noexcept {
    return "Exception";
}


const char* Exception::className() const noexcept {
    return typeid(*this).name();
}


const char* Exception::what() const noexcept {
    return name();
}


std::string Exception::displayText() const {
    std::string txt = name();
    if (!m_msg.empty()) {
        txt.append(": ");
        txt.append(m_msg);
    }
    return txt;
}


void Exception::extendedMessage(const std::string& arg) {
    if (!arg.empty()) {
        if (!m_msg.empty()) m_msg.append(": ");
        m_msg.append(arg);
    }
}


Exception* Exception::clone() const {
    return new Exception(*this);
}


void Exception::rethrow() const {
    throw *this;
}


GF_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
GF_IMPLEMENT_EXCEPTION(AssertionViolationException, LogicException, "Assertion violation")
GF_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
GF_IMPLEMENT_EXCEPTION(NullValueException, LogicException, "Null value")
GF_IMPLEMENT_EXCEPTION(BugcheckException, LogicException, "Bugcheck")
GF_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException, "Invalid argument")
GF_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException, "Not implemented")
GF_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")
GF_IMPLEMENT_EXCEPTION(IllegalStateException, LogicException, "Illegal state")
GF_IMPLEMENT_EXCEPTION(InvalidAccessException, LogicException, "Invalid access")
GF_IMPLEMENT_EXCEPTION(SignalException, LogicException, "Signal received")
GF_IMPLEMENT_EXCEPTION(UnhandledException, LogicException, "Unhandled exception")

GF_IMPLEMENT_EXCEPTION(RuntimeException, Exception, "Runtime exception")
GF_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException, "Not found")
GF_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException, "Exists")
GF_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException, "Timeout")
GF_IMPLEMENT_EXCEPTION(SystemException, RuntimeException, "System exception")
GF_IMPLEMENT_EXCEPTION(RegularExpressionException, RuntimeException, "Error in regular expression")
GF_IMPLEMENT_EXCEPTION(LibraryLoadException, RuntimeException, "Cannot load library")
GF_IMPLEMENT_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException, "Library already loaded")
GF_IMPLEMENT_EXCEPTION(NoThreadAvailableException, RuntimeException, "No thread available")
GF_IMPLEMENT_EXCEPTION(PropertyNotSupportedException, RuntimeException, "Property not supported")
GF_IMPLEMENT_EXCEPTION(PoolOverflowException, RuntimeException, "Pool overflow")
GF_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException, "No permission")
GF_IMPLEMENT_EXCEPTION(OutOfMemoryException, RuntimeException, "Out of memory")
GF_IMPLEMENT_EXCEPTION(DataException, RuntimeException, "Data error")

GF_IMPLEMENT_EXCEPTION(InterruptedException, RuntimeException, "Interrupted")
GF_IMPLEMENT_EXCEPTION(IndexOutOfBoundsException, RuntimeException, "Index out of bounds")
GF_IMPLEMENT_EXCEPTION(UnsupportedOperationException, RuntimeException, "Unsupported operation")
GF_IMPLEMENT_EXCEPTION(EmptyStackException, RuntimeException, "Empty stack")
GF_IMPLEMENT_EXCEPTION(StackOverflowException, RuntimeException, "Stack overflow")
GF_IMPLEMENT_EXCEPTION(ArithmeticException, RuntimeException, "Arithmetic error")

GF_IMPLEMENT_EXCEPTION(DataFormatException, DataException, "Bad data format")
GF_IMPLEMENT_EXCEPTION(SyntaxException, DataException, "Syntax error")
GF_IMPLEMENT_EXCEPTION(CircularReferenceException, DataException, "Circular reference")
GF_IMPLEMENT_EXCEPTION(PathSyntaxException, SyntaxException, "Bad path syntax")
GF_IMPLEMENT_EXCEPTION(IOException, RuntimeException, "I/O error")
GF_IMPLEMENT_EXCEPTION(ProtocolException, IOException, "Protocol error")
GF_IMPLEMENT_EXCEPTION(FileException, IOException, "File access error")
GF_IMPLEMENT_EXCEPTION(FileExistsException, FileException, "File exists")
GF_IMPLEMENT_EXCEPTION(FileNotFoundException, FileException, "File not found")
GF_IMPLEMENT_EXCEPTION(PathNotFoundException, FileException, "Path not found")
GF_IMPLEMENT_EXCEPTION(FileReadOnlyException, FileException, "File is read-only")
GF_IMPLEMENT_EXCEPTION(FileAccessDeniedException, FileException, "Access to file denied")
GF_IMPLEMENT_EXCEPTION(CreateFileException, FileException, "Cannot create file")
GF_IMPLEMENT_EXCEPTION(OpenFileException, FileException, "Cannot open file")
GF_IMPLEMENT_EXCEPTION(WriteFileException, FileException, "Cannot write file")
GF_IMPLEMENT_EXCEPTION(ReadFileException, FileException, "Cannot read file")
GF_IMPLEMENT_EXCEPTION(SeekFileException, FileException, "Failed to set the file position")
GF_IMPLEMENT_EXCEPTION(DirectoryNotEmptyException, FileException, "Directory not empty")
GF_IMPLEMENT_EXCEPTION(UnknownURISchemeException, RuntimeException, "Unknown URI scheme")
GF_IMPLEMENT_EXCEPTION(TooManyURIRedirectsException, RuntimeException, "Too many URI redirects")
GF_IMPLEMENT_EXCEPTION(URISyntaxException, SyntaxException, "Bad URI syntax")

GF_IMPLEMENT_EXCEPTION(ApplicationException, Exception, "Application exception")
GF_IMPLEMENT_EXCEPTION(BadCastException, RuntimeException, "Bad cast exception")


}
