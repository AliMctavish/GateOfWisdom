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
	SetObjectColor(1, 1, 1);
	CUBEID++;
}

void Gate::CalculateColorValue(float x, float y, float z, float x1, float y1, float z1)
{
	m_ResultantColor[0] = (x + x1) * 0.5f;
	m_ResultantColor[1] = (y + y1) * 0.5f;
	m_ResultantColor[2] = (z + z1) * 0.5f;
}

void Gate::Update()
{
	BaseObject::Update();
	BaseObject::RotateY();
}

void Gate::Draw(ModelLoader& modelLoader)
{
	m_Shader.SetMat4("model", m_Model);
	BaseObject::UseColor("objectColor");

	//for now
	//BaseObject::Draw();
	modelLoader.GetModel(ModelLoader::Type_Machine).Draw(m_Shader);
}

void Gate::Draw()
{
	BaseObject::Draw();
}
