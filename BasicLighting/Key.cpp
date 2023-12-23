#include "Key.h"

Key::Key()
{
	Init();
}

void Key::Init()
{
	objectId = CUBEID;
	Position = glm::vec3(0, 0, 0);
	Size = glm::vec3(1, 1, 1);
	SetObjectColor(0, 1, 1);
	CUBEID++;
}

void Key::Update(Player& player, GLFWwindow* window)
{
	if (isPickedUp)
	{
		Position = player.Position;

		if (player.isRunning)
			m_Model = glm::translate(m_Model, glm::sin(glm::vec3(0, -player.counter, 0)));

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			player.hasKey = false;
			isPickedUp = false;
			player.AssignPickedKey(0);
			Position = player.Position + glm::vec3(1,-1,1);
		}
	}

	BaseObject::Update();

	//the reason why this is not working when the object is not picked up 
	//is because of the sinmove method that you called in the rendering part 
	//what is actually happening you are overriding the matrix when the object
	//is not picked up !!
	if (isPickedUp)
		m_Model = glm::translate(m_Model, ((player.CameraRight * 0.5f) + player.CameraFront) * 2.0f);

	BaseObject::Rotate();
}

void Key::Draw()
{
	m_Shader.SetMat4("model", m_Model);
	BaseObject::UseColor("objectColor");
	m_ModelLoader.GetModel(ModelLoader::Type_Key).Draw(m_Shader);
}
