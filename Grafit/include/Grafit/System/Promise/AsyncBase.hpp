#ifndef ASYNCBASE_HPP
#define ASYNCBASE_HPP

#include <vector>
#include <memory>
#include <functional>

namespace gf {
template <typename T, typename E>
class AsyncBase;
template <typename T, typename E>
using AsyncBasePtr = std::shared_ptr<AsyncBase<T, E>>;

template <typename T, typename E>
struct AsyncLink
{
    AsyncBasePtr<T, E> async;
    std::function<void(T)> linkf;
};

template <typename T, typename E>
class AsyncBase : public std::enable_shared_from_this<AsyncBase<T, E>>
{
public:
        AsyncBase(AsyncBasePtr<T, E> d = AsyncBasePtr<T, E>());

        virtual ~AsyncBase();

        bool isResolved() const;

        bool isErrored() const;

        bool isErrorPending() const;

        bool isFulfilled() const;

        bool isPending() const;

        AsyncBasePtr<T, E> errorThen(std::function<T(E)>&& fn);

        AsyncBasePtr<T, E> errorThen(const std::function<T(E)>& fn);

        AsyncBasePtr<T, E> then(std::function<T(T)>&& fn);

        AsyncBasePtr<T, E> then(const std::function<T(T)>& fn);

        virtual void unlink(AsyncBasePtr<T, E> to);

        virtual bool isLinked(AsyncBasePtr<T, E> to);

        template <typename A, typename B>
        static void link(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, std::function<B(A)>&& fn);

        template <typename A, typename B>
        static void link(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, const std::function<B(A)>& fn);

        template <typename A, typename B>
        static void immediateLinkUpdate(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, std::function<B(A)>&& fn);

        template <typename A, typename B>
        static void immediateLinkUpdate(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, const std::function<B(A)>& fn);

        virtual void handleResolve(T value);

        virtual void handleError(E error);
protected:
        virtual AsyncBasePtr<T, E> thenImpl(std::function<T(T)>&& fn);

        virtual AsyncBasePtr<T, E> thenImpl(const std::function<T(T)>& fn);

        void resolve(T value);

        void onResolve(T value);

        void onError(E value);

protected:
        T _val;
        bool _resolved;
        bool _fulfilled;
        bool _pending;
        std::vector<AsyncLink<T, E>> _update;
        E _errorVal;
        bool _errored;
        bool _errorPending;
        std::function<T(E)> _errorMap;
        std::vector<std::function<void(E)>> _error;
};

}

#include <Grafit/System/Promise/AsyncBase.inl>
#endif // ASYNCBASE_HPP
