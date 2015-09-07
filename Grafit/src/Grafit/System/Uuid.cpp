#include <Grafit/System/Uuid.hpp>
#include <limits>
#include <random>
#include <sstream>
#include <cstring>
#include <iostream>

namespace gf {
static const char hexDigits[] = "0123456789abcdef";

Uuid::Uuid(void) {
    std::default_random_engine eng((std::random_device())());
    std::uniform_int_distribution<int8_t> idis(0, 255);
    for (size_t i = 0; i < sizeof (m_uuid); ++i) {
        Uint8 v = idis(eng);
        m_uuid[i] = v;
    }

    m_uuid[6] = (m_uuid[6] & 0x0f) | 0x40;
    m_uuid[8] = (m_uuid[8] & 0x3f) | 0x80;
}

Uuid::~Uuid(void) noexcept {

}

Uuid::Uuid(const Uuid & other) noexcept {
    memcpy(m_uuid, other.m_uuid, sizeof(m_uuid));
}

Uuid& Uuid::operator =(const Uuid& other) noexcept {
    memcpy(m_uuid, other.m_uuid, sizeof(m_uuid));
    return *this;
}

bool Uuid::isNull(void) const noexcept {
    for (size_t i = 0; i < sizeof (m_uuid); ++i)
        if (m_uuid[i] != 0)
            return false;
    return true;
}

gf::String Uuid::toString() const {
    std::ostringstream os ;
    const unsigned char* data = static_cast<const unsigned char*>(&m_uuid[0]);
    for (size_t i = 0; i < sizeof(m_uuid); ++i) {
        const unsigned char nextByte = *data++;
        os << hexDigits[nextByte >> 4];
        os << hexDigits[nextByte & 0xf];
    }
    return gf::String(os.str());
}

bool Uuid::operator ==(const Uuid& other) const noexcept {
    return memcmp(m_uuid, other.m_uuid, sizeof(m_uuid)) == 0;
}

bool Uuid::operator !=(const Uuid& other) const noexcept {
    return !operator== (other);
}

}
