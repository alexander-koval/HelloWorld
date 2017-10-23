#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP

namespace gf {

template <typename T>
inline void smart_ptr_add_ref(T* p) {
    intrusive_ptr_add_ref(p);
}

template <typename T>
inline void smart_ptr_release(T* p) {
    intrusive_ptr_release(p);
}

template<typename T>
class SmartPtr {
public:
    using ValueType = T;
    using SelfType = SmartPtr<ValueType>;
    using Reference = T&;
    using Pointer = T*;
    using ConstReference = const T&;
    using ConstPointer = const T*;

public:
    SmartPtr(void);
    SmartPtr(Pointer data, bool add_ref = true);
    SmartPtr(const SelfType& that);
    SmartPtr(SelfType&& that);
    ~SmartPtr();

    SelfType& operator=(const SelfType& that);
    SelfType& operator=(T* rhs);

    bool operator==(const SelfType& that) const;
    bool operator!=(const SelfType& that) const;
    bool operator<(const SelfType& that) const;
    bool operator<=(const SelfType& that) const;
    bool operator>(const SelfType& that) const;
    bool operator>=(const SelfType& that) const;

    Pointer operator->(void);
    Pointer operator->(void) const;
    Reference operator*(void);
    Reference operator*(void) const;

    void reset(void);
    void reset(T* rhs);
    void reset(T* rhs, bool add_ref);

    T* get(void) const;
    T* detach(void);

    void swap(SmartPtr& other);

private:
    T* px;
};

template<typename T>
SmartPtr<T>::SmartPtr() : px(nullptr) {

}

template<typename T>
SmartPtr<T>::SmartPtr(SmartPtr<T>::Pointer data, bool add_ref) : px(data) {
    if (px != nullptr && add_ref) {
        smart_ptr_add_ref(px);
    }
}

template<typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>::SelfType& that) : px(that.px) {
    if (px != nullptr) {
        smart_ptr_add_ref(px);
    }
}

template<typename T>
SmartPtr<T>::SmartPtr(SmartPtr<T>::SelfType&& that) : px(that.px) {
    that.px = nullptr;
}

template<typename T>
SmartPtr<T>::~SmartPtr() {
    if (px != nullptr) {
        smart_ptr_release(px);
    }
}

template<typename T>
typename SmartPtr<T>::SelfType& SmartPtr<T>::operator=(const SmartPtr<T>::SelfType& that) {
    SelfType(that).swap(*this);
    return *this;
}

template<typename T>
typename SmartPtr<T>::SelfType& SmartPtr<T>::operator=(T* rhs) {
    sefl_type(rhs).swap(*this);
    return *this;
}

template<typename T>
bool SmartPtr<T>::operator==(const SmartPtr<T>::SelfType& that) const {
    return !(*this < that) && !(that < *this);
}

template<typename T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>::SelfType& that) const {
    return (*this < that) || (that < *this);
}

template<typename T>
bool SmartPtr<T>::operator<(const SmartPtr<T>::SelfType& that) const {
    return px < that.px;
}

template<typename T>
bool SmartPtr<T>::operator<=(const SmartPtr<T>::SelfType& that) const {
    return !(that < *this);
}

template<typename T>
bool SmartPtr<T>::operator>(const SmartPtr<T>::SelfType& that) const {
    return that < *this;
}

template<typename T>
bool SmartPtr<T>::operator>=(const SmartPtr<T>::SelfType& that) const {
    return !(*this < that);
}

template<typename T>
typename SmartPtr<T>::Pointer SmartPtr<T>::operator->() {
    return px;
}

template<typename T>
typename SmartPtr<T>::Pointer SmartPtr<T>::operator->() const {
    return px;
}

template<typename T>
typename SmartPtr<T>::Reference SmartPtr<T>::operator*() {
    return *px;
}

template<typename T>
typename SmartPtr<T>::Reference SmartPtr<T>::operator*() const {
    return *px;
}

template<typename T>
void SmartPtr<T>::reset() {
    SelfType().swap(*this);
}

template<typename T>
void SmartPtr<T>::reset(T* rhs) {
    SelfType(rhs).swap(*this);
}

template<typename T>
void SmartPtr<T>::reset(T* rhs, bool add_ref) {
    SelfType(rhs).swap(*this);
    if (add_ref) {
        smart_ptr_add_ref(px);
    }
}

template<typename T>
T* SmartPtr<T>::get() const {
    assert(px != nullptr);
    return px;
}

template<typename T>
T* SmartPtr<T>::detach() {
    SelfType ptr;
    ptr.swap(*this);
    return ptr.get();
}

template<typename T>
void SmartPtr<T>::swap(SmartPtr& other) {
    T* tmp = px;
    px = other.px;
    other.px = tmp;
}

}



#endif // SMART_PTR_HPP

