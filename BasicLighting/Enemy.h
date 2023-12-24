#pragma once
#include "BaseObject.h"
#include "ModelLoader.h"
#include "Player.h"



//enmey class that handles enemies :3 
class Enemy : public BaseObject{
private : 
	bool m_HasStartPosition = false;
	bool m_HasStoppedFromMoving = true;
public : 
	bool InRangeWithPlayerPosition = false;
	glm::vec3 m_StartPosition;
	unsigned int objectId;
	Enemy();
	void SetRandomLocation();
	void Draw(ModelLoader& modelLoader);
	void Update();
	void MoveTowardsPlayer(Player &player);
};
