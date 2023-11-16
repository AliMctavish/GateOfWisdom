#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 MyTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform sampler2D TextureTest;

struct Material {
	vec3 Ambiant;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};


struct LightSource
{
	vec3 ambiant; 
	vec3 diffuse; 
	vec3 specular;
};

uniform Material material; 
uniform LightSource light;


void test()
{

};

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

	vec3 ambiant = light.ambiant * material.Ambiant ;
	
	// ambient
	//float ambientStrength = 0.2;
	vec3 ambient = lightColor  * ambiant * texture(TextureTest, MyTexture).rgb;
	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = light.diffuse * (diff * material.Diffuse) * lightColor * texture(TextureTest, MyTexture).rgb;
	
	// specular
	float specularStrength = 0.3;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.Shininess);
	vec3 specular = light.specular * (spec * material.Specular) * objectColor * texture(TextureTest, MyTexture).rgb;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4(result, 1.0);
}