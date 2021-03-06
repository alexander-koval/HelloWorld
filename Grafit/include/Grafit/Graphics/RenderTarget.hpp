#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <Grafit/Graphics/Color.hpp>
#include <Grafit/Graphics/Geometry/Rect.hpp>
#include <Grafit/Graphics/View.hpp>
#include <Grafit/Graphics/Transform.hpp>
#include <Grafit/Graphics/BlendMode.hpp>
#include <Grafit/Graphics/RenderStates.hpp>
#include <Grafit/Graphics/PrimitiveType.hpp>
#include <Grafit/Graphics/Vertex.hpp>
#include <Grafit/System/NonCopyable.hpp>
#include <Grafit/System/Destructable.hpp>
#include <stack>


namespace gf {
class Drawable;
class VertexArray;

enum MatrixMode {
    MODELVIEW,
    PROJECTION,
    TEXTURE
};

class RenderTarget : public Destructable, NonCopyable {
public:

    virtual ~RenderTarget();

    void clear(const Color<Uint8>& color = Color<Uint8>(0, 0, 0, 255));

    void clear(const Color<float>& color = Color<float>(0.f, 0.f, 0.f, 1.f));

    void setView(const View& view);

    const View& getView() const;

    const View& getDefaultView() const;

    RectI getViewport(const View& view) const;

    Vector2F mapPixelToCoords(const Vector2I& point) const;

    Vector2F mapPixelToCoords(const Vector2I& point, const View& view) const;

    Vector2I mapCoordsToPixel(const Vector2F& point) const;

    Vector2I mapCoordsToPixel(const Vector2F& point, const View& view) const;

    void draw(const Drawable& drawable, const RenderStates& states = RenderStates::Default) const;

    void draw(const VertexArray& vertices, PrimitiveType type, const RenderStates& states = RenderStates::Default) const;

    void draw(const Vertex2<Vector2F, Vector2F>* vertices, unsigned int vertexCount,
              PrimitiveType type, const RenderStates& states = RenderStates::Default) const;

    virtual Vector2U getSize() const = 0;

    void pushMatrix(MatrixMode mode);

    void popMatrix(MatrixMode mode);

    void pushGLStates();

    void popGLStates();

    void resetGLStates() const;

protected:
    RenderTarget();

    void initialize();

private:
    void applyCurrentView() const;

    void applyBlendMode(const BlendMode& mode);

    void applyTransform(const Transform& transform) const;

    void applyTexture(const Texture* texture);

    void applyShader(const Shader* shader) const;

    virtual bool activate(bool active) const = 0;

    struct StatesCache {
        enum {VertexCacheSize = 4};

        bool      glStatesSet;    ///< Are our internal GL states set yet?
        mutable bool      viewChanged;    ///< Has the current view changed since last draw?
        BlendMode lastBlendMode;  ///< Cached blending mode
        Uint64    lastTextureId;  ///< Cached texture
    };

    View        m_defaultView; ///< Default view
    View        m_view;        ///< Current view
    StatesCache m_cache;       ///< Render states cache

    mutable std::stack<Mat4F> m_modelViewStack;
    mutable std::stack<Mat4F> m_projectionStack;
    mutable std::stack<Mat4F> m_textureStack;
};

}

#endif // RENDERTARGET_HPP
