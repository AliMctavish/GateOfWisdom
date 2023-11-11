#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;

struct Material {
	vec3 Ambiant;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};

uniform Material material; 


void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

	// ambient
	//float ambientStrength = 0.2;
	vec3 ambient = lightColor  * material.Ambiant;

	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = (diff * material.Diffuse) * lightColor;

	// specular
	float specularStrength = 0.3;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.Shininess);
	vec3 specular =   (spec * material.Specular) * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4(result, 1.0);
}