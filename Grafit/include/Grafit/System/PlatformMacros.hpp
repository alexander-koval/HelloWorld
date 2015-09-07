#ifndef PLATFORMMACROS_HPP
#define PLATFORMMACROS_HPP

#if defined(__GNUC__)
    #define GF_FUNCTION __PRETTY_FUNCTION__
#elif defined(__MSC_VER)
    #if _MSC_VER >= 1300
        #define GF_FUNCTION __FUNCDNAME__
    #else
        #define GF_FUNCTION __FUNCTION__
    #endif
#else
    #define GF_FUNCTION "unknown symbol"
#endif

#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
    #define GF_UNUSED //__attribute__((unused))
#else
    #define GF_UNUSED
#endif

#if defined(GRAFIT_SYSTEM_LINUX)
    #define BREAKPOINT { ::kill (0, SIGTRAP) }
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define GF_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define GF_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
    #define GF_DEPRECATED_ATTRIBUTE
#endif

#if _MSC_VER >= 1400
#    define GF_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)    N
#    define GF_VA_NUM_ARGS_REVERSE_SEQUENCE            10, 9, 8, 7, 6, 5, 4, 3, 2, 1
#    define GF_LEFT_PARENTHESIS (
#    define GF_RIGHT_PARENTHESIS )
#    define GF_VA_NUM_ARGS(...) GF_VA_NUM_ARGS_HELPER GF_LEFT_PARENTHESIS __VA_ARGS__, GF_VA_NUM_ARGS_REVERSE_SEQUENCE GF_RIGHT_PARENTHESIS
#else

    #define SIZE_OF(...) sizeof(#__VA_ARGS__)

    #define GF_VA_NUM_ARGS_EMPTY(...) (sizeof(#__VA_ARGS__) == sizeof(GF_STRINGIFY()))
    #define GF_VA_NUM_ARGS(...) GF_VA_NUM_ARGS_HELPER(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
    #define GF_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)    N
#endif

#if _MSC_VER >= 1400
#    define GF_PASS_ARGS(...)                            GF_LEFT_PARENTHESIS __VA_ARGS__ GF_RIGHT_PARENTHESIS
#else
#    define GF_PASS_ARGS(...)                            (__VA_ARGS__)
#endif

#define GF_DEPRECATED(...) GF_DEPRECATED_ATTRIBUTE

#define GF_STRINGIFY_HELPER(token)    #token

#define GF_STRINGIFY(x) GF_STRINGIFY_HELPER(x)

#define GF_TOSTRING(x) GF_STRINGIFY(x)

#define GF_JOIN(x, y) GF_JOIN_HELPER(x, y)

#define GF_JOIN_HELPER(x, y) GF_JOIN_HELPER_HELPER(x, y)

#define GF_JOIN_HELPER_HELPER(x, y)      x##y

#define GF_EXPAND_ARGS_0(op)                    op()
#define GF_EXPAND_ARGS_1(op, a1)                op(a1)
#define GF_EXPAND_ARGS_2(op, a1, a2)            op(a1) op(a2)
#define GF_EXPAND_ARGS_3(op, a1, a2, a3)        op(a1) op(a2) op(a3)
#define GF_EXPAND_ARGS_4(op, a1, a2, a3, a4)    op(a1) op(a2) op(a3) op(a4)

#define GF_EXPAND_ARGS(op, ...) GF_JOIN(GF_EXPAND_ARGS_, GF_VA_NUM_ARGS(__VA_ARGS__))(op, __VA_ARGS__)

#define GF_PRAGMA(pragma)    __pragma(pragma)

/// support for C99 restrict keyword
#define GF_RESTRICT    __restrict

/// tells the compiler that the return value (RV) of a function is an object that will not be aliased with any other pointers
#define GF_RESTRICT_RV    __declspec(restrict)

/// tells the compiler that a function call does not modify or reference visible global state and only modifies the memory pointed to directly by pointer parameters
#define GF_NO_ALIAS    __declspec(noalias)

/// forces a function to be inlined
#define GF_INLINE    __forceinline

/// tells the compiler to never inline a particular function
#define GF_NO_INLINE    __declspec(noinline)

/// passes optimization hints to the compiler
#define GF_HINT(hint)    __assume(hint)

/// used in switch-statements whose default-case can never be reached, resulting in more optimal code
#define GF_NO_SWITCH_DEFAULT    GF_HINT(0)

#endif // PLATFORMMACROS_HPP

