#pragma once
#include "BaseObject.h"
#include "ModelLoader.h"



class Key : public BaseObject{
private : 
	uint16_t m_TextureIndex;
public : 
	uint16_t inline GetTexutreIndex() { return m_TextureIndex; }
	int objectId;
	Key();
	void Init();
	void Update();
	void Draw(ModelLoader *modelLoader);
};