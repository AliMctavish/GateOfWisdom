#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Player.h"

#define White_Sprite_Color glm::vec3(1,1,1);

class Sprite {
private :
	glm::vec3 Position;
	Texture texture;
	Shader m_Shader;
	glm::vec3 m_Color;
	glm::mat4 m_Model;
	Player* m_Player;
public :
	VertexBuffer vertexBuffer = VertexBuffer(VertexType::Surface_Type);
	VertexArray vertexArray;
	Sprite();
	void SetPosition(glm::vec3 &position);
	void SetTexture(std::string filePath);
	void SetCamera(Player *player);
	void Update();
	void Draw();
};
