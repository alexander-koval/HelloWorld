#version 330 core

layout(location=0) in vec2 VertexPosition;
smooth out vec2 UV;
uniform mat4 MVP;

void main(void)
{
    gl_Position = MVP * vec4(VertexPosition * 2.0 - 1, 0, 1);
    UV = vec2(VertexPosition.x, 1 - VertexPosition.y);
}

