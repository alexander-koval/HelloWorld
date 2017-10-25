#version 330 core

//uniform sampler2D TextureMap;
//in vec2 resolution;
//in float time;

#define amp 0.02
#define tint_color vec4(0.45, 0.89,0.99, 1)

void water2d( out vec4 fragColor, in vec2 fragCoord )
{
//    vec2 uv = fragCoord.xy / resolution.xy;
    
//    vec2 p = uv +
//        (vec2(.5) - texture(TextureMap, uv * 0.3 + vec2( time * 0.05,  time * 0.025 )).xy) * amp +
//        (vec2(.5) - texture(TextureMap, uv * 0.3 - vec2(-time * 0.005, time * 0.0125)).xy) * amp;

//    fragColor = texture(TextureMap, p)*tint_color;
}

