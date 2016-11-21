#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP

namespace gf {
namespace memory {

template<typename T>
class smart_ptr {
public:
    using value_type = T;
    using self_type = smart_ptr<value_type>;
    using reference = T&;
    using pointer = T*;
    using const_reference = const T&;
    using const_pointer = const T*;

public:
    smart_ptr(void);
    smart_ptr(pointer data);
    smart_ptr(const self_type& that);

    bool operator==(const self_type& that) const;
    bool operator!=(const self_type& that) const;
    bool operator<(const self_type& that) const;
    bool operator<=(const self_type& that) const;
    bool operator>(const self_type& that) const;
    bool operator>=(const self_type& that) const;

    pointer operator->(void);
    pointer operator->(void) const;
    reference operator*(void);
    reference operator*(void) const;

    void reset(void);
    void reset(T* rhs);
    void reset(T* rhs, bool add_ref);

    T* get(void) const;
    T* detach(void);

    void swap(smart_ptr& other);

private:
    T* px;
};

template <typename T>
class smart_ref_counter {

private:
    using counter_type = unsigned int;
    mutable counter_type m_ref_counter;

public:
    smart_ref_counter(void);

    smart_ref_counter(const smart_ref_counter& that);

    smart_ref_counter& operator=(const smart_ref_counter& that);

    unsigned int use_count(void) const;

    static void increment(unsigned int& counter);

    static void decrement(unsigned int& counter);

protected:
    friend void smart_ptr_add_ref<T>(const smart_ref_counter<T>* p);
    friend void smart_ptr_release<T>(const smart_ref_counter<T>* p);
};

template <typename T>
inline void smart_ptr_add_ref(const smart_ref_counter<T>* p) {

}

template <typename T>
inline void smart_ptr_release(const smart_ref_counter<T>* p) {

}

}
}



#endif // SMART_PTR_HPP

