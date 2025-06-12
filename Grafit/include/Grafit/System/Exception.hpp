#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

namespace gf {

class Exception : public std::exception {
public:
    Exception(const std::string &msg, int code = 0);

    Exception(const std::string &msg, const std::string &arg, int code = 0);

    Exception(const std::string &msg, const Exception &nested, int code = 0);

    Exception(const Exception &exc);

    ~Exception() noexcept;

    Exception &operator=(const Exception &exc);

    virtual const char *name() const noexcept;

    virtual const char *className() const noexcept;

    virtual const char *what() const noexcept;

    const Exception *nested() const;

    const std::string &message() const;

    int code() const;

    std::string displayText() const;

    virtual Exception *clone() const;

    virtual void rethrow() const;

protected:
    Exception(int code = 0);

    void message(const std::string &msg);

    void extendedMessage(const std::string &arg);

private:
    std::string m_msg;
    Exception* m_nested;
    int m_code;
};

inline const Exception *Exception::nested() const { return m_nested; }

inline const std::string &Exception::message() const { return m_msg; }

inline void Exception::message(const std::string &msg) { m_msg = msg; }

inline int Exception::code() const { return m_code; }

#define GF_DECLARE_EXCEPTION_CODE(CLS, BASE, CODE)                          \
    class CLS : public BASE {                                               \
    public:                                                                 \
    CLS(int code = CODE);                                                   \
    CLS(const std::string &msg, int code = CODE);                           \
    CLS(const std::string &msg, const std::string &arg, int code = CODE);   \
    CLS(const std::string &msg, const gf::Exception &exc, int code = CODE); \
    CLS(const CLS &exc);                                                    \
    ~CLS() noexcept;                                                        \
    CLS &operator=(const CLS &exc);                                         \
    const char *name() const noexcept;                                      \
    const char *className() const noexcept;                                 \
    gf::Exception *clone() const;                                           \
    void rethrow() const;                                                   \
};

#define GF_DECLARE_EXCEPTION(CLS, BASE) GF_DECLARE_EXCEPTION_CODE(CLS, BASE, 0)

#define GF_IMPLEMENT_EXCEPTION(CLS, BASE, NAME)                                  \
    CLS::CLS(int otherCode) : BASE(otherCode) {}                                 \
    CLS::CLS(const std::string &msg, int otherCode) : BASE(msg, otherCode) {}    \
    CLS::CLS(const std::string &msg, const std::string &arg, int otherCode)      \
    : BASE(msg, arg, otherCode) {}                                               \
    CLS::CLS(const std::string &msg, const gf::Exception &exc, int otherCode)    \
    : BASE(msg, exc, otherCode) {}                                               \
    CLS::CLS(const CLS &exc) : BASE(exc) {}                                      \
    CLS::~CLS() noexcept {}                                                      \
    CLS &CLS::operator=(const CLS &exc) {                                        \
    BASE::operator=(exc);                                                        \
    return *this;                                                                \
}                                                                                \
    const char *CLS::name() const noexcept { return NAME; }                      \
    const char *CLS::className() const noexcept { return typeid(*this).name(); } \
    gf::Exception *CLS::clone() const { return new CLS(*this); }                 \
    void CLS::rethrow() const { throw *this; }

GF_DECLARE_EXCEPTION(LogicException, Exception)
GF_DECLARE_EXCEPTION(AssertionViolationException, LogicException)
GF_DECLARE_EXCEPTION(NullPointerException, LogicException)
GF_DECLARE_EXCEPTION(NullValueException, LogicException)
GF_DECLARE_EXCEPTION(BugcheckException, LogicException)
GF_DECLARE_EXCEPTION(InvalidArgumentException, LogicException)
GF_DECLARE_EXCEPTION(NotImplementedException, LogicException)
GF_DECLARE_EXCEPTION(RangeException, LogicException)
GF_DECLARE_EXCEPTION(IllegalStateException, LogicException)
GF_DECLARE_EXCEPTION(InvalidAccessException, LogicException)
GF_DECLARE_EXCEPTION(SignalException, LogicException)
GF_DECLARE_EXCEPTION(UnhandledException, LogicException)

GF_DECLARE_EXCEPTION(RuntimeException, Exception)
GF_DECLARE_EXCEPTION(NotFoundException, RuntimeException)
GF_DECLARE_EXCEPTION(ExistsException, RuntimeException)
GF_DECLARE_EXCEPTION(TimeoutException, RuntimeException)
GF_DECLARE_EXCEPTION(SystemException, RuntimeException)
GF_DECLARE_EXCEPTION(RegularExpressionException, RuntimeException)
GF_DECLARE_EXCEPTION(LibraryLoadException, RuntimeException)
GF_DECLARE_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException)
GF_DECLARE_EXCEPTION(NoThreadAvailableException, RuntimeException)
GF_DECLARE_EXCEPTION(PropertyNotSupportedException, RuntimeException)
GF_DECLARE_EXCEPTION(PoolOverflowException, RuntimeException)
GF_DECLARE_EXCEPTION(NoPermissionException, RuntimeException)
GF_DECLARE_EXCEPTION(OutOfMemoryException, RuntimeException)
GF_DECLARE_EXCEPTION(DataException, RuntimeException)
GF_DECLARE_EXCEPTION(InterruptedException, RuntimeException)
GF_DECLARE_EXCEPTION(IndexOutOfBoundsException, RuntimeException)
GF_DECLARE_EXCEPTION(UnsupportedOperationException, RuntimeException)
GF_DECLARE_EXCEPTION(EmptyStackException, RuntimeException)
GF_DECLARE_EXCEPTION(StackOverflowException, RuntimeException)
GF_DECLARE_EXCEPTION(ArithmeticException, RuntimeException)

GF_DECLARE_EXCEPTION(DataFormatException, DataException)
GF_DECLARE_EXCEPTION(SyntaxException, DataException)
GF_DECLARE_EXCEPTION(CircularReferenceException, DataException)
GF_DECLARE_EXCEPTION(PathSyntaxException, SyntaxException)
GF_DECLARE_EXCEPTION(IOException, RuntimeException)
GF_DECLARE_EXCEPTION(ProtocolException, IOException)
GF_DECLARE_EXCEPTION(FileException, IOException)
GF_DECLARE_EXCEPTION(FileExistsException, FileException)
GF_DECLARE_EXCEPTION(FileNotFoundException, FileException)
GF_DECLARE_EXCEPTION(PathNotFoundException, FileException)
GF_DECLARE_EXCEPTION(FileReadOnlyException, FileException)
GF_DECLARE_EXCEPTION(FileAccessDeniedException, FileException)
GF_DECLARE_EXCEPTION(CreateFileException, FileException)
GF_DECLARE_EXCEPTION(OpenFileException, FileException)
GF_DECLARE_EXCEPTION(WriteFileException, FileException)
GF_DECLARE_EXCEPTION(ReadFileException, FileException)
GF_DECLARE_EXCEPTION(SeekFileException, FileException)
GF_DECLARE_EXCEPTION(DirectoryNotEmptyException, FileException)
GF_DECLARE_EXCEPTION(UnknownURISchemeException, RuntimeException)
GF_DECLARE_EXCEPTION(TooManyURIRedirectsException, RuntimeException)
GF_DECLARE_EXCEPTION(URISyntaxException, SyntaxException)

GF_DECLARE_EXCEPTION(ApplicationException, Exception)
GF_DECLARE_EXCEPTION(BadCastException, RuntimeException)

}  // namespace gf

#endif

