#version 330 core

out vec4 color;
in  vec3 ourColor;
in vec2 ourTexture;

uniform vec3 customColor;
uniform vec4 distance_color;

void main()
{
	//color = mix(texture(textureFrag ,ourTexture), texture(textureFrag2, ourTexture) , 0.2);
	color = vec4(customColor,1);
}