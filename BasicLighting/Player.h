#pragma once
#include "BaseObject.h"

class Player : BaseObject {
public:
	Player();
	bool grounded = false;
	bool isJumping = false;
	glm::vec3 Position;
	glm::vec3 CameraFront;
	glm::vec3 CameraUp;
	glm::vec3 CameraRight;
	glm::mat4 View;
	glm::mat4 Projection;
	void SetMatrix();
	~Player();
};