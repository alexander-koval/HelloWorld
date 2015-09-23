#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <Grafit/System/EmptyType.hpp>
#include <Grafit/System/NullType.hpp>
#include <Grafit/System/Assert.hpp>
#include <Grafit/System/Destructable.hpp>
#include <type_traits>
#include <functional>
#include <map>

namespace gf {

namespace priv {

template <typename ... Args> struct FactoryImpl;

template <typename AP, typename ID, typename ... Args>
struct FactoryImpl<AP, ID, Args...> : public Destructable {
    using ReturnType = AP;
    virtual ReturnType create(const ID& id, Args&& ...args) = 0;
};

}

template <typename AbstractProduct, typename IdentifierType, typename ... Args>
class Factory {
protected:
    using Impl = priv::FactoryImpl<AbstractProduct, IdentifierType, Args...>;
    using ProductCreator = std::function<typename Impl::ReturnType(Args...)>;

private:
    using ProductMap = std::map<IdentifierType, ProductCreator>;
    ProductMap m_associations;

public:
    using ReturnType = typename Impl::ReturnType;

    Factory() : m_associations() {}

    ~Factory() {}

    bool registrate(const IdentifierType& id, const ProductCreator& creator) {
        return m_associations.insert(
                    typename ProductMap::value_type(id, creator)).second != 0;
    }

    bool unregistrate(const IdentifierType& id) {
        return m_associations.erase(id) != 0;
    }

    bool isRegistered(const IdentifierType& id) {
        return m_associations.find(id) != m_associations.end();
    }

    ReturnType create(const IdentifierType& id, Args&& ...args) {
        typename ProductMap::iterator it = m_associations.find(id);
        GF_ASSERT(it != m_associations.end(), "Wrong type for creation", id);
        return (it->second)(std::forward(args)...);
    }
};

}


#endif // FACTORY_HPP
