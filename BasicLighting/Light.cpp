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

void Light::Update(Player& player, GLFWwindow* window)
{
	BaseObject::Update();
	if (isPickedUp)
	{
		//trying to make cube follow camera direciton ?

		Position = player.Position;
		m_Model = glm::translate(m_Model, ((player.CameraRight * 0.5f) + player.CameraFront) * 2.0f);
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

