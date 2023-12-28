#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform vec3 spriteColor;
uniform sampler2D spriteTexture;

void main()
{
	vec4 texColor = texture(spriteTexture, TexCoords) * vec4(1);

	if (texColor.a < 0.1)
		discard;

	color = texColor;
}