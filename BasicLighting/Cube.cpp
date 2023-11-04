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
	angle = 0;
	Size = glm::vec3(2, 2, 2);
	m_Model = glm::mat4(1.0f);
	m_Program = 0;
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


void Cube::Update()
{
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, Position);
	Resize(Size);
	Rotaions();
}

void Cube::Rotaions()
{
	RotateX();
	RotateY();
	RotateZ();
}

void Cube::SinMove()
{
	m_Model = glm::mat4(1.0f);
	Position.y = glm::sin(sineValue)/2;
	m_Model = glm::translate(m_Model, Position);
	sineValue+=0.01;
}

void Cube::RotateX()
{
	m_Model = glm::rotate(m_Model,rotateX,glm::vec3(1,0,0));
}
void Cube::RotateY()
{
	m_Model = glm::rotate(m_Model,rotateY, glm::vec3(0,1,0));
}
void Cube::RotateZ()
{
	m_Model = glm::rotate(m_Model,rotateZ, glm::vec3(0,0,1));
}

void Cube::Resize(glm::vec3& size)
{
	m_Model = glm::scale(m_Model, size);
}

void Cube::Debug()
{
	ImGui::Text(GetName().c_str());
	ImGui::ColorEdit3(GetName().c_str(), Color, 0);
	//ImGui::SliderFloat("Move2 On X" + cube.GetName(), &cube.Position.x, -50, 50, "%.3f", 0);
	//ImGui::SliderFloat("Move2 On Y" + cube.GetName(), &cube.Position.y, -50, 50, "%.3f", 0);
	//ImGui::SliderFloat("Move2 On Z" + cube.GetName(), &cube.Position.z, -50, 50, "%.3f", 0);
	//ImGui::SliderFloat("Rsizex object" + cube.GetName(), &cube.Size.x, 0, 100, "%.3f", 0);
	//ImGui::SliderFloat("Rsizey object" + cube.GetName(), &cube.Size.y, 0, 100, "%.3f", 0);
	//ImGui::SliderFloat("Rsizez object" + cube.GetName(), &cube.Size.z, 0, 100, "%.3f", 0);
	//ImGui::SliderFloat("Rotate on x Axis" + cube.GetName(), &cube.rotateX, 0, 10, "%.3f", 0);
	//ImGui::SliderFloat("Rotate on y Axis" + cube.GetName(), &cube.rotateY, 0, 10, "%.3f", 0);
	//ImGui::SliderFloat("Rotate on z Axis" + cube.GetName(), &cube.rotatez, 0, 10, "%.3f", 0);
}


Cube::~Cube()
{

}


