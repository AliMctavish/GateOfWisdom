#version 330 core

out vec4 color;
in vec4 ourColor;

uniform vec3 objectColor;

void main()
{
	color = vec4(objectColor , 1);
}