#version 330 core

layout (location = 0) in vec2 coords;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(coords, 0, 1);
}