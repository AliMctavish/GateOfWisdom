#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Controllers {
private:
	//MOUSE CONTROLLERS
	bool firstMouse;
	float lastX, lastY;
	float yaw;
	float pitch;
	//CAMERA STUFF IN HERE
	float horizontal_directions;
	float vertical_directions;
	float resize;
	bool isMoving;
	float fov;
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 direction;
	glm::vec3 cameraRight;
	Controllers();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void processInput(GLFWwindow* window, float deltaTime);
};


