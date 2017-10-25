#version 330 core

layout (location=0) out vec4 FragColor;
smooth in vec2 TexCoord;
uniform sampler2D TextureMap;
//uniform vec2 TextureSize;

//vec4 dither2x2(vec2 position, vec4 color);
vec4 dither4x4(vec2 position, vec4 color);
//vec4 dither8x8(vec2 position, vec4 color);
//vec4 water2d(vec2 position, vec4 color);
//float luma(vec4 color) {
//  return dot(color.rgb, vec3(0.299, 0.587, 0.114));
//}

void main(void)
{
    /** TWIRL */
//    vec2 uv = TexCoord - 0.5;
//    float angle = atan(uv.y, uv.x);
//    float radius = length(uv);
//    angle += radius * 5;
//    vec2 shifted = radius* vec2(cos(angle), sin(angle));
//    FragColor = texture(TextureMap, (shifted + 0.5));

    vec4 color = texture2D(TextureMap, TexCoord);
//    float brightness = luma(color);
//    FragColor = vec4(vec3(brightness), 1.0);
//    water2d(gl_FragCoord.xy, color);
    FragColor = dither4x4(gl_FragCoord.xy, color);
//    FragColor = texture(TextureMap, TexCoord);// * vec4(0.0, 0.0, 1.0, 1.0);
}

