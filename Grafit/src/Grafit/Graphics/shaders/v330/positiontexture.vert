 #version 330 core

layout(location=0) in vec2 VertexPosition;
layout(location=1) in vec2 VertexTexCoord;
smooth out vec2 TexCoord;
//uniform mat4 Transform;
uniform mat4 MVP;

void main(void)
{
    TexCoord = VertexTexCoord;
//    vec4 position = Transform * vec4(VertexPosition - 1, 0, 1);
//    gl_Position = MVP * position;
    gl_Position = MVP * vec4(VertexPosition - 1, 0, 1);
//    gl_Position = MVP * Transform *  vec4(VertexPosition - 1, 0, 1);
}

