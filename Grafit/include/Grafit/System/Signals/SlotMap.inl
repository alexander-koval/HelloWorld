#include <Grafit/System/Signals/SlotMap.hpp>

namespace gf {

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
typename SlotMap<TSlot, CompareType>::Iterator SlotMap<TSlot, CompareType>::end(void) {
    return SlotMap<TSlot, CompareType>::Iterator(m_groups.end(), m_groups.end());
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

template <typename TSlot, typename CompareType>
void SlotMap<TSlot, CompareType>::removeDisconnectedSlots(void) {
    GroupIterator group_it = m_groups.begin();
    while (group_it != m_groups.end()) {
        SlotPairIterator it = group_it->second.begin();
        while (it != group_it->second.end()) {
            if (it->first.connected()) ++it;
            else group_it->second.erase(it++);
        }
        if (isEmpty(group_it))
            m_groups.erase(group_it++);
        else
            ++group_it;
    }
}

}
