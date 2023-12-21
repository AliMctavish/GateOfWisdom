#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


//CAMERA STUFF IN HERE

//MOUSE CONTROLLERS
float yaw = 1;
float pitch = 1;
float lastX = 400, lastY = 300;
bool firstMouse = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

}

void processInput(GLFWwindow* window, Player& player)
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	player.CameraFront = glm::normalize(direction);
	player.CameraRight = glm::normalize(glm::cross(player.CameraFront, player.CameraUp)) ;

	const float cameraSpeed = 0.7; 

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player.Position -= glm::normalize(glm::cross(player.CameraRight, player.CameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player.Position += glm::normalize(glm::cross(player.CameraRight, player.CameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player.Position -= glm::normalize(glm::cross(player.CameraFront, player.CameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player.Position += glm::normalize(glm::cross(player.CameraFront, player.CameraUp)) * cameraSpeed;


	if (player.grounded && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || player.grounded && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || player.grounded && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || player.grounded && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player.isWalking = true;
	else
		player.isWalking = false;


	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		player.Position += player.CameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		player.Position -= player.CameraUp * cameraSpeed;

	//nasty code in here :3 
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS )
	{
		player.Position -= glm::normalize(glm::cross(player.CameraRight, player.CameraUp)) * cameraSpeed * 0.7f;
		player.isRunning = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE || !player.grounded)
		player.isRunning = false;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;


	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		yaw -= 0.5;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw += 0.5;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pitch += 0.5;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pitch -= 0.5;
}
