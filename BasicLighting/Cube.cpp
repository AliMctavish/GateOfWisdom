#include "Cube.h"

Cube::Cube(unsigned int program)
{
	Init();
	m_Program = program;
}

void Cube::Init()
{
	m_Model = glm::mat4(1.0f);
	m_Program = 0;
	m_Location = glm::vec3(0, 0, 0);
}

void Cube::Draw()
{
	int modelLoc = glGetUniformLocation(m_Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_Model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::SetLocation(glm::vec3 location)
{
	m_Model = glm::mat4(1.0f);
	m_Location = location;
	m_Model = glm::translate(m_Model, location);
}

void Cube::Rotate(float angle)
{
	m_Model = glm::rotate(m_Model,angle, glm::vec3(0, 1, 0));
}


Cube::~Cube()
{

}


