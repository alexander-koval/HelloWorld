#version 330 core

layout (location=0) out vec4 FragColor;
smooth in vec2 TexCoord;
uniform sampler2D TextureMap;

void main(void)
{
    FragColor = texture(TextureMap, TexCoord);
}

