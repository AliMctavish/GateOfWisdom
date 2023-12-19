#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite()
{
	Position = glm::vec3(0, 0, 0);
	m_Model = glm::mat4(1.0f);
	m_Player = nullptr;
	m_Color = White_Sprite_Color;
	m_Shader.SetShaders("SpriteVertexShader.shader", "SpriteFragmentShader.shader");
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

void Sprite::SetCamera(Player* player)
{
	m_Player = player;
}

void Sprite::Update()
{
	Position = m_Player->Position;
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, Position);
}

void Sprite::Draw()
{
	vertexArray.Bind();
	texture.Bind();
	m_Shader.Bind();
	m_Shader.SetMat4("projection", m_Player->Projection);
	m_Shader.SetMat4("model", m_Model);
	m_Shader.Set3Float("spriteColor", m_Color.x, m_Color.y, m_Color.z);
	m_Shader.setInt("spriteTexture", texture.m_TextureIndex);
	m_Shader.SetMat4("model", m_Model);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_Shader.UnBind();
	vertexArray.UnBind();
}
