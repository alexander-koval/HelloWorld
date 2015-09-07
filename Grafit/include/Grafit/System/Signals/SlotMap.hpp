#ifndef SLOTMAP
#define SLOTMAP

#include <memory>
#include <list>
#include <map>
#include <iterator>

namespace gf {
class Connection;
template <typename TSlot, typename CompareType> class SlotMap;

enum class ConnectPosition { Back, Front };
class StoredGroup {
public:
    enum StorageKind { Empty, Front, Back, Group };

    StoredGroup(StorageKind kind = StorageKind::Empty) : m_kind(kind), m_group() {}

    template <typename T>
    StoredGroup(const T& group) : m_kind(StorageKind::Group), m_group(new T(group)) {}

    bool isFront(void) const { return m_kind == StorageKind::Front; }

    bool isBack(void) const { return m_kind == StorageKind::Back; }

    bool isEmpty(void) const { return m_kind == StorageKind::Empty; }

    void* get(void) const { return m_group.get(); }

private:
    StorageKind m_kind;
    std::shared_ptr<void> m_group;
};

template <typename TSlot> using ConSlotPair = std::pair<Connection, TSlot>;

template <typename Compare, typename Key>
class GroupBridgeCompare {
public:
    using ResultType = bool;
    using FirstArgumentType = const StoredGroup&;
    using SecondArgumentType = const StoredGroup&;

    GroupBridgeCompare(void) : m_comp() {}

    GroupBridgeCompare(const Compare& comp) : m_comp(comp) {}

    bool operator()(const StoredGroup& k1, const StoredGroup& k2) const {
        if (k1.isFront()) return !k2.isFront();
        if (k1.isBack()) return false;
        if (k2.isFront()) return false;
        if (k2.isBack()) return true;

        return m_comp(*static_cast<Key*>(k1.get()), *static_cast<Key*>(k2.get()));
    }

private:
    Compare m_comp;
};

template <typename TSlot, typename CompareType>
class SlotIterator : public std::iterator<std::forward_iterator_tag,
                                          ConSlotPair<TSlot>,
                                          std::ptrdiff_t,
                                          ConSlotPair<TSlot>*,
                                          ConSlotPair<TSlot>&> {
    using Base = std::iterator<std::forward_iterator_tag,
                               ConSlotPair<TSlot>,
                               std::ptrdiff_t,
                               ConSlotPair<TSlot>*,
                               ConSlotPair<TSlot>&>;
    using DifferenceType = typename Base::difference_type;
    using IteratorCategory = typename Base::iterator_category;
    using ValueType = typename Base::value_type;
    using Poiner = typename Base::pointer;
    using Reference = typename Base::reference;

    using GroupList = std::list<ConSlotPair<TSlot>>;
    using SlotPairIterator = typename GroupList::iterator;
    using SlotContainerType = std::map<StoredGroup, GroupList, CompareType>;
    using GroupIterator = typename SlotContainerType::iterator;
    using ConstGroupIterator = typename SlotContainerType::const_iterator;

public:
    SlotIterator() : m_isAssigned(false) {}

    SlotIterator(const SlotIterator& other)
        : m_group(other.m_group)
        , m_groupLast(other.m_groupLast)
        , m_isAssigned(other.m_isAssigned) {
        if (m_isAssigned) m_slot = other.m_slot;
    }

    SlotIterator& operator =(const SlotIterator& other) {
        m_isAssigned = other.m_isAssigned;
        m_group = other.m_group;
        m_groupLast = other.m_groupLast;
        if (m_isAssigned) m_slot = other.m_slot;
        return *this;
    }

    Reference operator *() const {
        return *m_slot;
    }

    Poiner operator ->() const {
        return &(operator*());
    }

    SlotIterator& operator ++() {
        ++m_slot;
        if (m_slot == m_group->second.end()) {
            ++m_group;
            initNextGroup();
        }
        return *this;
    }

    SlotIterator operator ++(int) {
        SlotIterator tmp = *this;
        ++m_slot;
        if (m_slot == m_group->second.end()) {
            ++m_group;
            initNextGroup();
        }
        return tmp;
    }

private:
    SlotIterator(GroupIterator group_iterator, GroupIterator last)
        : m_group(group_iterator), m_groupLast(last), m_isAssigned(false) {
        initNextGroup();
    }

    SlotIterator(GroupIterator group_iterator, GroupIterator last, SlotPairIterator slot)
        : m_group(group_iterator), m_groupLast(last), m_slot(slot), m_isAssigned(true) { }

    void initNextGroup(void) {
        while (m_group != m_groupLast && m_group->second.empty()) ++m_group;
        if (m_group != m_groupLast) {
            m_slot = m_group->second.begin();
            m_isAssigned = true;
        }
    }

private:
    friend class SlotMap<TSlot, CompareType>;
    template <typename Slot, typename Compare>
    friend bool operator == (const SlotIterator<Slot, Compare>& x, const SlotIterator<Slot, Compare>& y);
    template <typename Slot, typename Compare>
    friend bool operator != (const SlotIterator<Slot, Compare>& x, const SlotIterator<Slot, Compare>& y);
    GroupIterator m_group;
    GroupIterator m_groupLast;
    SlotPairIterator m_slot;
    bool m_isAssigned;
};

template<typename TSlot, typename CompareType>
inline bool operator ==(const SlotIterator<TSlot, CompareType>& x, const SlotIterator<TSlot, CompareType>& y) {
    return (x.m_group == y.m_group && (x.m_group == x.m_groupLast || x.m_slot == y.m_slot));
}

template<typename TSlot, typename CompareType>
inline bool operator !=(const SlotIterator<TSlot, CompareType>& x, const SlotIterator<TSlot, CompareType>& y)
  { return !(x == y); }

template <typename TSlot, typename CompareType = GroupBridgeCompare<std::less<int>, int>>
class SlotMap {
public:
    using Iterator = SlotIterator<TSlot, CompareType>;

    SlotMap();

    void clear(void);

    Iterator begin(void);

    Iterator end(void);

    Iterator insert(const StoredGroup& name, const Connection& con, const TSlot& slot, ConnectPosition at);

    void disconnect(const StoredGroup& name);

    void erase(Iterator it);

    void removeDisconnectedSlots(void);

private:
    using GroupList = std::list<ConSlotPair<TSlot>>;
    using SlotPairIterator = typename GroupList::iterator;
    using SlotContainerType = std::map<StoredGroup, GroupList, CompareType>;
    using GroupIterator = typename SlotContainerType::iterator;
    using ConstGroupIterator = typename SlotContainerType::const_iterator;

    bool isEmpty(ConstGroupIterator group) const {
        return (m_groups->second.empty() && group != m_groups.begin() && m_groups != m_back);
    }

    SlotContainerType m_groups;
    GroupIterator m_back;
};

}

#include <Grafit/System/Signals/SlotMap.inl>

#endif // SLOTMAP

