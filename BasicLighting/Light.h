#pragma once
#include "BaseObject.h"
#include "Shader.h"
#include "ModelLoader.h"
#include "Player.h"

class Light :public BaseObject{
public:
	bool isPushing = false;
	bool isInterpolated = false;
	int objectId;
	glm::vec3 direction;
	void SetRandomLocation();
	void SetRandomColor();
	void Push();
	std::string GetName() { return _name; }
	void Update(Player &player , GLFWwindow* window);
	void Init();
	void Draw(ModelLoader &objectModel);
	Light();
};
