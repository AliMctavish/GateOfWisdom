#include "Sprite.h"

Sprite::Sprite()
{
	Position = glm::vec3(0, 0, 0);
	m_Model = glm::mat4(1.0f);
	m_Color = White_Sprite_Color;
	m_Shader.SetShaders("Shaders/SpriteVertexShader.shader", "Shaders/SpriteFragmentShader.shader");

	m_Shader.Bind();
	m_Shader.SetMat4("projection", m_Projeciton);
	m_Shader.UnBind();

	vertexArray.Bind();
	vertexBuffer.Bind();
	vertexArray.UnBind();
}

void Sprite::SetPosition(glm::vec3 &position)
{
	Position = position;
}

void Sprite::SetTexture(std::string filePath)
{
	texture.SetTexture(filePath.c_str(), 0);
}

void Sprite::Update()
{
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, Position);
}

void Sprite::Draw()
{
	vertexArray.Bind();
	texture.Bind();
	m_Shader.Bind();
	m_Shader.Set3Float("spriteColor", m_Color.x, m_Color.y, m_Color.z);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_Shader.UnBind();
	vertexArray.UnBind();
}
