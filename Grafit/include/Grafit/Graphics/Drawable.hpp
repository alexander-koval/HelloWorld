#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <Grafit/Graphics/RenderStates.hpp>

namespace gf {
class RenderTarget;
class Drawable {
public:

    virtual ~Drawable() {}

protected:

    friend class RenderTarget;

    virtual void draw(const RenderTarget& target, RenderStates states) const = 0;
};
}

#endif // DRAWABLE_HPP
