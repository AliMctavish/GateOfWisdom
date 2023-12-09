#pragma once
#include "BaseObject.h"
#include "ModelLoader.h"
#include "Player.h"



//enmey class that handles enemies :3 
class Enemy : public BaseObject{
private : 
public : 
	unsigned int objectId;
	Enemy();
	void SetRandomLocation();
	void EnemyGenerator(std::vector<Enemy> enemies);
	void Draw(ModelLoader& objectModel);
	void Update();
	void MoveTowardsPlayer(Player &player);
};
