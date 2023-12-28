#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform vec3 objectColor;
uniform sampler2D texture_diffuse1;


void main()
{
	color = texture(texture_diffuse1, TexCoords) * vec4(objectColor,1) ;
}