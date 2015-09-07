#ifndef UUID_HPP
#define UUID_HPP

#include <Grafit/System/Types.hpp>
#include <Grafit/System/String.hpp>

namespace gf {
class Uuid {
public:
    Uuid(void);

    ~Uuid(void) noexcept;

    Uuid (const Uuid&) noexcept;

    Uuid& operator= (const Uuid&) noexcept;

    bool isNull(void) const noexcept;

    String toString(void) const;

    bool operator== (const Uuid&) const noexcept;
    bool operator!= (const Uuid&) const noexcept;

    const Uint8* getRawData(void) const { return m_uuid; }

private:
    Uint8 m_uuid[16];
};

}
#endif // UUID_HPP

