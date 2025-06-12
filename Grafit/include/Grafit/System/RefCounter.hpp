#ifndef REFCOUNTER_HPP
#define REFCOUNTER_HPP

#include <cstdint>
#include <Grafit/System/Assert.hpp>

namespace gf {

class RefCounter {
protected:
    RefCounter() : m_counter(0), m_weakCounter(0) {}

    explicit RefCounter(const RefCounter&) : m_counter(0), m_weakCounter(0) {}

    RefCounter& operator= (const RefCounter&) { return *this; }

    virtual ~RefCounter();

    uint16_t refCount() const { return m_counter; }

    uint16_t refWeakCount() const { return m_weakCounter; }

private:
    friend void intrusive_ptr_add_ref(RefCounter* p);
    friend void intrusive_ptr_release(RefCounter* p);
    friend void intrusive_weak_ptr_add_ref(RefCounter* p);
    friend void intrusive_weak_ptr_release(RefCounter* p);
    friend bool intrusive_weak_ptr_alive(RefCounter* p);

private:
    mutable uint16_t m_counter;
    mutable uint16_t m_weakCounter;
};

}

#endif // REFCOUNTER_HPP
