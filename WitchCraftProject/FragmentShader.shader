#version 330 core

out vec4 color;
in  vec3 ourColor;
in vec2 ourTexture;

uniform vec4 colorTest;
uniform sampler2D textureFrag;

void main()
{
	color = texture(textureFrag,ourTexture);
}