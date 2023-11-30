#pragma once
#include "BaseObject.h"
#include "Cube.h"
#include "Light.h"
#include "Player.h"

class Physics {
private:

	GLFWwindow* _window;
	Player _player;

	bool isJumping = false;
	float acceleration = 0.001f;
public:
	bool IsCollided(glm::vec3& object1, glm::vec3& object2, glm::vec3& sizeObject1);
	Physics();
	~Physics();
	void SetVariables(GLFWwindow* window, Player &player);
	void UpdateGravity(double& deltaTime,Player &player);
	bool CheckCollision(Cube& cube , Player &player);
	bool CheckLightCollision(Light& light, Player &player);
};


