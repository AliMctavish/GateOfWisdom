#pragma once
#include "BaseObject.h"
#include "Cube.h"

class Physics {
private: 
	GLFWwindow* _window;
	bool grounded = false;
	bool isJumping = false;
	float acceleration = 0.00001f;
	bool IsCollided(glm::vec3& object1, glm::vec3& object2, glm::vec3& sizeObject1);
public : 
	Physics();
	~Physics();
	void SetWindow(GLFWwindow* window);
	void CheckCollision(Cube &cube, glm::vec3& cameraPos, double &deltaTime);
};
