#pragma once
#include "BaseObject.h"
#include "Cube.h"

class Physics {
private: 

	GLFWwindow* _window;
	glm::vec3 m_CameraPos;

	bool grounded = false;
	bool isJumping = false;
	float acceleration = 0.001f;
	bool IsCollided(glm::vec3& object1, glm::vec3& object2, glm::vec3& sizeObject1);
public : 
	Physics();
	~Physics();
	void SetVariables(GLFWwindow* window,glm::vec3 cameraPos);
	void Update(glm::vec3 &cameraPos,double &deltaTime);
	bool CheckCollision(Cube &cube, glm::vec3& cameraPos);
};
