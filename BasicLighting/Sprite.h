#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>


#define White_Sprite_Color glm::vec3(1,1,1);

class Sprite {
private :
	glm::mat4 m_Projeciton = glm::perspective(glm::radians(75.0f), 1200.f / 800.f, 0.1f, 10.0f);
	glm::vec3 Position;
	Texture texture;
	Shader m_Shader;
	glm::vec3 m_Color;
	glm::mat4 m_Model;
public :
	VertexBuffer vertexBuffer = VertexBuffer(VertexType::Surface_Type);
	VertexArray vertexArray;
	Sprite();
	void SetPosition(glm::vec3 &position);
	void SetTexture(std::string filePath);
	void Update();
	void Draw();
};
