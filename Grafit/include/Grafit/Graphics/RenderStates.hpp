#ifndef RENDERSTATES_HPP
#define RENDERSTATES_HPP

#include <Grafit/Graphics/BlendMode.hpp>
#include <Grafit/Graphics/Transform.hpp>


namespace gf {
class Shader;
class Texture;

class RenderStates {
public:
    RenderStates();

    RenderStates(const BlendMode& theBlendMode);

    RenderStates(const Transform& theTransform);

    RenderStates(const Texture* theTexture);

    RenderStates(Shader* theShader);

    RenderStates(const BlendMode& theBlendMode, const Transform& theTransform,
                 const Texture* theTexture, Shader* theShader);

    static const RenderStates Default; ///< Special instance holding the default render states

    BlendMode      blendMode; ///< Blending mode
    Transform      transform; ///< Transform
    const Texture* texture;   ///< Texture
    const Shader* shader;    ///< Shader
};

}

#endif // RENDERSTATES_HPP
