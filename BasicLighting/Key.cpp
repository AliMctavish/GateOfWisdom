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
	CUBEID++;
}

void Key::Update()
{
	BaseObject::Update();
	BaseObject::Rotate();
}

void Key::Draw(ModelLoader *modelLoader)
{
	m_Shader.SetMat4("model" , m_Model);
	BaseObject::UseColor("objectColor");
	modelLoader->GetModel(modelLoader->Type_Key).Draw(m_Shader);
}
