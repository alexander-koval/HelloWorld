#version 330 core

layout (location=0) out vec4 FragColor;
smooth in vec2 TexCoord;
uniform sampler2D TextureMap;

//vec4 dither2x2(vec2 position, vec4 color);
void main(void)
{
//    vec4 color = texture(TextureMap, TexCoord);
//    float brightness = luma(color);
//    FragColor = vec4(vec3(brightness), 1.0);
//    FragColor = dither2x2(gl_FragCoord.xy, color);
    FragColor = texture2D(TextureMap, TexCoord);// * vec4(0.0, 0.0, 1.0, 1.0);
}

