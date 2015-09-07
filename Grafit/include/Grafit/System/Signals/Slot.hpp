#ifndef SLOT_HPP
#define SLOT_HPP

namespace gf {
class Connection;
template <typename ... Args> class Slot;
template <typename R, typename ... Args>
class Slot<R(Args...)> {
public:
    using ResultType = R;
    using Fn = R(Args...);

    Slot(const std::function<R(Args...)>& listener, bool once = false, int priority = 0);

    void setListener(const std::function<R(Args...)>& listener) {
        m_listener = listener;
    }

    const std::function<R(Args...)>& getListener(void) const {
        return m_listener;
    }

    bool isOnce(void) const {
        return m_isOnce;
    }

    int getPriority(void) const {
        return m_priority;
    }

    void execute(Args&&... args) const;

protected:
    int m_priority;
    std::function<R(Args...)> m_listener;
    bool m_isEnabled;
    bool m_isOnce;
};

using Slot0 = Slot<void()>;
template <typename TValue> using Slot1 = Slot<void(TValue)>;
template <typename TValue1, typename TValue2> using Slot2 = Slot<void(TValue1, TValue2)>;
template <typename TValue1, typename TValue2, typename TValue3> using Slot3 = Slot<void(TValue1, TValue2, TValue3)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4> using Slot4 = Slot<void(TValue1, TValue2, TValue3, TValue4)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5> using Slot5 = Slot<void(TValue1, TValue2, TValue3, TValue4, TValue5)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6> using Slot6 = Slot<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7> using Slot7 = Slot<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7, typename TValue8> using Slot8 = Slot<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7, TValue8)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7, typename TValue8, typename TValue9> using Slot9 = Slot<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7, TValue8, TValue9)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7, typename TValue8, typename TValue9, typename TValue10> using Slot10 = Slot<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7, TValue8, TValue9, TValue10)>;

}

#include <Grafit/System/Signals/Slot.inl>
#endif // SLOT_HPP
