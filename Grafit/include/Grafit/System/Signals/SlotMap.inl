#include <Grafit/System/Signals/SlotMap.hpp>

namespace gf {

template <typename TSlot, typename CompareType>
SlotIterator<TSlot, CompareType>::SlotIterator(const SlotIterator &other)
    : m_group(other.m_group)
    , m_groupLast(other.m_groupLast)
    , m_isAssigned(other.m_isAssigned) {
    if (m_isAssigned) m_slot = other.m_slot;
}

template <typename TSlot, typename CompareType>
SlotIterator<TSlot, CompareType>& SlotIterator<TSlot, CompareType>::operator=(const SlotIterator& other) {
    m_isAssigned = other.m_isAssigned;
    m_group = other.m_group;
    m_groupLast = other.m_groupLast;
    if (m_isAssigned) m_slot = other.m_slot;
    return *this;
}

template <typename TSlot, typename CompareType>
typename SlotIterator<TSlot, CompareType>::Reference SlotIterator<TSlot, CompareType>::operator*() const {
    return *m_slot;
}

template <typename TSlot, typename CompareType>
SlotIterator<TSlot, CompareType>& SlotIterator<TSlot, CompareType>::operator++(void) {
    ++m_slot;
    if (m_slot == m_group->second.end()) {
        ++m_group;
        initNextGroup();
    }
    return *this;
}

template <typename TSlot, typename CompareType>
SlotIterator<TSlot, CompareType> SlotIterator<TSlot, CompareType>::operator++(int) {
    SlotIterator tmp = *this;
    ++m_slot;
    if (m_slot == m_group->second.end()) {
        ++m_group;
        initNextGroup();
    }
    return tmp;
}

template <typename TSlot, typename CompareType>
typename SlotIterator<TSlot, CompareType>::Pointer SlotIterator<TSlot, CompareType>::operator->() const {
    return &(operator*());
}

template <typename TSlot, typename CompareType>
ConstSlotIterator<TSlot, CompareType>::ConstSlotIterator(const ConstSlotIterator &other)
    : m_group(other.m_group)
    , m_groupLast(other.m_groupLast)
    , m_isAssigned(other.m_isAssigned) {
    if (m_isAssigned) m_slot = other.m_slot;
}

template <typename TSlot, typename CompareType>
ConstSlotIterator<TSlot, CompareType>& ConstSlotIterator<TSlot, CompareType>::operator=(const ConstSlotIterator& other) {
    m_isAssigned = other.m_isAssigned;
    m_group = other.m_group;
    m_groupLast = other.m_groupLast;
    if (m_isAssigned) m_slot = other.m_slot;
    return *this;
}

template <typename TSlot, typename CompareType>
typename ConstSlotIterator<TSlot, CompareType>::Reference ConstSlotIterator<TSlot, CompareType>::operator*() const {
    return *m_slot;
}

template <typename TSlot, typename CompareType>
ConstSlotIterator<TSlot, CompareType>& ConstSlotIterator<TSlot, CompareType>::operator++(void) {
    ++m_slot;
    if (m_slot == m_group->second.end()) {
        ++m_group;
        initNextGroup();
    }
    return *this;
}

template <typename TSlot, typename CompareType>
ConstSlotIterator<TSlot, CompareType> ConstSlotIterator<TSlot, CompareType>::operator++(int) {
    ConstSlotIterator tmp = *this;
    ++m_slot;
    if (m_slot == m_group->second.end()) {
        ++m_group;
        initNextGroup();
    }
    return tmp;
}

template <typename TSlot, typename CompareType>
typename ConstSlotIterator<TSlot, CompareType>::Pointer ConstSlotIterator<TSlot, CompareType>::operator->() const {
    return &(operator*());
}


template <typename TSlot, typename CompareType>
SlotMap<TSlot, CompareType>::SlotMap() {
    clear();
}

template <typename TSlot, typename CompareType>
void SlotMap<TSlot, CompareType>::clear(void) {
    m_groups.clear();
    m_groups[StoredGroup(StoredGroup::Front)];
    m_groups[StoredGroup(StoredGroup::Back)];
    m_back = m_groups.end();
    --m_back;
}

template <typename TSlot, typename CompareType>
typename SlotMap<TSlot, CompareType>::Iterator SlotMap<TSlot, CompareType>::begin(void) {
    return SlotMap<TSlot, CompareType>::Iterator(m_groups.begin(), m_groups.end());
}

template <typename TSlot, typename CompareType>
typename SlotMap<TSlot, CompareType>::ConstIterator SlotMap<TSlot, CompareType>::begin(void) const {
    return SlotMap<TSlot, CompareType>::ConstIterator(m_groups.begin(), m_groups.end());
}

template <typename TSlot, typename CompareType>
typename SlotMap<TSlot, CompareType>::Iterator SlotMap<TSlot, CompareType>::end(void) {
    return SlotMap<TSlot, CompareType>::Iterator(m_groups.end(), m_groups.end());
}

template <typename TSlot, typename CompareType>
typename SlotMap<TSlot, CompareType>::ConstIterator SlotMap<TSlot, CompareType>::end(void) const {
    return SlotMap<TSlot, CompareType>::ConstIterator(m_groups.end(), m_groups.end());
}


template <typename TSlot, typename CompareType>
typename SlotMap<TSlot, CompareType>::Iterator SlotMap<TSlot, CompareType>::insert(const StoredGroup& name,
                                                         const gf::Connection& con,
                                                         const TSlot& slot, ConnectPosition at) {
    GroupIterator group_it;
    if (name.isEmpty()) {
        switch (at) {
        case ConnectPosition::Front:
            group_it = m_groups.begin();
            break;
        case ConnectPosition::Back:
            group_it = m_back;
            break;
        }
    } else {
        group_it = m_groups.find(name);
        if (group_it == m_groups.end()) {
            typename SlotContainerType::value_type v(name, GroupList());
            group_it = m_groups.insert(v).first;
        }
    }
    Iterator it;
    it.m_group = group_it;
    it.m_groupLast = m_groups.end();

    switch (at) {
    case ConnectPosition::Back:
        group_it->second.push_back(std::make_pair(con, slot));
        it.m_slot = group_it->second.end();
        it.m_isAssigned = true;
        --(it.m_slot);
        break;

    case ConnectPosition::Front:
        group_it->second.push_front(std::make_pair(con, slot));
        it.m_slot = group_it->second.begin();
        it.m_isAssigned = true;
        break;
    }
    return it;
}

template <typename TSlot, typename CompareType>
void SlotMap<TSlot, CompareType>::disconnect(const StoredGroup& name) {
    GroupIterator group_it = m_groups.find(name);
    if (group_it != m_groups.end()) {
        SlotPairIterator it = group_it->second.begin();
        while (it != group_it->second.end()) {
            SlotPairIterator next_it = it;
            ++next_it;
            it->first.disconnect();
            it = next_it;
        }
        m_groups.erase(group_it);
    }
}

template <typename TSlot, typename CompareType>
void SlotMap<TSlot, CompareType>::erase(Iterator pos) {
    pos.m_slot->first.disconnect();
    pos.m_group->second.erase(pos.m_slot);
}

}
