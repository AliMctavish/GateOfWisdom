#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;


struct LightSource
{
	vec3 ambiant;
	vec3 diffuse;
	vec3 specular;
};


void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}