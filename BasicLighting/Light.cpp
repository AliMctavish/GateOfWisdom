#include "Light.h"

void Light::Init()
{
	objectId = CUBEID;
	angle = 0;
	rotateX = 0;
	rotateY = 0;
	Size = glm::vec3(2, 2, 2);
	m_Model = glm::mat4(1.0f);
	Position = glm::vec3(50, 0, 20);
	m_Program = 0;
	CUBEID++;
}

Light::Light()
{
	Init();
}

void Light::Update()
{
	BaseObject::Update();
}

void Light::Draw()
{
	BaseObject::Draw();
}

