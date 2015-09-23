#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <Grafit/Graphics/RenderStates.hpp>
#include <Grafit/System/Destructable.hpp>

namespace gf {
class RenderTarget;
class Drawable : public Destructable {
public:
    friend class RenderTarget;

    virtual void draw(const RenderTarget& target, RenderStates states) const = 0;
};
}

#endif // DRAWABLE_HPP
