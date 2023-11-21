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
	Position.y = glm::sin(sineValue) / 2;
	m_Model = glm::translate(m_Model, Position);
	sineValue += 0.01;
}

void BaseObject::UseColor(const char* name)
{
	int colorLoc = glGetUniformLocation(m_Program, name);
	glUniform3f(colorLoc, Color[0], Color[1], Color[2]);
}

void BaseObject::SetProgram(uint32_t program)
{
	m_Program = program;
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
