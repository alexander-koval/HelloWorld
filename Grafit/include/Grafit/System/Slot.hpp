#ifndef SLOT_HPP
#define SLOT_HPP

#include <Grafit/System/Signal.hpp>

namespace gf {

template <typename TSignal, typename TListener>
class Slot {
public:
    Slot(TSignal signal, TListener listener, bool once = false, int priority = 0);

    void remove(void);

    void setListener(TListener listener);

    TListener getListener(void);

    bool isOnce(void) const;

    int getPriority(void) const;

private:
    int m_priority;
    TListener m_listener;
    TSignal m_signal;
    bool m_isEnabled;
    bool m_isOnce;
};

template <typename TSignal, typename TListener>
Slot<TSignal, TListener>::Slot(TSignal signal, TListener listener, bool once, int priority)
    : m_priority(priority)
    , m_listener(listener)
    , m_signal(signal)
    , m_isEnabled(true)
    , m_isOnce(once) {

}

template <typename TSignal, typename TListener>
void Slot<TSignal, TListener>::remove(void) {
    m_signal.remove(m_listener);
}

template <typename TSignal, typename TListener>
void Slot<TSignal, TListener>::setListener(TListener listener) {
    m_listener = listener;
}

template <typename TSignal, typename TListener>
TListener Slot<TSignal, TListener>::getListener(void) {
    return m_listener;
}

class Slot0 : public Slot<gf::Signal0, void(*)()> {

};

}
#endif // SLOT_HPP
