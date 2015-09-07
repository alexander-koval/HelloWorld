#ifndef CONDITIONAL_HPP
#define CONDITIONAL_HPP

namespace gf {

template <bool Cond, typename ThenPart, typename ElsePart>
struct if_then_else;

template <typename ThenPart, typename ElsePart>
struct if_then_else<true, ThenPart, ElsePart> {
    typedef ThenPart result;
};

template <typename ThenPart, typename ElsePart>
struct if_then_else<false, ThenPart, ElsePart> {
    typedef ElsePart result;
};

} // namespace gf

#endif // CONDITIONAL_HPP

