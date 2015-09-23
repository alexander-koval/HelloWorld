#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <memory>
#include <type_traits>
#include <Grafit/System/Assert.hpp>
#include <Grafit/System/Destructable.hpp>

namespace gf {

namespace priv {
template<typename ... Args> class FunctionImpl;

template <typename R, typename ... Args>
class FunctionImpl<R(Args...)> : public Destructable {
public:
    using Fn = R(Args...);
    using ResultType = R;
    virtual R operator()(Args&& ...args) = 0;
    virtual FunctionImpl* clone(void) const = 0;

    template <typename U>
    static U* clone(U* object) {
        if (!object) return nullptr;
        U* clone = static_cast<U*>(object->clone());
        GF_ASSERT(typeid(*object) == typeid(*clone), "Can't make clone object", typeid(*clone).name());
        return clone;
    }
};

template <typename ParentFunction, typename FnPtr, typename ... Args>
class FuncPtrImpl : public ParentFunction::Impl {
    using Base = typename ParentFunction::Impl;
public:
    using ResultType = typename Base::ResultType;

    FuncPtrImpl(const FnPtr& fun) : m_fun(fun) { }

    virtual ResultType operator()(Args&& ...args) {
        return m_fun(std::forward<Args>(args)...);
    }

    virtual FuncPtrImpl* clone(void) const {
        return new FuncPtrImpl(*this);
    }

    FnPtr m_fun;
};


template <typename ParentFunction, typename ObjectPtr, typename MemFnPtr, typename ... Args>
class ClassMethodImpl : public ParentFunction::Impl {
    using Base = typename ParentFunction::Impl;
public:
    using ResultType = typename Base::ResultType;

    ClassMethodImpl(const ObjectPtr& object, MemFnPtr fun) : m_object(object), m_fun(fun) {}

    virtual ResultType operator()(Args&& ...args) {
        return ((*m_object).*m_fun)(std::forward<Args>(args)...);
    }

    virtual ClassMethodImpl* clone(void) const {
        return new ClassMethodImpl(*this);
    }

    ObjectPtr m_object;
    MemFnPtr m_fun;
};
}

template <typename ... Args> class Function;
template <typename R, typename ... Args>
class Function<R(Args...)> {
public:
    using Impl = priv::FunctionImpl<R(Args...)>;
    using ResultType = R;

    Function(void) : m_pimpl() { }

    Function(const Function& other) : m_pimpl(Impl::clone(other.m_pimpl.get())) { }

    template <typename Fn>
    Function(Fn fun) : m_pimpl(new priv::FuncPtrImpl<Function, Fn, Args...>(fun)) {
        std::cout << "FunctionPtrStub" << std::endl;
    }

    template <typename ObjPtr, typename MemFn>
    Function(const ObjPtr& obj, MemFn memFn) : m_pimpl(new priv::ClassMethodImpl<Function, ObjPtr, MemFn, Args...>(obj, memFn)) {
        std::cout << "ClassMethodStub" << std::endl;
    }

    Function& operator =(const Function& other) {
        Function copy(other);
        Impl* impl = m_pimpl.release();
        m_pimpl.reset(copy.m_pimpl.release());
        copy.m_pimpl.reset(impl);
        return *this;
    }

    ResultType operator ()(Args&& ...args) const {
        return (*m_pimpl)(std::forward<Args>(args)...);
    }

private:
    std::unique_ptr<Impl> m_pimpl;

};

}

#endif // FUNCTION_HPP
