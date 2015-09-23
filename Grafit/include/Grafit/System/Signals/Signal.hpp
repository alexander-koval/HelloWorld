#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <map>
#include <queue>
#include <memory>
#include <functional>
#include <unordered_map>
#include <type_traits>
#include <Grafit/System/NonCopyable.hpp>
#include <Grafit/System/Signals/SlotMap.hpp>

namespace gf {

template <typename ... Args> class Slot;
template <typename ... Args> class Signal;
template <typename R, typename ... Args>
class Signal<R(Args...)> {
public:
    using Fn = R(Args...);
    using ResultType = R;

    Signal(void) : m_slotMap() {}

    Connection& connect(const std::function<R(Args...)>& listener, bool once = false, int priority = 0,
                        ConnectPosition pos = ConnectPosition::Back) {
        registerListener(listener, once, priority, pos);
    }


    virtual bool disconnect(const Connection& connection);

    virtual void disconnectAll(void) {
        m_slotMap.clear();
    }

    int numSlots(void) const {
        std::size_t count = 0;
        for (ConstIterator it = m_slotMap.begin(); it != m_slotMap.end(); ++it) {
            if (it->first.isConnected()) ++count;
        }
        return count;
    }

    void dispatch(Args&& ...args) {
        Iterator it = m_slotMap.begin();
        while (it != m_slotMap.end()) {
            if (it->first.isConnected()) {
                const Slot<R(Args...)>& slot = it->second;
                slot.execute(std::forward<Args>(args)...);
                if (slot.isOnce()) {
                    m_slotMap.erase(it++);
                    continue;
                }
            }
            ++it;
        }
    }

private:
    Connection& registerListener(const std::function<R(Args...)>& listener, bool once, int priority, ConnectPosition pos);

    static void disconnect(Signal<R(Args...)>* signal, const Connection& con) {
        if (signal) {
            signal->disconnect(con);
        }
    }

private:
    using SlotContainer = SlotMap<Slot<R(Args...)>>;
    using Iterator = typename SlotContainer::Iterator;
    using ConstIterator = typename SlotContainer::ConstIterator;

    SlotMap<Slot<R(Args...)>> m_slotMap;
};

using Signal0 = Signal<void()>;
template <typename TValue> using Signal1 = Signal<void(TValue)>;
template <typename TValue1, typename TValue2> using Signal2 = Signal<void(TValue1, TValue2)>;
template <typename TValue1, typename TValue2, typename TValue3> using Signal3 = Signal<void(TValue1, TValue2, TValue3)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4> using Signal4 = Signal<void(TValue1, TValue2, TValue3, TValue4)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5> using Signal5 = Signal<void(TValue1, TValue2, TValue3, TValue4, TValue5)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6> using Signal6 = Signal<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7> using Signal7 = Signal<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7, typename TValue8> using Signal8 = Signal<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7, TValue8)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7, typename TValue8, typename TValue9> using Signal9 = Signal<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7, TValue8, TValue9)>;
template <typename TValue1, typename TValue2, typename TValue3, typename TValue4, typename TValue5, typename TValue6, typename TValue7, typename TValue8, typename TValue9, typename TValue10> using Signal10 = Signal<void(TValue1, TValue2, TValue3, TValue4, TValue5, TValue6, TValue7, TValue8, TValue9, TValue10)>;

}

#include <Grafit/System/Signals/Signal.inl>

#endif // SIGNAL_HPP
