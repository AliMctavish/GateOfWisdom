#pragma once
#include "BaseObject.h"
#include "Key.h"
#include "Light.h"


class Machine : public BaseObject {
private:
	bool m_HasFirstColor = false;
	bool m_HasSecondColor = false;
	float m_ResultantColor[3] = {0,0,0};
	uint16_t m_TextureIndex;
	glm::vec3 m_Direction; 
	glm::vec3 m_ForwardDirection = glm::vec3(0, 0, 2);
	glm::vec3 m_RightDirection = glm::vec3(1, 0, 0);
	void UpdateLightsPosition();
	void AddSlot(glm::vec3 position);
public:
	std::vector<Light> m_Lights;
	uint16_t inline GetTexutreIndex() { return m_TextureIndex; }
	int objectId;
	float rotateY,angle;
	bool MachineIsFull = false;
	Machine();
	void ResetLights();
	void AddLight(Light &light);
	void Init();
	void AssignToKey(Key &key);
	void CalculateColorValue(float x,float y, float z,float x1 , float y1 , float z1);
	void Update();
	void RotateOnY(float angle);
	void Draw(ModelLoader& modelLoader);
};
