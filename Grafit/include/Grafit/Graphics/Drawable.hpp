#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

namespace gf {
class Drawable {
public:

    virtual ~Drawable() {}

protected:

//    friend class RenderTarget;

    virtual void draw(RenderTarget& target, RenderStates states) const = 0;
};
}

#endif // DRAWABLE_HPP
