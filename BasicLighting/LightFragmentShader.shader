#version 330 core

out vec4 color;
in  vec3 ourColor;
in vec2 ourTexture;

uniform vec3 customColor;
uniform vec3 objectColor;
uniform vec4 distance_color;

void main()
{
	color = vec4(customColor * objectColor, 1);
}