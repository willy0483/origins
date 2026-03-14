#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoords;


out vec3 color;
out vec2 texCoords;

uniform mat4 cameraMatrix;
uniform mat4 model;

void main()
{
    gl_Position = cameraMatrix * model * vec4(aPos, 0.0f, 1.0f);
    color = aColor;
    texCoords = aTexCoords;
}
