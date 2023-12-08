#include "Enemy.h"

Enemy::Enemy()
{
	objectId = CUBEID;
	Size = glm::vec3(2, 2, 2);
	m_Model = glm::mat4(1.0f);
	Position = glm::vec3(50, 0, 20);
	CUBEID++;
}


void Enemy::Update()
{
	BaseObject::Update();
	BaseObject::Resize();
}

void Enemy::Draw(ModelLoader& objectModel)
{
	m_Shader.SetMat4("model", m_Model);
	//BaseObject::Draw();
	objectModel.GetModel(ModelLoader::Type_Enemy).Draw(m_Shader);
}