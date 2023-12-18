#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform vec3 spriteColor;
uniform sampler2D spriteTexture;

void main()
{
	color = texture(spriteTexture, TexCoords) * vec4(1,1,1,1);
}