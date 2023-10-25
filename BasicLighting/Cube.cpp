#include "Cube.h"

Cube::Cube(unsigned int program)
{
	m_Program = program;
	Init();
}


void Cube::Init()
{
	m_Model = glm::mat4(1.0f);
}




void Cube::Draw()
{
	int modelLoc = glGetUniformLocation(m_Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_Model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


Cube::~Cube()
{
}

void Cube::SetLocation(int x , int y , int z)
{
	m_Location = glm::vec3(x,y,z);
	m_Model = glm::translate(m_Model,m_Location);
}


void Cube::Update()
{

}

void Cube::Resize()
{

}

