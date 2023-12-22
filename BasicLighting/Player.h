#pragma once
#include "BaseObject.h"

class Player :public BaseObject {
private : 
	float m_Pov = 75.0f;
	glm::vec3 m_OscillationAngle = glm::vec3(0,0,0);
	void MoveWithOscillation(float speedAmount, float oscTime);
	void SetVariablesToDefault();
	void OscillateOnMoving();
	uint32_t m_CubeIndex = 0;
public:
	uint32_t inline GetCollidedCubeIndex() { return m_CubeIndex; }
	void ResetCollisionDetection();
	void AssignCollidedCube(uint32_t cubeIndex);
	void SetMatrix();
	int NumberOfKeys = 0;
	float counter = 0;
	float speedAmount= 0 ; 
	Player();
	void Draw();
	void Update();
	bool CollidedWithCube = false;
	bool hasAttachedObject = false;
	bool inRangeOfKeyObject = false;
	bool inRangeOfLightObject = false;
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
	~Player();
};