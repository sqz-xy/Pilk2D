#version 330 core

in vec2 oTexCoords;
in vec3 oFragPos;

out vec4 FragColor;

uniform vec4 uColour;
uniform sampler2D uDiffuse;
uniform float uTime;

uniform vec2 uSpriteSheetSize;
uniform vec2 uSpriteSize;

void main()
{
    vec2 SpriteSize = vec2(64, 64);
    vec2 SpriteSheetSize = vec2(384, 64);
    int index = 0;

    float w = SpriteSheetSize.x;
    float h = SpriteSheetSize.y;

    float dx = SpriteSize.x / w;
    float dy = SpriteSize.y / h;

    float cols = w / SpriteSize.x;

    float col = mod(index, cols);
    float row = floor(index / cols);

    vec2 uv = vec2(dx * oTexCoords.x + col * dx, 1.0 - dy - row * dy + dy * oTexCoords.y);

    vec4 texel = texture(uDiffuse, uv);

    if (texel.a < 0.5)
        discard;

    FragColor = texel;
} 