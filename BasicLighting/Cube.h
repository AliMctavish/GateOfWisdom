#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GuiDebugger.h"
#include "Shader.h"

enum RotateSide {
	xAxis = 0,
	yAxis = 1,
	zAxis = 2,
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
	int cubeId;
	float Color[3] = {0,0,0};
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
	void Rotate();
	void SetColor(const char* name);
	void Resize(glm::vec3& size);
	void Init();
};
