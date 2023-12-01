#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#define Material_Default_Value glm::vec3(0.5f,0.5f,0.5f)
#define Effect_Defualt_Value glm::vec3(0,0,0)

	struct Material {
		glm::vec3 Ambiant = glm::vec3(0.05f, 0.05f, 0.05f);
		glm::vec3 Diffuse = Material_Default_Value;
		glm::vec3 Specular = Material_Default_Value;
		float shininess = 32;
	};

	struct Effect_Material {
		glm::vec3 DiffuseSurface = Effect_Defualt_Value;
	};


	static uint32_t CUBEID;

class BaseObject {
private:
	double sineValue = 50;
public : 
	Shader m_Shader;
	bool isPickedUp = false;
	glm::vec3 direction;
	glm::vec3 Position;
	glm::mat4 m_Model;
	uint32_t m_Program;
	std::string _name;
	float Color[3] = { 0.5,0.5,0.5 };
	void Update();
	void Draw();
	void SinMove();
	void SetShader(Shader &shader);
	void UseColor(const char* name);
	void SetProgram(uint32_t program);
	void SetObjectColor(float x, float y, float z);
	void SetName(std::string name);
};
