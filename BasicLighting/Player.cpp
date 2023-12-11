#include "Player.h"

Player::Player()
{
	Position = glm::vec3(3.0f, 3.0f, 3.0f);
	CameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
}


void Player::SetMatrix()
{
	glm::mat4 view;
	const float radius = 10.0f;
	float camX = sin(glfwGetTime() * 0.01) * radius;
	float camZ = cos(glfwGetTime() * 0.01) * radius;
	view = glm::translate(view, glm::vec3(-10.0f, 10.0f, 20.0f));
	view = glm::lookAt(Position, CameraFront + Position, CameraUp);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(m_Pov), 1200.f / 800.f, 0.1f, 100000.0f);

	View = view;
	Projection = projection;

	OscillateOnMoving();
}

void Player::Update()
{
	BaseObject::Update();
}

void Player::OscillateOnMoving()
{
	//do it in cenratain amount of Oscillation ?
	if (isRunning)
		MoveWithOscillation(0.08f);
	else
		MoveWithOscillation(0.03f);
}

void Player::MoveWithOscillation(float amount)
{
	View = glm::translate(View, glm::sin(glm::vec3(0, counter  , 0)));
	counter += amount;
	if (counter > 360)
		counter = 0;
}




Player::~Player()
{
}

