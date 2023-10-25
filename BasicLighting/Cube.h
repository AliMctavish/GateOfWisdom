#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


class Cube {
private : 
	glm::mat4 m_Model;
	unsigned int m_Program;
	glm::vec3 m_Location;
public : 
	Cube(unsigned int program);
	~Cube();
	void Update();
	void Draw();
	void SetLocation(int x , int y , int z);

	void Resize();
	void Init();


};
