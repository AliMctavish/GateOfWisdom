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
	color = mix(texture(textureFrag ,ourTexture), texture(textureFrag2, ourTexture) * vec4(ourColor, 1)  , 0.1);
	//color = vec4(ourColor,1);
}