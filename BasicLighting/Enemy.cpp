#include "Enemy.h"

Enemy::Enemy()
{
	objectId = CUBEID;
	Size = glm::vec3(2, 2, 2);
	m_Model = glm::mat4(1.0f);
	Position = glm::vec3(50, 0, 20);
	CUBEID++;
}

void Enemy::SetRandomLocation()
{
	Position = glm::vec3(rand() % 90, rand() % 90, rand() % 90);
}


void Enemy::Update()
{
	BaseObject::Update();
	BaseObject::Resize();
}

void Enemy::MoveTowardsPlayer(Player& player)
{
	glm::vec3 direction = glm::normalize(Position - player.Position);
	Position -= direction * 0.02f;
	float angle = glm::atan(direction.x, direction.z);

	m_Model = glm::rotate(m_Model, angle, glm::vec3(0, 1, 0));
	//m_Model = glm::translate(m_Model, direction);
}



void Enemy::Draw(ModelLoader& objectModel)
{
	m_Shader.SetMat4("model", m_Model);
	//BaseObject::Draw();
	objectModel.GetModel(ModelLoader::Type_Enemy).Draw(m_Shader);
}