#pragma once
#include "BaseObject.h"
#include "Player.h"
#include "Shader.h"

class Light :public BaseObject{
public:
	bool isPushing = false;
	Material material;
	int objectId;
	glm::vec3 Size;
	float angle;
	float rotateX, rotateY, rotateZ;
	std::string GetName() { return _name; }
	glm::mat4 inline GetModel() { return m_Model; }
	void Update(Player &player , GLFWwindow* window);
	void Init();
	float MoveOnX();
	void Draw();
	Light();
};
