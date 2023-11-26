#include "Physics.h"

Physics::Physics()
{

}

void Physics::SetVariables(GLFWwindow* window, glm::vec3 cameraPos)
{
	_window = window;
	m_CameraPos = cameraPos;
}


bool Physics::CheckCollision(Cube& cube, glm::vec3& cameraPos)
{
	if (IsCollided(cube.Position, cameraPos, cube.Size))
	{
		float distance = cameraPos.y - cube.Position.y;
		cameraPos.y = cube.Position.y + distance;
		isJumping = false;
		acceleration = 0.001f;
		return true;
	}	
	else
		return false;

}

void Physics::Update(glm::vec3& cameraPos, double& deltaTime , bool &grounded)
{
	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		isJumping = true;

	if (!grounded)
		cameraPos.y -= 0.0001f * deltaTime;

	if (isJumping)
	{
		cameraPos.y += acceleration * deltaTime;
		acceleration -= 0.00000001f * deltaTime;
	}
}



bool Physics::IsCollided(glm::vec3& object1, glm::vec3& object2, glm::vec3& sizeObject1)
{
	int object1XX = object1.x + sizeObject1.x +1;
	int object1X = object1.x;
	int object1YY = object1.y + sizeObject1.y + 5;
	int object1Y = object1.y;
	int object1ZZ = object1.z + sizeObject1.z;
	int object1Z = object1.z;

	int object2XX = object2.x + 3;
	int object2X = object2.x;
	int object2YY = object2.y + 2;
	int object2Y = object2.y;
	int object2ZZ = object2.z + 2;
	int object2Z = object2.z;

	return object2Y < object1YY&& object1Y < object2YY&& object2X < object1XX
		&& object1X < object2XX&& object2Z < object1ZZ&& object1Z < object2ZZ;
}



Physics::~Physics()
{
}

