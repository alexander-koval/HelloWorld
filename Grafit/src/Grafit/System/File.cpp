#include <Grafit/System/File.hpp>

namespace gf {

File::File(const String& path)
    : m_path(path)
    , m_status() {
    using boost::filesystem::file_status;
    boost::system::error_code code;
    m_status = boost::filesystem::status(m_path, code);
}

File::~File(void) {

}

bool File::isExist(void) const {
    return boost::filesystem::exists(m_status);
}

bool File::isDirectory(void) const {
    return boost::filesystem::is_directory(m_status);
}

bool File::isHidden(void) const {

}

bool File::isSymbolicLink(void) const {
    return boost::filesystem::is_symlink(m_status);
}

bool File::isRegularFile(void) const {
    return boost::filesystem::is_regular_file(m_status);
}

String File::getName(void) const {
    boost::filesystem::path path = m_path.stem();
    return path.c_str();
}

String File::getExtension(void) const {
    boost::filesystem::path path = m_path.extension();
    return path.c_str();
}

String File::getNativePath(void) const {
    return m_path.native();
}

const File& File::getParent(void) const {

}

String File::getSeparator(void) {
    return boost::filesystem::path::preferred_separator;
}

float File::getSize(void) const {
    boost::uintmax_t size = boost::filesystem::file_size(m_path);
    return size;
}

float File::getSpaceAvailable(void) const {
    boost::filesystem::space_info space = boost::filesystem::space(m_path);
    return space.available;
}

String File::getType(void) const {
//    m_status.type();
}

}
