#include "Light.h"

void Light::Init()
{
	objectId = CUBEID;
	Size = glm::vec3(2, 2, 2);
	m_Model = glm::mat4(1.0f);
	Position = glm::vec3(50, 0, 20);
	CUBEID++;
}


Light::Light()
{
	Init();
}

void Light::SetRandomLocation()
{
	Position = glm::vec3(rand() % 90, rand() % 90, rand() % 90);
}

void Light::SetRandomColor()
{
	Color[0] = rand() % 10;
	Color[1] = rand() % 10;
	Color[2] = rand() % 10;
}


void Light::Push()
{
	Position += 1.0f * direction;
}

void Light::Update(Player& player, GLFWwindow* window)
{
	BaseObject::Update();
	if (isPickedUp)
	{
		Position = player.Position;


		m_Model = glm::translate(m_Model, ((player.CameraRight * 0.5f) + player.CameraFront) * 2.0f);

		if (player.isRunning)
			m_Model = glm::translate(m_Model, glm::sin(glm::vec3(0, -player.counter + 0.1f, 0)));

		m_Model = glm::rotate(m_Model, (float)glfwGetTime(), glm::vec3(1, 1, 0));

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			isPickedUp = false;
			player.hasLight = false;
			isPushing = true;
			direction = glm::normalize(player.CameraFront);
		}
	}
}

void Light::Draw(ModelLoader& objectModel)
{
	//BaseObject::Draw();
	m_Shader.SetMat4("model", m_Model);
	UseColor("objectColor");
	objectModel.GetModel(ModelLoader::Type_Sphere).Draw(m_Shader);
}

