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


void Light::Update()
{
	BaseObject::Update();
	BaseObject::Rotate();
}


void Light::Update(Player& player, GLFWwindow* window)
{
	//there is an offset happening for the position of the player 
	//cuz of the redefining the matrix of the light 
	// so to solve this you need to define the matrix after 
	// the light is picked up so you can control the offset of the player 
	// after the changing of the light position of the object 
	// so you also need to change the matrix cuz defiing the matrix 
	// from the start of the function will cuz the offset to happen 
	// cuz you are not updating the model of the matrix of the light 
	//after the changing happen of the offset of the player 
	// non - sense ikr? 

	if (isPickedUp)
	{
		Position = player.Position;

		if (player.isRunning)
			m_Model = glm::translate(m_Model, glm::sin(glm::vec3(0, -player.counter, 0)));

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			isPickedUp = false;
			player.hasLight = false;
			isPushing = true;
			direction = glm::normalize(player.CameraFront);
		}
	}

	BaseObject::Update();

	//the reason why this is not working when the object is not picked up 
	//is because of the sinmove method that you called in the rendering part 
	//what is actually happening you are overriding the matrix when the object
	//is not picked up !!
	m_Model = glm::translate(m_Model, ((player.CameraRight * 0.5f) + player.CameraFront) * 2.0f);
	BaseObject::Rotate();
}




void Light::Draw()
{
	m_Shader.SetMat4("model", m_Model);
	UseColor("objectColor");
    m_ModelLoader.GetModel(ModelLoader::Type_Sphere).Draw(m_Shader);
}


