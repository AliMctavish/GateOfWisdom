#pragma once
#include "BaseObject.h"
#include "ModelLoader.h"


//enmey class that handles enemies :3 
class Enemy : public BaseObject{
private : 
public : 
	unsigned int objectId;
	Enemy();
	void Draw(ModelLoader& objectModel);
	void Update();
	void MoveTowardsPlayer();
};
