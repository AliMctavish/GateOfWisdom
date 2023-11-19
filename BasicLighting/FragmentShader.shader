#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 MyTexture;

uniform vec3 lightPos[20];
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform sampler2D TextureTest;
uniform int LightCount;

struct Material {
	vec3 Ambiant;
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};


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


vec3 CalculateFragment(vec3 lightPos, vec3 lightColor)
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	//vec3 distance = lightPos - FragPos;

	float distance = length(lightPos - FragPos);

	float attenuation = 1.0f / ((distance * distance) * 0.008) * ((distance * 0.15f) );

	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = light.diffuse * (diff * Texture(material.Diffuse)) * lightColor ;






	// specular
	float specularStrength = 0.3;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
	vec3 specular = light.specular * (spec)*objectColor;

	return (diffuse + specular ) * objectColor * attenuation;
}

void main()
{
	vec3 result;
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambient = (light.ambiant - 0.4) * Texture(material.Diffuse) * lightColor;
	for (int i = 0; i < LightCount; i++)
	{
		//todo clean the code and make loop on list of light sourse so we can make multiple light sources
		result += CalculateFragment(lightPos[i], lightColor);
	}
	FragColor = vec4(result + ambient, 1.0);
}

