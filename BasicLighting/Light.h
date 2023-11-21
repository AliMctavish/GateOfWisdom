#pragma once
#pragma once
#include "Cube.h"

class Light :public Cube{
public:
	Material material;
	int objectId;
	glm::vec3 Size;
	float angle;
	float rotateX, rotateY, rotateZ;
	std::string GetName() { return _name; }
	glm::mat4 inline GetModel() { return m_Model; }
	void Update();
	void Init();
	void Draw();
	Light();
};
