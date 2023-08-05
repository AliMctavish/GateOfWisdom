#version 330 core
out vec4 color;
in  vec3 ourColor;
uniform vec4 colorTest;

void main()
{
	color = colorTest;
}