#include "Player.h"

Player::Player()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	CameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
}


void Player::SetMatrix()
{
	glm::mat4 view;
	glm::mat4 projection;

	view = glm::lookAt(Position, Position + CameraFront, CameraUp);
	projection = glm::perspective(glm::radians(m_Pov), 1200.f / 800.f, 0.1f, 1000.0f);


	View = view;
	Projection = projection;
}

void Player::Update()
{
	//BaseObject::Update();
	//View = glm::translate(View, Position);
}

void Player::AttachObject(Light* light)
{
	if (!hasAttachedObject)
	{
		m_AttachedLight = light;
		m_AttachedLight->isPickedUp = true;
		hasAttachedObject = true;
	}
}

void Player::UnAttachObject()
{
	if (m_AttachedLight != nullptr)
	{
		m_AttachedLight->isPickedUp = false;
		hasLight = false;
		m_AttachedLight->isPushing = true;
		m_AttachedLight->direction = glm::normalize(CameraFront);
		hasAttachedObject = false;
		m_AttachedLight = nullptr;
	}
}



void Player::OscillateOnMoving(double& deltaTime)
{
	//do it in cenratain amount of Oscillation ?
	if (isRunning)
		MoveWithOscillation(3.f, 0.20f, deltaTime);
}

void Player::MoveWithOscillation(float speedAmount, float oscTime, double& deltaTime)
{
	m_OscillationAngle = glm::sin(glm::vec3(0, counter, 0)) * oscTime;

	View = glm::translate(View, m_OscillationAngle);
	counter += speedAmount;
	if (counter > 360)
		counter = 0;
}




Player::~Player()
{
}

