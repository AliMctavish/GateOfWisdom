#pragma once
#include "BaseObject.h"
#include "Player.h"
#include "Shader.h"
#include "ModelLoader.h"

class Light :public BaseObject{
public:
	bool isPushing = false;
	bool isInterpolated = false;
	int objectId;
	glm::vec3 Size;
	glm::vec3 direction;
	std::string GetName() { return _name; }
	glm::mat4 inline GetModel() { return m_Model; }
	void Update(Player &player , GLFWwindow* window);
	void Init();
	void Draw(ModelLoader &objectModel);
	Light();
};
