#include <Grafit/Graphics/RenderTarget.hpp>
#include <Grafit/Graphics/Drawable.hpp>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/Texture.hpp>
#include <Grafit/Graphics/VertexArray.hpp>
#include <Grafit/System/Assert.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stack>

namespace {
    Uint32 factorToGlConstant(gf::BlendMode::Factor blendFactor) {
        switch (blendFactor) {
            case gf::BlendMode::Zero:             return GL_ZERO;
            case gf::BlendMode::One:              return GL_ONE;
            case gf::BlendMode::SrcColor:         return GL_SRC_COLOR;
            case gf::BlendMode::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
            case gf::BlendMode::DstColor:         return GL_DST_COLOR;
            case gf::BlendMode::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
            case gf::BlendMode::SrcAlpha:         return GL_SRC_ALPHA;
            case gf::BlendMode::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
            case gf::BlendMode::DstAlpha:         return GL_DST_ALPHA;
            case gf::BlendMode::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
        }
    }

    Uint32 equationToGlConstant(gf::BlendMode::Equation blendEquation) {
        switch (blendEquation) {
            case gf::BlendMode::Add:             return GL_FUNC_ADD;
            case gf::BlendMode::Subtract:        return GL_FUNC_SUBTRACT;
        }
    }
}


namespace gf {

RenderTarget::RenderTarget() :
m_defaultView(),
m_view       (),
m_cache      () {
    m_cache.glStatesSet = false;
    resetGLStates();
}

RenderTarget::~RenderTarget() {

}

void RenderTarget::clear(const Color<Uint8>& color) {
    if (activate(true)) {
        applyTexture(nullptr);

        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
        GL_CHECK(glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f));
    }
}

void RenderTarget::clear(const Color<float> &color) {
    if (activate(true)) {
         applyTexture(nullptr);

        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
        GL_CHECK(glClearColor(color.r, color.g, color.b, color.a));
    }
}

void RenderTarget::setView(const View& view) {
    m_view = view;
    m_cache.viewChanged = true;
}


const View& RenderTarget::getView() const {
    return m_view;
}

const View& RenderTarget::getDefaultView() const {
    return m_defaultView;
}

RectI RenderTarget::getViewport(const View& view) const {
    float width  = static_cast<float>(getSize().x);
    float height = static_cast<float>(getSize().y);
    const RectF& viewport = view.getViewport();

    return RectI(static_cast<int>(0.5f + width  * viewport.left),
                   static_cast<int>(0.5f + height * viewport.top),
                   static_cast<int>(0.5f + width  * viewport.width),
                   static_cast<int>(0.5f + height * viewport.height));
}


Vector2F RenderTarget::mapPixelToCoords(const Vector2I& point) const {
    return mapPixelToCoords(point, getView());
}

Vector2F RenderTarget::mapPixelToCoords(const Vector2I& point, const View& view) const {
    // First, convert from viewport coordinates to homogeneous coordinates
    Vector2F normalized;
    RectI viewport = getViewport(view);
    normalized.x = -1.f + 2.f * (point.x - viewport.left) / viewport.width;
    normalized.y =  1.f - 2.f * (point.y - viewport.top)  / viewport.height;

    // Then transform by the inverse of the view matrix
    return view.getInverseTransform().transformPoint(normalized);
}

Vector2I RenderTarget::mapCoordsToPixel(const Vector2F& point) const {
    return mapCoordsToPixel(point, getView());
}

Vector2I RenderTarget::mapCoordsToPixel(const Vector2F& point, const View& view) const {
    // First, transform the point by the view matrix
    Vector2F normalized = view.getTransform().transformPoint(point);

    // Then convert to viewport coordinates
    Vector2I pixel;
    RectI viewport = getViewport(view);
    pixel.x = static_cast<int>(( normalized.x + 1.f) / 2.f * viewport.width  + viewport.left);
    pixel.y = static_cast<int>((-normalized.y + 1.f) / 2.f * viewport.height + viewport.top);

    return pixel;
}


////////////////////////////////////////////////////////////
void RenderTarget::draw(const Drawable& drawable, const RenderStates& states) const {
    drawable.draw(*this, states);
}

