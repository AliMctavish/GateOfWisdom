#pragma once
#include "BaseObject.h"
#include "ModelLoader.h"
#include "Player.h"



//enmey class that handles enemies :3 
class Enemy : public BaseObject{
private : 
	glm::vec3 m_StartPosition;
	bool m_HasStartPosition = false;
	bool m_HasStoppedFromMoving = true;
public : 
	unsigned int objectId;
	Enemy();
	void SetRandomLocation();
	void Draw(ModelLoader& modelLoader);
	void Update();
	void MoveTowardsPlayer(Player &player);
};
