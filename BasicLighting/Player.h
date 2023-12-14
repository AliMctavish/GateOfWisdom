#pragma once
#include "BaseObject.h"

class Player :public BaseObject {
private : 
	float m_Pov = 75.0f;
	glm::vec3 m_OscillationAngle = glm::vec3(0,0,0);
	void OscillateOnMoving();
	void MoveWithOscillation(float speedAmount, float oscTime);
public:
	float counter = 0;
	float speedAmount= 0 ; 
	Player();
	bool grounded = false;
	bool isJumping = false;
	bool isRunning = false;
	bool isWalking = false;
	bool hasLight = false;
	glm::vec3 Position;
	glm::vec3 CameraFront;
	glm::vec3 CameraUp;
	glm::vec3 CameraRight;
	glm::mat4 View;
	glm::mat4 Projection;
	void SetMatrix();
	void Update();
	~Player();
};