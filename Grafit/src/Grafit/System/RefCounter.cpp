#include <Grafit/System/RefCounter.hpp>

namespace gf {

RefCounter::~RefCounter() {
    GF_ASSERT(m_counter == 0, "Destroying, but still in use", m_counter);
}

void intrusive_ptr_add_ref(RefCounter* p) {
    GF_ASSERT(p->m_counter < 0xFFFF, "Out of Range", p->m_counter);
    ++p->m_counter;
}

void intrusive_ptr_release(RefCounter* p) {
    GF_ASSERT(p->m_counter > 0, "Out of Range", p->m_counter);
    --p->m_counter;
    if (p->m_counter == 0) {
        if (p->m_weakCounter == 0) {
            delete p;
        } else {
            void* mdp = dynamic_cast<void*>(p);
            p->~RefCounter();
            *reinterpret_cast<void**>(p) = mdp;
        }
    }
}

void intrusive_weak_ptr_add_ref(RefCounter* p) {
    GF_ASSERT(p->m_weakCounter < 0xFFFF, "Out of Range", p->m_weakCounter);
    ++p->m_weakCounter;
}

void intrusive_weak_ptr_release(RefCounter* p) {
    GF_ASSERT(p->m_weakCounter > 0, "Out of Range", p->m_weakCounter);
    --p->m_weakCounter;
    if (p->m_weakCounter == 0) {
        if (p->m_counter == 0) {
            void* mdp = *reinterpret_cast<void**>(p);
            ::operator delete(mdp);
        }
    }
}

bool intrusive_weak_ptr_alive(RefCounter* p) {
    return p->m_counter > 0;
}

}
