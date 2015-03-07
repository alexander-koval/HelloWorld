#version 330 core
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec4 VertexColor;
smooth out vec4 SmoothColor;
uniform mat4 MVP;

void main(void) {
    SmoothColor = vec4(VertexColor);
    gl_Position = MVP * vec4(VertexPosition, 0, 1);
}
