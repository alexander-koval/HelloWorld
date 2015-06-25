#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <map>
#include <queue>


namespace gf {
class Slot0;

template <typename TSlot, typename TListener>
class Signal {
public:
    Signal();

    TSlot* add(TListener listener, bool once = false, int priority = 0);

    TSlot* remove(TListener listener);

    void removeAll(void);

private:
    TSlot* registerListener(TListener listener, bool once = false, int priority = 0);

    bool isRegistrationPossible(TListener listener, bool once = false);

    TSlot* createSlot(TListener listener, bool once = false, int priority = 0);

    int numListeners(void) const;

private:
    bool m_isPriorityBased;
    std::priority_queue<TSlot*> m_slots;
    std::map<TListener, TSlot*> m_slotsMap;
};

template <typename TSlot, typename TListener>
Signal<TSlot, TListener>::Signal()
    : m_isPriorityBased(false) {

}

template <typename TSlot, typename TListener>
TSlot* Signal<TSlot, TListener>::add(TListener listener, bool once/*= false*/, int priority/* = 0*/) {
    return registerListener(listener, once, priority);
}

template <typename TSlot, typename TListener>
TSlot* Signal<TSlot, TListener>::registerListener(TListener listener, bool once, int priority) {
    TSlot* newSlot = nullptr;
    if (isRegistrationPossible(listener, once)) {
        newSlot = createSlot(listener, once, priority);
        if (!m_isPriorityBased && priority != 0) m_isPriorityBased = true;
        m_slots.push(newSlot);
        m_slotsMap.insert(std::make_pair(listener, newSlot));
    } else {
        typename std::map<TListener, TSlot*>::iterator it = m_slotsMap.find(listener);
        if (it != m_slotsMap.end()) {
            newSlot = it->second;
        }
    }
    return newSlot;
}

template <typename TSlot, typename TListener>
bool Signal<TSlot, TListener>::isRegistrationPossible(TListener listener, bool once) {
    return false;
}

template <typename TSlot, typename TListener>
TSlot* Signal<TSlot, TListener>::createSlot(TListener listener, bool once/* = false*/, int priority/* = 0*/) {
    return new TSlot();
}

class Signal0 : public Signal<gf::Slot0, void(*)()> {

};

}

#endif // SIGNAL_HPP
