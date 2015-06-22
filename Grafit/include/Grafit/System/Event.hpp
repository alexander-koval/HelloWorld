#ifndef EVENT_HPP
#define EVENT_HPP

#include <utility>
#include <cassert>

class Delegate {
    typedef void* InstancePtr;
    typedef void (*InternalFunction)(InstancePtr, int);
    typedef std::pair<InstancePtr, InternalFunction> Stub;

    template<void (*Function)(int)>
    static inline void FunctionStub(InstancePtr, int ARG0) {
        return (Function)(ARG0);
    }

    template<typename C, void(C::*Function)(int)>
    static inline void ClassMethodStub(InstancePtr instance, int ARG0) {
        return (static_cast<C*>(instance)->*Function)(ARG0);
    }

public:
    Delegate(void) : m_stub(nullptr, nullptr) {

    }

    template<void (*Function)(int)>
    void bind(void) {
        m_stub.first = nullptr;
        m_stub.second = &FunctionStub<Function>;
    }

    template<typename C, void(C::*Function)(int)>
    void bind(C* instance) {
        m_stub.first = instance;
        m_stub.second = &ClassMethodStub<C, Function>;
    }

    void invoke(int ARG0) const {
        assert(m_stub.second != nullptr)        ;
        return m_stub.second(m_stub.first, ARG0);
    }

private:
    Stub m_stub;

};

#endif // EVENT_HPP

