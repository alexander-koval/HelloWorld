#version 330 core
smooth in vec4 v_smoothColor;
layout(location = 0) out vec4 v_fragColor;

void main(void) {
    v_fragColor = v_smoothColor;
}
