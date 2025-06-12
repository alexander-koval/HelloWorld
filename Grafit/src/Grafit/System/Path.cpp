#include <Grafit/System/Path.hpp>
#include <Grafit/System/File.hpp>
#include <Grafit/System/SystemInfo.hpp>
#include <Grafit/System/Assert.hpp>
#include <exception>
#include <algorithm>

namespace gf {

Path::Path(): m_absolute(false)
{
}


Path::Path(bool absolutePath): m_absolute(absolutePath)
{
}


Path::Path(const std::string& path)
{
    assign(path);
}


Path::Path(const std::string& path, Style style)
{
    assign(path, style);
}


Path::Path(const char* path)
{
    assign(path);
}


Path::Path(const char* path, Style style)
{
    assign(path, style);
}


Path::Path(const Path& path):
    m_node(path.m_node),
    m_device(path.m_device),
    m_name(path.m_name),
    m_version(path.m_version),
    m_dirs(path.m_dirs),
    m_absolute(path.m_absolute)
{
}


Path::Path(const Path& rParent, const std::string& fileName):
    m_node(rParent.m_node),
    m_device(rParent.m_device),
    m_name(rParent.m_name),
    m_version(rParent.m_version),
    m_dirs(rParent.m_dirs),
    m_absolute(rParent.m_absolute)
{
    makeDirectory();
    m_name = fileName;
}


Path::Path(const Path& rParent, const char* fileName):
    m_node(rParent.m_node),
    m_device(rParent.m_device),
    m_name(rParent.m_name),
    m_version(rParent.m_version),
    m_dirs(rParent.m_dirs),
    m_absolute(rParent.m_absolute)
{
    makeDirectory();
    m_name = fileName;
}


Path::Path(const Path& rParent, const Path& relative):
    m_node(rParent.m_node),
    m_device(rParent.m_device),
    m_name(rParent.m_name),
    m_version(rParent.m_version),
    m_dirs(rParent.m_dirs),
    m_absolute(rParent.m_absolute)
{
    resolve(relative);
}


Path::~Path()
{
}


Path& Path::operator = (const Path& path)
{
    return assign(path);
}


Path& Path::operator = (const std::string& path)
{
    return assign(path);
}


Path& Path::operator = (const char* path)
{
    return assign(path);
}


void Path::swap(Path& path)
{
    std::swap(m_node, path.m_node);
    std::swap(m_device, path.m_device);
    std::swap(m_name, path.m_name);
    std::swap(m_version, path.m_version);
    std::swap(m_dirs, path.m_dirs);
    std::swap(m_absolute, path.m_absolute);
}


Path& Path::assign(const Path& path)
{
    if (&path != this)
    {
        m_node     = path.m_node;
        m_device   = path.m_device;
        m_name     = path.m_name;
        m_version  = path.m_version;
        m_dirs     = path.m_dirs;
        m_absolute = path.m_absolute;
    }
    return *this;
}


Path& Path::assign(const std::string& path)
{
#if defined(GRAFIT_SYSTEM_WINDOWS)
    parseWindows(path);
#else
    parseUnix(path);
#endif
    return *this;
}


Path& Path::assign(const std::string& path, Style style)
{
    switch (style)
    {
    case PATH_UNIX:
        parseUnix(path);
        break;
    case PATH_WINDOWS:
        parseWindows(path);
        break;
    }
    return *this;
}


Path& Path::assign(const char* path)
{
    return assign(std::string(path));
}


std::string Path::toString() const
{
#if defined(GRAFIT_SYSTEM_WINDOWS)
    return buildWindows();
#else
    return buildUnix();
#endif
}


std::string Path::toString(Style style) const
{
    switch (style)
    {
    case PATH_UNIX:
        return buildUnix();
    case PATH_WINDOWS:
        return buildWindows();
    }
    return std::string();
}


bool Path::tryParse(const std::string& path)
{
    try
    {
        Path p;
        p.parse(path);
        assign(p);
        return true;
    }
    catch (...)
    {
        return false;
    }
}


bool Path::tryParse(const std::string& path, Style style)
{
    try
    {
        Path p;
        p.parse(path, style);
        assign(p);
        return true;
    }
    catch (...)
    {
        return false;
    }
}


Path& Path::parseDirectory(const std::string& path)
{
    assign(path);
    return makeDirectory();
}


Path& Path::parseDirectory(const std::string& path, Style style)
{
    assign(path, style);
    return makeDirectory();
}


Path& Path::makeDirectory()
{
#if defined(POCO_OS_FAMILY_VMS)
    pushDirectory(getBaseName());
#else
    pushDirectory(m_name);
#endif
    m_name.clear();
    m_version.clear();
    return *this;
}


Path& Path::makeFile()
{
    if (!m_dirs.empty() && m_name.empty())
    {
        m_name = m_dirs.back();
        m_dirs.pop_back();
#if defined(POCO_OS_FAMILY_VMS)
        setExtension("DIR");
#endif
    }
    return *this;
}


Path& Path::makeAbsolute()
{
    return makeAbsolute(current());
}


Path& Path::makeAbsolute(const Path& base)
{
    if (!m_absolute)
    {
        Path tmp = base;
        tmp.makeDirectory();
        for (StringVec::const_iterator it = m_dirs.begin(); it != m_dirs.end(); ++it)
        {
            tmp.pushDirectory(*it);
        }
        m_node     = tmp.m_node;
        m_device   = tmp.m_device;
        m_dirs     = tmp.m_dirs;
        m_absolute = base.m_absolute;
    }
    return *this;
}


Path Path::absolute() const
{
    Path result(*this);
    if (!result.m_absolute)
    {
        result.makeAbsolute();
    }
    return result;
}


Path Path::absolute(const Path& base) const
{
    Path result(*this);
    if (!result.m_absolute)
    {
        result.makeAbsolute(base);
    }
    return result;
}


Path Path::parent() const
{
    Path p(*this);
    return p.makeParent();
}


Path& Path::makeParent()
{
    if (m_name.empty())
    {
        if (m_dirs.empty())
        {
            if (!m_absolute)
                m_dirs.push_back("..");
        }
        else
        {
            if (m_dirs.back() == "..")
                m_dirs.push_back("..");
            else
                m_dirs.pop_back();
        }
    }
    else
    {
        m_name.clear();
        m_version.clear();
    }
    return *this;
}


Path& Path::append(const Path& path)
{
    makeDirectory();
    m_dirs.insert(m_dirs.end(), path.m_dirs.begin(), path.m_dirs.end());
    m_name = path.m_name;
    m_version = path.m_version;
    return *this;
}


Path& Path::resolve(const Path& path)
{
    if (path.isAbsolute())
    {
        assign(path);
    }
    else
    {
        for (int i = 0; i < path.depth(); ++i)
            pushDirectory(path[i]);
        m_name = path.m_name;
    }
    return *this;
}


Path& Path::setNode(const std::string& node)
{
    m_node     = node;
    m_absolute = m_absolute || !node.empty();
    return *this;
}


Path& Path::setDevice(const std::string& device)
{
    m_device   = device;
    m_absolute = m_absolute || !device.empty();
    return *this;
}


const std::string& Path::directory(int n) const
{
//    GF_ASSERT(0 <= n, n <= m_dirs.size(), "");

    if (n < m_dirs.size())
        return m_dirs[n];
    else
        return m_name;
}


const std::string& Path::operator [] (int n) const
{
//    poco_assert (0 <= n && n <= m_dirs.size());

    if (n < m_dirs.size())
        return m_dirs[n];
    else
        return m_name;
}


Path& Path::pushDirectory(const std::string& dir)
{
    if (!dir.empty() && dir != ".")
    {
        if (dir == "..")
        {
            if (!m_dirs.empty() && m_dirs.back() != "..")
                m_dirs.pop_back();
            else if (!m_absolute)
                m_dirs.push_back(dir);
        }
        else m_dirs.push_back(dir);
    }
    return *this;
}


Path& Path::popDirectory()
{
//    GF_ASSERT(!m_dirs.empty(), "");

    m_dirs.pop_back();
    return *this;
}


Path& Path::popFrontDirectory()
{
//    GF_ASSERT(!m_dirs.empty(), "");

    StringVec::iterator it = m_dirs.begin();
    m_dirs.erase(it);
    return *this;
}


Path& Path::setFileName(const std::string& name)
{
    m_name = name;
    return *this;
}


Path& Path::setBaseName(const std::string& name)
{
    std::string ext = getExtension();
    m_name = name;
    if (!ext.empty())
    {
        m_name.append(".");
        m_name.append(ext);
    }
    return *this;
}


std::string Path::getBaseName() const
{
    std::string::size_type pos = m_name.rfind('.');
    if (pos != std::string::npos)
        return m_name.substr(0, pos);
    else
        return m_name;
}


Path& Path::setExtension(const std::string& extension)
{
    m_name = getBaseName();
    if (!extension.empty())
    {
        m_name.append(".");
        m_name.append(extension);
    }
    return *this;
}


std::string Path::getExtension() const
{
    std::string::size_type pos = m_name.rfind('.');
    if (pos != std::string::npos)
        return m_name.substr(pos + 1);
    else
        return std::string();
}


Path& Path::clear()
{
    m_node.clear();
    m_device.clear();
    m_name.clear();
    m_dirs.clear();
    m_version.clear();
    m_absolute = false;
    return *this;
}


std::string Path::current()
{
    return SystemInfo::getApplicationDirectory();
}


std::string Path::home()
{
    return SystemInfo::getUserDirectory();
}

std::string Path::temp()
{
    return SystemInfo::getTempDirectory();
}

bool Path::find(StringVec::const_iterator it, StringVec::const_iterator end, const std::string& name, Path& path)
{
    while (it != end)
    {
#if defined(WIN32)
        std::string cleanPath(*it);
        if (cleanPath.size() > 1 && cleanPath[0] == '"' && cleanPath[cleanPath.size() - 1] == '"')
        {
            cleanPath = cleanPath.substr(1, cleanPath.size() - 2);
        }
        Path p(cleanPath);
#else
        Path p(*it);
#endif
        p.makeDirectory();
        p.resolve(Path(name));
        File f(p.toString());
        if (f.isExist())
        {
            path = p;
            return true;
        }
        ++it;
    }
    return false;
}

void Path::parseUnix(const std::string& path)
{
    clear();

    std::string::const_iterator it  = path.begin();
    std::string::const_iterator end = path.end();

    if (it != end)
    {
        if (*it == '/')
        {
            m_absolute = true; ++it;
        }
        else if (*it == '~')
        {
            ++it;
            if (it == end || *it == '/')
            {
                Path cwd(home());
                m_dirs = cwd.m_dirs;
                m_absolute = true;
            }
            else --it;
        }

        while (it != end)
        {
            std::string name;
            while (it != end && *it != '/') name += *it++;
            if (it != end)
            {
                if (m_dirs.empty())
                {
                    if (!name.empty() && *(name.rbegin()) == ':')
                    {
                        m_absolute = true;
                        m_device.assign(name, 0, name.length() - 1);
                    }
                    else
                    {
                        pushDirectory(name);
                    }
                }
                else pushDirectory(name);
            }
            else m_name = name;
            if (it != end) ++it;
        }
    }
}


void Path::parseWindows(const std::string& path)
{
    clear();

    std::string::const_iterator it  = path.begin();
    std::string::const_iterator end = path.end();

    if (it != end)
    {
        if (*it == '\\' || *it == '/') { m_absolute = true; ++it; }
        if (m_absolute && it != end && (*it == '\\' || *it == '/')) // UNC
        {
            ++it;
            while (it != end && *it != '\\' && *it != '/') m_node += *it++;
            if (it != end) ++it;
        }
        else if (it != end)
        {
            char d = *it++;
            if (it != end && *it == ':') // drive letter
            {
                if (m_absolute || !((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))) throw std::invalid_argument(path);
                m_absolute = true;
                m_device += d;
                ++it;
                if (it == end || (*it != '\\' && *it != '/')) throw std::invalid_argument(path);
                ++it;
            }
            else --it;
        }
        while (it != end)
        {
            std::string name;
            while (it != end && *it != '\\' && *it != '/') name += *it++;
            if (it != end)
                pushDirectory(name);
            else
                m_name = name;
            if (it != end) ++it;
        }
    }
    if (!m_node.empty() && m_dirs.empty() && !m_name.empty())
        makeDirectory();
}

std::string Path::buildUnix() const
{
    std::string result;
    if (!m_device.empty())
    {
        result.append("/");
        result.append(m_device);
        result.append(":/");
    }
    else if (m_absolute)
    {
        result.append("/");
    }
    for (StringVec::const_iterator it = m_dirs.begin(); it != m_dirs.end(); ++it)
    {
        result.append(*it);
        result.append("/");
    }
    result.append(m_name);
    return result;
}


std::string Path::buildWindows() const
{
    std::string result;
    if (!m_node.empty())
    {
        result.append("\\\\");
        result.append(m_node);
        result.append("\\");
    }
    else if (!m_device.empty())
    {
        result.append(m_device);
        result.append(":\\");
    }
    else if (m_absolute)
    {
        result.append("\\");
    }
    for (StringVec::const_iterator it = m_dirs.begin(); it != m_dirs.end(); ++it)
    {
        result.append(*it);
        result.append("\\");
    }
    result.append(m_name);
    return result;
}

}
