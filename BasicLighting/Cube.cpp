#include "Cube.h"


Cube::Cube()
{
	Init();
}

void Cube::SetProgram(uint32_t program)
{
	m_Program = program;
}

void Cube::SetName(std::string name)
{
	_name = name;
}

void Cube::Init()
{
	cubeId = CUBEID;
	angle = 0;
	rotateX = 0;
	rotateY = 0;
	Size = glm::vec3(2, 2, 2);
	m_Model = glm::mat4(1.0f);
	Position = glm::vec3(50, 0, 20);
	m_Program = 0;
	CUBEID++;
}
void Cube::UseColor(const char* name)
{
	int colorLoc = glGetUniformLocation(m_Program, name);
	glUniform3f(colorLoc,Color[0], Color[1], Color[2]);
}

void Cube::SetObjectColor(float x, float y, float z)
{
	Color[0] = x;
	Color[1] = y;
	Color[2] = z;
}


void Cube::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void Cube::Update()
{
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, Position);
	Rotate(rotateX);
	RotateOnY(rotateY);
	Resize(Size);
}



void Cube::SinMove()
{
	m_Model = glm::mat4(1.0f);
	Position.y = glm::sin(sineValue)/2;
	m_Model = glm::translate(m_Model, Position);
	sineValue+=0.01;
}

void Cube::Rotate(float angle)
{
	m_Model = glm::rotate(m_Model,rotateX,glm::vec3(1,0,0));
}

void Cube::RotateOnY(float angle)
{
	m_Model = glm::rotate(m_Model, rotateY, glm::vec3(0, 1, 0));
}

void Cube::Resize(glm::vec3& size)
{
	m_Model = glm::scale(m_Model, size);
}




Cube::~Cube()
{

}