void RenderTarget::draw(const VertexArray& vertices, PrimitiveType type, const RenderStates& states) const {
    if (activate(true)) {
        const Shader* shader = states.shader;
        const Texture* texture = states.texture;
        Transform transform = states.transform;
        applyTransform(transform);
        applyCurrentView();
//        Uint64 textureId = states.texture ? states.texture->m_textureID : 0;
//        if (textureId != m_cache.lastTextureId)
//        applyTexture(texture);
        applyShader(shader);
        vertices.use();
//        Mat4F mvpView = m_projectionStack.top() * m_modelViewStack.top() * m_textureStack.top();
        Mat4F mvpView = /*m_textureStack.top() * */m_modelViewStack.top() * m_projectionStack.top();
        GF_ASSERT(shader != nullptr, "Unitialized shader pointer", nullptr);
        shader->setUniform("TextureMap", *texture);
        shader->setUniform("MVP", mvpView);
//        shader->setParameter<Shader::Uniform>("Time", .1f);
//        shader->setParameter<Shader::Uniform>("TextureSize", texture->getSize().x, texture->getSize().y);
        GL_CHECK(glDrawElements(type,
                                vertices.getIndexBuffer().getNumIndices(),
                                GL_UNSIGNED_SHORT, nullptr));
        vertices.unuse();
        applyShader(nullptr);
    }
    resetGLStates();
}

////////////////////////////////////////////////////////////
void RenderTarget::draw(const Vertex2<Vector2F, Vector2F>* vertices, unsigned int vertexCount,
                        PrimitiveType type, const RenderStates& states) const {
    // Nothing to draw?
//    if (!vertices || (vertexCount == 0))
//        return;

//    // GL_QUADS is unavailable on OpenGL ES
//    #ifdef OPENGL_ES
//        if (type == Quads)
//        {
//            err() << "gf::Quads primitive type is not supported on OpenGL ES platforms, drawing skipped" << std::endl;
//            return;
//        }
//        #define GL_QUADS 0
//    #endif

//    if (activate(true))
//    {
//        // First set the persistent OpenGL states if it's the very first call
//        if (!m_cache.glStatesSet)
//            resetGLStates();

//        // Check if the vertex count is low enough so that we can pre-transform them
//        bool useVertexCache = (vertexCount <= StatesCache::VertexCacheSize);
//        if (useVertexCache)
//        {
//            // Pre-transform the vertices and store them into the vertex cache
//            for (unsigned int i = 0; i < vertexCount; ++i)
//            {
//                Vertex& vertex = m_cache.vertexCache[i];
//                vertex.position = states.transform * vertices[i].position;
//                vertex.color = vertices[i].color;
//                vertex.texCoords = vertices[i].texCoords;
//            }

//            // Since vertices are transformed, we must use an identity transform to render them
//            if (!m_cache.useVertexCache)
//                applyTransform(Transform::Identity);
//        }
//        else
//        {
//            applyTransform(states.transform);
//        }

//        // Apply the view
//        if (m_cache.viewChanged)
//            applyCurrentView();

//        // Apply the blend mode
//        if (states.blendMode != m_cache.lastBlendMode)
//            applyBlendMode(states.blendMode);

//        // Apply the texture
//        Uint64 textureId = states.texture ? states.texture->m_cacheId : 0;
//        if (textureId != m_cache.lastTextureId)
//            applyTexture(states.texture);

//        // Apply the shader
//        if (states.shader)
//            applyShader(states.shader);

//        // If we pre-transform the vertices, we must use our internal vertex cache
//        if (useVertexCache)
//        {
//            // ... and if we already used it previously, we don't need to set the pointers again
//            if (!m_cache.useVertexCache)
//                vertices = m_cache.vertexCache;
//            else
//                vertices = nullptr;
//        }

//        // Setup the pointers to the vertices' components
//        if (vertices)
//        {
//            const char* data = reinterpret_cast<const char*>(vertices);
//            glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex), data + 0));
//            glCheck(glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), data + 8));
//            glCheck(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), data + 12));
//        }

//        // Find the OpenGL primitive type
//        static const GLenum modes[] = {GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES,
//                                       GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS};
//        GLenum mode = modes[type];

//        // Draw the primitives
//        glCheck(glDrawArrays(mode, 0, vertexCount));

//        // Unbind the shader, if any
//        if (states.shader)
//            applyShader(nullptr);

//        // Update the cache
//        m_cache.useVertexCache = useVertexCache;
//    }
}

