#ifndef EMPTYTYPE_HPP
#define EMPTYTYPE_HPP

namespace gf {
class EmptyType {};

inline bool operator==(const EmptyType&, const EmptyType&) {
    return true;
}

inline bool operator<(const EmptyType&, const EmptyType&) {
    return false;
}

inline bool operator>(const EmptyType&, const EmptyType&) {
    return false;
}

}

#endif // EMPTYTYPE_HPP
