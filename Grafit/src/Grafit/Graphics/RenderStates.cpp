#include <Grafit/Graphics/RenderStates.hpp>
#include <cstddef>

namespace gf {
const RenderStates RenderStates::Default(BlendMode(
    BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha, BlendMode::Add,
    BlendMode::One, BlendMode::OneMinusSrcAlpha, BlendMode::Add));


RenderStates::RenderStates() :
blendMode(BlendAlpha),
transform(),
texture  (nullptr),
shader   (nullptr)
{
}

RenderStates::RenderStates(const Transform& theTransform) :
blendMode(BlendAlpha),
transform(theTransform),
texture  (nullptr),
shader   (nullptr)
{
}

RenderStates::RenderStates(const BlendMode& theBlendMode) :
blendMode(theBlendMode),
transform(),
texture  (nullptr),
shader   (nullptr)
{
}

RenderStates::RenderStates(const Texture* theTexture) :
blendMode(BlendAlpha),
transform(),
texture  (theTexture),
shader   (nullptr)
{
}

RenderStates::RenderStates(Shader* theShader) :
blendMode(BlendAlpha),
transform(),
texture  (nullptr),
shader   (theShader)
{
}

RenderStates::RenderStates(const BlendMode& theBlendMode, const Transform& theTransform,
                           const Texture* theTexture, Shader* theShader) :
blendMode(theBlendMode),
transform(theTransform),
texture  (theTexture),
shader   (theShader)
{
}

}
