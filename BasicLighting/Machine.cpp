#include "Machine.h"

Machine::Machine()
{
	Init();
}

void Machine::Init()
{
	objectId = CUBEID;
	Position = glm::vec3(0, 0, 0);
	Size = glm::vec3(1.5, 1.5, 1.5);
	CUBEID++;
}

void Machine::Update()
{
	//its time to make this work :"|
	BaseObject::Update();
	RotateOnY(rotateY);
	BaseObject::Resize();
}

void Machine::RotateOnY(float angle)
{
	m_Model = glm::rotate(m_Model, rotateY, glm::vec3(0, 1, 0));
}

void Machine::Draw()
{
	m_Shader.SetMat4("model", m_Model);
	BaseObject::UseColor("objectColor");
	m_ModelLoader.GetModel(ModelLoader::Type_Machine).Draw(m_Shader);
}
