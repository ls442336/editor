#version 330 core

out vec4 color;

uniform vec3 primitiveColor;

void main()
{
	color = vec4(primitiveColor, 1.0);
}