#version 330 core
layout (location = 0) in vec4 inPosAndCoords;
out vec2 texCoords;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(inPosAndCoords.x, inPosAndCoords.y, 0, 1.0);
	texCoords = inPosAndCoords.zw;
}