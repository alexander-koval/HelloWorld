#version 330 core
layout(location = 0) in vec3 a_vertex;
layout(location = 1) in vec3 a_color;
smooth out vec4 v_smoothColor;
uniform mat4 MVP;

void main(void) {
    v_smoothColor = vec4(a_color, 1);
    gl_Position = MVP * vec4(a_vertex, 1);
}
