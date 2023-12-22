#pragma once
#include "BaseObject.h"


class Machine : public BaseObject {
private:
	uint16_t m_TextureIndex;
public:
	uint16_t inline GetTexutreIndex() { return m_TextureIndex; }
	int objectId;
	float rotateY,angle;
	Machine();
	void Init();

	void Update();
	void RotateOnY(float angle);
	void Draw();
};
