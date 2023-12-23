#pragma once
#include "BaseObject.h"


class Gate : public BaseObject{
private :
	unsigned int objectId;
public :
	Gate();
	void Init();
	void Update();
	void Draw();
	void Draw(ModelLoader &modelLoader);
};
