#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;


void main()
{
    FragColor = vec4(vec3(1.0f,1.0f,1.0f),1.0f);
}
