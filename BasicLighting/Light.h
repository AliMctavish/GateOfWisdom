#pragma once
#include "BaseObject.h"

class Light :public BaseObject{
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
	float MoveOnX();
	void Draw();
	Light();
};
