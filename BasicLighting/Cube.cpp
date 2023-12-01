#include "Cube.h"

Cube::Cube()
{
	Init();
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

void Cube::Draw()
{
	m_Shader.setVec3("light.diffuse", material.Diffuse);
	m_Shader.setVec3("light.specular", material.Specular);
	m_Shader.setFloat("material.Shininess", material.shininess);
	m_Shader.SetMat4("model", m_Model);
	m_Shader.setInt("texture0", texture.m_TextureIndex);
	texture.Bind();
	UseColor("objectColor");

	BaseObject::Draw();
}

void Cube::SetTextureData(uint16_t textureIndex)
{
	m_TextureIndex = textureIndex;
	texture.SetTexutreType(m_TextureIndex);
}

//void Cube::SetShaderData()
//{
//	shader.setVec3("light.ambiant", material.Ambiant);
//	shader.setVec3("light.diffuse", material.Diffuse);
//	shader.setVec3("light.specular", material.Specular);
//	shader.setFloat("material.Shininess", material.shininess);
//	shader.SetMat4("model", GetModel());
//	shader.setInt("texture0", texture.m_TextureIndex);
//}


void Cube::Update()
{
	BaseObject::Update();
	Rotate(rotateX);
	RotateOnY(rotateY);
	Resize(Size);
}

void Cube::Rotate(float angle)
{
	m_Model = glm::rotate(m_Model, rotateX, glm::vec3(1, 0, 0));
}

void Cube::RotateOnY(float angle)
{
	m_Model = glm::rotate(m_Model, rotateY, glm::vec3(0, 1, 0));
}

void Cube::Resize(glm::vec3& size)
{
	m_Model = glm::translate(m_Model, glm::vec3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
	m_Model = glm::scale(m_Model, glm::vec3(size));
}




Cube::~Cube()
{

}


