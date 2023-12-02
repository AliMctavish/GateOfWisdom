#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 MyTexture;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform int LightCount;
uniform vec3 lightColor[40];
uniform vec3 lightPos[40];
uniform vec3 lightDiffuse[40];



struct Effect {
	vec3 DiffuseSurface;
};

struct Material {
	vec3 Ambiant;
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};

uniform sampler2D texture0;

struct LightSource
{
	vec3 ambiant;
	vec3 diffuse;
	vec3 specular;
};

vec3 Texture(sampler2D passedTexture)
{
	return texture(passedTexture, MyTexture).rgb;
};

uniform Material material;
uniform LightSource light;
uniform Effect effect;


vec3 CalculateFragment(vec3 lightPos, vec3 lightColor,vec3 lightDiffuse)
{

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float distance = length(lightPos - FragPos);

	float attenuation = ((distance * distance) * 0.0057) + ((distance * 0.0075) + 1);

	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = ((light.diffuse + lightDiffuse) * (diff * Texture(texture0)) * lightColor) ;

	// specular
	float specularStrength = 0.02;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
	vec3 specular = light.specular * (spec)*objectColor * lightColor;

	return (diffuse + specular ) * objectColor / attenuation;
}

void main()
{
	vec3 result;
	vec3 ambient = (light.ambiant) * Texture(texture0);
	for (int i = 0; i < LightCount; i++)
	{
	ambient *= lightColor[i];

		//todo clean the code and make loop on list of light sourse so we can make multiple light sources
		result += CalculateFragment(lightPos[i], lightColor[i], lightDiffuse[i]);
		//result += CalculateFragment(lightPos[i], lightColor[i],texture1);
	}
	FragColor = vec4(result + ambient,  1.0);
}

