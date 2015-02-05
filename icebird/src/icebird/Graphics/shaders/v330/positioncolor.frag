#version 330 core
smooth in vec4 SmoothColor;
layout(location = 0) out vec4 FragColor;

void main(void) {
    FragColor = SmoothColor;
}
