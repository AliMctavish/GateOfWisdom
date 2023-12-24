#pragma once
#include "BaseObject.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

class RequiredColor : public BaseObject{
public :
	VertexBuffer vertexBuffer = VertexBuffer(VertexType::Surface_Type);
	VertexArray vertexArray;
	int objectId;
	RequiredColor();
	void Init();
	void Update();
	void Draw();
};
