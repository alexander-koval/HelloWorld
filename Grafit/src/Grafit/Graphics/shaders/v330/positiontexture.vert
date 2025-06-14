#version 330 core

layout(location=0) in vec2 VertexPosition;
layout(location=1) in vec2 VertexTexCoord;
smooth out vec2 TexCoord;
uniform mat4 MVP;

void main(void)
{
    TexCoord = VertexTexCoord;
    gl_Position = MVP * vec4(VertexPosition, 0, 1);
}

