#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

uniform float uTime;

out vec3 oFragPos;
out vec2 oTexCoords;

void main()
{
    oTexCoords = aTexCoords;
    oFragPos = vec3(uModel * vec4(aPos, 1.0));
    gl_Position = uProjection * uModel * uView * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

