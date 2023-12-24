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
	if (!m_HasStartPosition)
	{
		// the 1.0f is added to prevent any zero or negetive number 
		m_StartPosition = Position + 1.0f;
		m_HasStartPosition = true;
	}

	glm::vec3 direction;

	if(glm::distance(m_StartPosition , player.Position) <= 100)
		direction = glm::normalize(Position - player.Position);
	else
		direction = glm::normalize(Position - m_StartPosition);

	Position -= direction * 0.2f;

	float angle = glm::atan(direction.x, direction.z);
	m_Model = glm::rotate(m_Model, angle, glm::vec3(0, 1, 0));
}



void Enemy::Draw(ModelLoader& modelLoader)
{
	m_Shader.SetMat4("model", m_Model);
	modelLoader.GetModel(ModelLoader::Type_Enemy).Draw(m_Shader);
}