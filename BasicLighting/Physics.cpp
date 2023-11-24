#include "Physics.h"

Physics::Physics()
{

}

void Physics::SetWindow(GLFWwindow* window)
{
	_window = window;
}


void Physics::CheckCollision(Cube &cube,glm::vec3 &cameraPos,double &deltaTime)
{
	if (grounded == false || cube.collided)
	{
		if (IsCollided(cube.Position,cameraPos,cube.Size))
		{

			float distance = cameraPos.y - cube.Position.y;
			cameraPos.y = cube.Position.y + distance;
			std::cout << "triggerd !" << std::endl;
			std::cout << distance << std::endl;

			//std::cout << acceleration << std::endl;

			cube.collided = true;
			grounded = true;
			isJumping = false;
			acceleration = 0.05f;
		}
		else
		{
			grounded = false;
			cube.collided = false;
		}
	}

	if (grounded == false)
		cameraPos.y -= 0.00001f * deltaTime;

	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cube.collided = false;
		grounded = false;
		isJumping = true;
	}

	if (isJumping)
	{
		cameraPos.y += acceleration;
		acceleration -= 0.00005;
	}
}


bool Physics::IsCollided(glm::vec3& object1, glm::vec3& object2, glm::vec3& sizeObject1)
{
	int object1XX = object1.x + sizeObject1.x;
	int object1X = object1.x;
	int object1YY = object1.y + sizeObject1.y + 1;
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

