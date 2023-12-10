#pragma once
#include "BaseObject.h"

class Player :public BaseObject {
private : 
	float m_Pov = 75.0f;
public:
	float counter = 0;
	Player();
	bool grounded = false;
	bool isJumping = false;
	bool isRunning = false;
	bool hasLight = false;
	glm::vec3 Position;
	glm::vec3 CameraFront;
	glm::vec3 CameraUp;
	glm::vec3 CameraRight;
	glm::mat4 View;
	glm::mat4 Projection;
	void SetMatrix();
	void OnRunning();
	~Player();
};