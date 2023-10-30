#version 330 core

out vec4 color;
in  vec3 ourColor;
in vec2 ourTexture;

uniform vec4 colorTest;
uniform sampler2D textureFrag;
uniform sampler2D textureFrag2;
uniform vec4 distance_color;

void main()
{
	//color = mix(texture(textureFrag ,ourTexture), texture(textureFrag2, ourTexture) , 0.2);
	color = vec4(1, 0, 0, 1);
}