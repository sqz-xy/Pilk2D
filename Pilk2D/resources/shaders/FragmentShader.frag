#version 330 core

in vec2 oTexCoords;
in vec3 oFragPos;

out vec4 FragColor;

uniform vec4 uColour;
uniform sampler2D uDiffuse;
uniform float uTime;

void main()
{
    vec2 uv = oTexCoords;
    
    if (uv.y > 0.3)
        uv.x += cos(uTime + uv.y) * 0.01;

    vec4 texel = texture(uDiffuse, uv);

    if (texel.a < 0.5)
        discard;

    FragColor = texel;
} 