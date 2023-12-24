#include "BaseObject.h"

void BaseObject::Update()
{
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, Position);
}


void BaseObject::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void BaseObject::SinMove()
{
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, Position + glm::vec3(0, glm::sin(sineValue) / 2 + 1,0));
	sineValue += 0.1;
}

void BaseObject::Resize()
{
	m_Model = glm::translate(m_Model, glm::vec3(Size.x * 0.5f, Size.y * 0.5f, Size.z * 0.5f));
	m_Model = glm::scale(m_Model, glm::vec3(Size));
}

void BaseObject::ResetValues()
{
	Position = Origin;
	isPushing = false;
	isPickedUp = false;
}

void BaseObject::Rotate()
{
	m_Model = glm::rotate(m_Model, glm::radians(m_RotationAngleCounter++), glm::vec3(1, 1, 0));
	if (m_RotationAngleCounter > 360)
		m_RotationAngleCounter = 0;
}

void BaseObject::Rotate360OnY()
{
	m_Model = glm::rotate(m_Model, glm::radians(m_RotationAngleCounter+=.2), glm::vec3(0, 1, 0));
	if (m_RotationAngleCounter > 360)
		m_RotationAngleCounter = 0;
}

void BaseObject::Rotate360OnX()
{
	m_Model = glm::rotate(m_Model, glm::radians(m_RotationAngleCounter += .2), glm::vec3(0, 0, 1));
	if (m_RotationAngleCounter > 360)
		m_RotationAngleCounter = 0;
}

void BaseObject::SetShader(Shader &shader)
{
	m_Shader = shader;
}

//void BaseObject::SetModel(ModelLoader& modelLoader)
//{
//	m_ModelLoader = modelLoader;
//}

void BaseObject::SetPosition(glm::vec3 position)
{
	Position = position;
	Origin = position;
}


void BaseObject::UseColor(const char* name)
{
	int colorLoc = glGetUniformLocation(m_Shader.shader_program, name);
	glUniform3f(colorLoc, Color[0], Color[1], Color[2]);
}

void BaseObject::SetObjectColor(float x, float y, float z)
{
	Color[0] = x;
	Color[1] = y;
	Color[2] = z;
}

void BaseObject::SetName(std::string name)
{
	_name = name;
}

void BaseObject::RotateY()
{
	m_Model = glm::rotate(m_Model, glm::radians(rotateY), glm::vec3(0, 1, 0));
}
