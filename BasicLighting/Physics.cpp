#include "Physics.h"

Physics::Physics()
{
	_window = nullptr;
}

void Physics::SetVariables(GLFWwindow* window, Player& player)
{
	_window = window;
	_player = player;
}

void Physics::PickUp(Player& player, Light& light)
{
	light.Position = player.Position;

	light.m_Model = glm::translate(light.m_Model, ((player.CameraRight * 0.5f) + player.CameraFront) * 2.0f);

	if (player.isRunning)
		light.m_Model = glm::translate(light.m_Model, glm::sin(glm::vec3(0, -player.counter, 0)));

 	light.m_Model = glm::rotate(light.m_Model, (float)glfwGetTime(), glm::vec3(1, 1, 0));

	light.isPickedUp = false;
}


bool Physics::CheckCollision(Cube& cube, Player& player)
{
	if (IsCollided(cube.Position, player.Position, cube.Size))
	{
		float distance = player.Position.y - cube.Position.y;
		player.Position.y = cube.Position.y + distance;
		//implement the sides collouion also ! 

		player.isJumping = false;
		acceleration = 2;

		return player.grounded = true;
	}
	else
		return player.grounded = false;
}
bool Physics::CheckLightCollision(Light& light, Player& player)
{
	if (IsCollided(light.Position, player.Position, light.Size))
	{
		if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS && !player.hasLight)
		{
			player.hasLight = true;
			return light.isPickedUp = true;
		}
	}
}

void Physics::UpdateGravity(double& deltaTime, Player& player)
{
	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		player.isJumping = true;

	if (!player.grounded)
		player.Position.y -= 1;

	if (player.isJumping)
	{
		player.Position.y += acceleration;
		acceleration -= 0.1f;
	}
}


bool Physics::IsCollided(glm::vec3& object1, glm::vec3& object2, glm::vec3& sizeObject1)
{
	int object1XX = object1.x + sizeObject1.x + 1;
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


bool Physics::IsCollidedTest(glm::vec3& object1, glm::vec3& object2, glm::vec3& sizeObject1)
{
	int object1XX = object1.x + sizeObject1.x + 1;
	int object1X = object1.x;
	int object1YY = object1.y + sizeObject1.y + 2;
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

