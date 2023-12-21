#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#define Material_Default_Value glm::vec3(0.5f,0.5f,0.5f)
#define Effect_Defualt_Value glm::vec3(0,0,0)

	struct Material {
		glm::vec3 Ambiant = Material_Default_Value * 0.1f;
		glm::vec3 Diffuse = Material_Default_Value * 2.0f;
		glm::vec3 Specular = Material_Default_Value * 2.0f;
		float shininess = 32;
	};

	struct Effect_Material {
		glm::vec3 DiffuseSurface = Effect_Defualt_Value;
	};


	static uint32_t CUBEID;

class BaseObject {
private:
	double sineValue = 50;
	float m_RotationAngleCounter = 0;
public : 
	Shader m_Shader;
	bool isPickedUp = false;
	glm::vec3 Position;
	glm::vec3 Size;
	glm::mat4 m_Model;
	std::string _name;
	float Color[3] = { 0.5,0.5,0.5 };
	void Update();
	void Draw();
	void SinMove();
	void SetShader(Shader &shader);
	std::string inline GetName() { return _name; }
	void UseColor(const char* name);
	void SetObjectColor(float x, float y, float z);
	void SetName(std::string name);
	void Resize();
	void Rotate();
};
