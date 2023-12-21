#pragma once
#include "BaseObject.h"
#include "ModelLoader.h"
#include "Player.h"



//enmey class that handles enemies :3 
class Enemy : public BaseObject{
public : 
	unsigned int objectId;
	Enemy();
	void SetRandomLocation();
	void Draw();
	void Update();
	void MoveTowardsPlayer(Player &player);
};
