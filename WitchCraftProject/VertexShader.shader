#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(loaction = 1) in vec3 colorPos;
out vec3 outColor;

void main()
{
	gl_Position = vec4(vertexPos.xyz, 1);
	colorPos = ourColor;
}