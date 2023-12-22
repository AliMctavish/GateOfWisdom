#pragma once
#include "BaseObject.h"
#include "ModelLoader.h"
#include "Player.h"



class Key : public BaseObject{
private : 
	uint16_t m_TextureIndex;
public : 
	uint16_t inline GetTexutreIndex() { return m_TextureIndex; }
	int objectId;
	//bool isPickedUp = false;
	glm::vec3 direction;
	Key();
	void Init();
	void Update(Player &player, GLFWwindow* window);
	void Draw();
};