#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GuiDebugger.h"
#include "Shader.h"

#define Material_Default_Value glm::vec3(0.5f,0.5f,0.5f)

enum RotateSide {
	xAxis = 0,
	yAxis = 1,
	zAxis = 2,
};

struct Material {
	glm::vec3 Ambiant = Material_Default_Value;
	glm::vec3 Diffuse = Material_Default_Value;
	glm::vec3 Specular = Material_Default_Value;
	float shininess = 32;
};


static int CUBEID;

class Cube {
private : 
	glm::mat4 m_Model;
	uint32_t m_Program;
	glm::vec3 m_Location;
	std::string _name;
	double sineValue = 50;
public : 
	Material material;
	int cubeId;
	float Color[3] = {1,1,1};
	glm::vec3 Position;
	glm::vec3 Size;
	float angle;
	float rotateX,rotateY,rotateZ;

	Cube();
	~Cube();
	void SinMove();
	void SetName(std::string name);
	std::string GetName() { return _name; }
	glm::mat4 inline GetModel() { return m_Model; }
	void SetProgram(uint32_t program);
	void Update();
	void Draw();
	void Rotate(float angle);
	void RotateOnY(float angle);
	void SetColor(const char* name);
	void Resize(glm::vec3& size);
	void Init();
};
