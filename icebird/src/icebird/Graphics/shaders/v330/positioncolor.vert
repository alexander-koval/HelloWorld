#version 330 core
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColor;
smooth out vec4 SmoothColor;
uniform mat4 MVP;

void main(void) {
    SmoothColor = vec4(VertexColor, 1);
    gl_Position = MVP * vec4(VertexPosition, 1);
}
