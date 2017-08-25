#ifndef ASYNCBASE_HPP
#define ASYNCBASE_HPP

#include <vector>
#include <functional>

namespace gf {
template <typename T, typename E>
class AsyncBase;

template <typename T, typename E>
struct AsyncLink
{
        AsyncBase<T, E>* async;
        std::function<void(T)> linkf;
};

template <typename T, typename E>
class AsyncBase
{
public:
        AsyncBase(AsyncBase<T, E>* d = nullptr);

        virtual ~AsyncBase();

        bool isResolved() const;

        bool isErrored() const;

        bool isErrorPending() const;

        bool isFulfilled() const;

        bool isPending() const;

        AsyncBase<T, E>* errorThen(std::function<T(E)>&& fn);

        virtual AsyncBase<T, E>* then(const std::function<T(T)>& fn);

        virtual void unlink(AsyncBase<T, E>* to);

        virtual bool isLinked(AsyncBase<T, E>* to);

        template <typename A, typename B>
        static void link(AsyncBase<A, E>* current, AsyncBase<B, E>* next, const std::function<B(A)>& fn);

        template <typename A, typename B>
        static void immediateLinkUpdate(AsyncBase<A, E>* current, AsyncBase<B, E>* next, const std::function<B(A)>& fn);

        virtual void handleResolve(T value);

        virtual void handleError(E error);
protected:
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
