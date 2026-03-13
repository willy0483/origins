#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColor = mix(texture(texture0, texCoords), texture(texture1, texCoords), 0.2);
}
