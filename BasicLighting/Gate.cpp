#include "Gate.h"

Gate::Gate()
{
	Init();
}

void Gate::Init()
{
	objectId = CUBEID;
	Position = glm::vec3(0, 0, 0);
	Size = glm::vec3(1, 1, 1);
	SetObjectColor(0, 1, 1);
	CUBEID++;
}

void Gate::Update()
{
	BaseObject::Update();
}

void Gate::Draw(ModelLoader& modelLoader)
{
	m_Shader.SetMat4("model", m_Model);
	BaseObject::UseColor("objectColor");

	//for now
	BaseObject::Draw();
	//modelLoader.GetModel(ModelLoader::Type_Machine).Draw(m_Shader);
}

void Gate::Draw()
{
	BaseObject::Draw();
}