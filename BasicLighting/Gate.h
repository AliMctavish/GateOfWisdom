#pragma once
#include "BaseObject.h"


class Gate : public BaseObject{
private : 
	float m_ResultantColor[3] = {0,0,0};
public :
	unsigned int objectId;
	Gate();
	void Init();
	void Update();
	void Draw();
	void CalculateColorValue();
	void Draw(ModelLoader &modelLoader);
};
