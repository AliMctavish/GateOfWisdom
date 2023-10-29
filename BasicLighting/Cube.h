#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

enum RotateSide {
	xAxis = 0,
	yAxis = 1,
	zAxis = 2,
};


class Cube {
private : 
	glm::mat4 m_Model;
	uint32_t m_Program;
	glm::vec3 m_Location;
	const char* _name;
public : 
	int xCoord, yCoord, zCoord;
	float angle , size;
	float rotateX,rotateY,rotateZ;

	Cube();
	~Cube();
	void SetName(const char* name);
	const char* GetName() { return _name; }
	void SetProgram(uint32_t program);
	void Draw();
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void SetLocation(glm::vec3 location);
	void Resize(glm::vec3 size);
	void Init();
};
