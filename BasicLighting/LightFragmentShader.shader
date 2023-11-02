#version 330 core

out vec4 color;
in  vec3 ourColor;
in vec2 ourTexture;

vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	lightColor = vec3(1, 1, 0);
	color = vec4(objectColor * lightColor, 1);
}