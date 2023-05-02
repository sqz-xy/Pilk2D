#version 330 core

in vec2 oTexCoords;

out vec4 FragColor;

uniform vec4 uColour;
uniform sampler2D uDiffuse;

void main()
{
    FragColor = texture(uDiffuse, oTexCoords) + uColour;
} 