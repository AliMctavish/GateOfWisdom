#include "Player.h"

Player::Player()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Origin = Position;
	CameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
}

void Player::Update()
{
	SetMatrix();
	SetVariablesToDefault();
}


void Player::ResetPointOfView()
{
	m_Pov--;
	if (m_Pov <= 75)
		m_Pov = 75;
}

void Player::SetPointOfView()
{
	m_Pov++;
	if (m_Pov >= 90)
		m_Pov = 90;

}

void Player::ResetValues()
{
	BaseObject::ResetValues();
	NumberOfKeys = 0;
	NumberOfKeys = 0;
	counter = 0;
	speedAmount = 0;
	MaybePickedKeyValid = true;
	CollidedWithCube = false;
	hasAttachedObject = false;
	inRangeOfKeyObject = false;
	inRangeOfLightObject = false;
	inRangeOfMachineObject = false;
	inRangeOfGateObject = false;
	CorrectKey = false;
	grounded = false;
	isJumping = false;
	isRunning = false;
	isWalking = false;
	hasLight = false;
	hasKey = false;
	m_CubeIndex = 0;
	m_LightIndex = 0;
	m_KeyIndex = 0;

}

void Player::ResetCollisionDetection()
{
	m_CubeIndex = 0;
	CollidedWithCube = false;
}

void Player::AssignCollidedCube(uint32_t cubeIndex)
{
	m_CubeIndex = cubeIndex;
	CollidedWithCube = true;
}

void Player::AssignPickedLight(uint32_t lightIndex)
{
	m_LightIndex = lightIndex;
}

void Player::AssignPickedKey(uint32_t keyIndex)
{
	m_KeyIndex = keyIndex;
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

void Player::SetVariablesToDefault()
{
	inRangeOfKeyObject = false;
	inRangeOfLightObject = false;
}


void Player::Draw()
{
	m_Shader.SetMat4("view", View);
	m_Shader.SetMat4("projection", Projection);
	m_Shader.setVec3("viewPos", Position);
}

void Player::MoveWithOscillation(float speedAmount, float oscTime)
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

