#include "Cube.h"


Cube::Cube()
{
	_name = nullptr;
	Init();
}

void Cube::SetProgram(uint32_t program)
{
	m_Program = program;
}

void Cube::SetName(const char* name)
{
	_name = name;
}

void Cube::Init()
{
	xCoord = 0;
	yCoord = 0;
	zCoord = 0;
	angle = 0;
	size = 5;
	m_Model = glm::mat4(1.0f);
	m_Program = 0;
	m_Location = glm::vec3(xCoord,yCoord,zCoord);
}
void Cube::SetColor(const char* name)
{
	int colorLoc = glGetUniformLocation(m_Program, name);
	glUniform3f(colorLoc,Color[0], Color[1], Color[2]);
}

void Cube::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::Position(glm::vec3 location)
{
	m_Model = glm::mat4(1.0f);
	m_Location = location;
	m_Model = glm::translate(m_Model, location);
}

void Cube::RotateX(float angle)
{
	m_Model = glm::rotate(m_Model,angle,glm::vec3(1,0,0));
}
void Cube::RotateY(float angle)
{
	m_Model = glm::rotate(m_Model,angle, glm::vec3(0,1,0));
}
void Cube::RotateZ(float angle)
{
	m_Model = glm::rotate(m_Model,angle, glm::vec3(0,0,1));
}

void Cube::Resize(glm::vec3 size)
{
	m_Model = glm::scale(m_Model, size);
}


Cube::~Cube()
{

}


