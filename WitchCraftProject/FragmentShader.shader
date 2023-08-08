#version 330 core

out vec4 color;
in  vec3 ourColor;
in vec2 ourTexture;

uniform vec4 colorTest;
uniform sampler2D textureFrag;
uniform sampler2D textureFrag2;

void main()
{
	color = mix( texture(textureFrag,ourTexture) *  vec4(ourColor,1), texture(textureFrag2, ourTexture) * vec4(ourColor, 1) ,0.2);
}