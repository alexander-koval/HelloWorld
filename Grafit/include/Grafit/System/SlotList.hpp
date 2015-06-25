#ifndef SLOTLIST_HPP
#define SLOTLIST_HPP


namespace gf {

template <typename TSlot, typename TListener>
class SlotList {
public:
    SlotList(TSlot& head, SlotList<TSlot, TListener>& tail);

    SlotList& prepend(TSlot& slot);

    SlotList& append(TSlot& slot);

    SlotList& inserWithPriority(TSlot& slot);

    SlotList& filterNot(TListener& listener);

    bool contains(TListener& listener);

    TSlot& find(TListener& listener);

private:
    TSlot& m_head;
    SlotList<TSlot&, TListener&> m_tail;
    bool m_isEmpty;
};


template <typename TSlot, typename TListener>
SlotList<TSlot, TListener>::SlotList(TSlot& head, SlotList<TSlot, TListener>& tail) {
    m_isEmpty = true;

}

}

#endif // SLOTLIST_HPP