void RenderTarget::popMatrix(MatrixMode mode) {
    if (mode == MatrixMode::MODELVIEW) {
        m_modelViewStack.pop();
    } else if (mode == MatrixMode::PROJECTION) {
        m_projectionStack.pop();
    } else if (mode == MatrixMode::TEXTURE) {
        m_textureStack.pop();
    } else {
        GF_ASSERT(false, "Unresolvable MatrixMode", GF_STRINGIFY(MatrixMode));
    }
}

void RenderTarget::pushMatrix(MatrixMode mode) {
    if (mode == MatrixMode::MODELVIEW) {
        m_modelViewStack.push(m_modelViewStack.top());
    } else if (mode == MatrixMode::PROJECTION) {
        m_projectionStack.push(m_projectionStack.top());
    } else if (mode == MatrixMode::TEXTURE) {
        m_textureStack.push(m_textureStack.top());
    } else {
        GF_ASSERT(false, "Unresolvable MatrixMode", GF_STRINGIFY(MatrixMode));
    }
}

void RenderTarget::pushGLStates() {
    if (activate(true)) {
        pushMatrix(PROJECTION);
        pushMatrix(MODELVIEW);
        pushMatrix(TEXTURE);
    }
}

void RenderTarget::popGLStates() {
    if (activate(true)) {
        popMatrix(PROJECTION);
        popMatrix(MODELVIEW);
        popMatrix(TEXTURE);
    }
}

void RenderTarget::resetGLStates() const {
    while (!m_modelViewStack.empty()) {
        m_modelViewStack.pop();
    }
    while (!m_projectionStack.empty()) {
        m_projectionStack.pop();
    }
    while (!m_textureStack.empty()) {
        m_textureStack.pop();
    }
    m_modelViewStack.push(Mat4F::IDENTITY);
    m_projectionStack.push(Mat4F::IDENTITY);
    m_textureStack.push(Mat4F::IDENTITY);
}

void RenderTarget::initialize() {
    // Setup the default and current views
    m_defaultView.reset(RectF(0, 0, static_cast<float>(getSize().x), static_cast<float>(getSize().y)));
    m_view = m_defaultView;

    // Set GL states only on first draw, so that we don't pollute user's states
    m_cache.glStatesSet = false;
}

void RenderTarget::applyCurrentView() const {
    // Set the viewport
    RectI viewport = getViewport(m_view);
    int top = getSize().y - (viewport.top + viewport.height);
    GL_CHECK(glViewport(viewport.left, top, viewport.width, viewport.height));

    m_projectionStack.push(m_view.getTransform().getMatrix());

    m_cache.viewChanged = false;
}

void RenderTarget::applyBlendMode(const BlendMode& mode) {
    if (GL_EXT_blend_func_separate) {
        GL_CHECK(glBlendFuncSeparate(
            factorToGlConstant(mode.colorSrcFactor), factorToGlConstant(mode.colorDstFactor),
            factorToGlConstant(mode.alphaSrcFactor), factorToGlConstant(mode.alphaDstFactor)));
    }
    else {
        GL_CHECK(glBlendFunc(
            factorToGlConstant(mode.colorSrcFactor),
            factorToGlConstant(mode.colorDstFactor)));
    }

    if (GL_EXT_blend_equation_separate) {
        GL_CHECK(glBlendEquationSeparate(
            equationToGlConstant(mode.colorEquation),
            equationToGlConstant(mode.alphaEquation)));
    }
    else {
        GL_CHECK(glBlendEquation(equationToGlConstant(mode.colorEquation)));
    }

    m_cache.lastBlendMode = mode;
}

void RenderTarget::applyTransform(const Transform& transform) const {
    m_modelViewStack.push(transform.getMatrix());
}

void RenderTarget::applyTexture(const Texture* texture) {
    Texture::bind(texture/*, Texture::Pixels*/);

//    m_cache.lastTextureId = texture ? texture->m_textureID : 0;
}

void RenderTarget::applyShader(const Shader* shader) const {
//    Shader::use();
    Shader::bind(shader);
}

}
