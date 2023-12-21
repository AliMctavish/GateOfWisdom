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

void Key::Draw()
{
	m_Shader.SetMat4("model" , m_Model);
	BaseObject::UseColor("objectColor");
	m_ModelLoader.GetModel(ModelLoader::Type_Key).Draw(m_Shader);
}
