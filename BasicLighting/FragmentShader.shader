#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 MyTexture;

uniform vec3 lightPos[2];
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform sampler2D TextureTest;

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

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	 
	// ambient
	vec3 ambient = light.ambiant * Texture(material.Diffuse) *  lightColor ;
	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos[0] - FragPos);
	vec3 lightDir2 = normalize(lightPos[1] - FragPos);
	float diff = max(dot(norm, lightDir), 0);
	float diff2 = max(dot(norm, lightDir2), 0);
	vec3 diffuse = light.diffuse * (diff * Texture(material.Diffuse)) * lightColor ;
	vec3 diffuse2 = light.diffuse * (diff2 * Texture(material.Diffuse)) * lightColor ;
	
	// specular
	float specularStrength = 0.3;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.Shininess);
	vec3 specular = light.specular * (spec) * objectColor;

	vec3 result = (ambient + diffuse + diffuse2 + specular) * objectColor;

	FragColor = vec4(result, 1.0);
}