#include "Light.h"

void Light::Init()
{
	objectId = CUBEID;
	Size = glm::vec3(0, 0, 0);
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

}


void Light::Draw(ModelLoader& objectModel)
{
	//BaseObject::Draw();
	m_Shader.SetMat4("model", m_Model);
	UseColor("objectColor");
	objectModel.GetModel(ModelLoader::Type_Sphere).Draw(m_Shader);
}

