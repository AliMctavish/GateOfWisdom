#pragma once
#include "RequiredColor.h"
#include <array>


class Gate : public BaseObject{
private : 
	std::array<float, 3> m_ResultantColor = {0,0,0};
	bool m_IsColorMix = false;
	bool m_HasSavedValue = false;
	uint16_t NumberOfKeysLeft = 7;
	std::array<float,3> CalculateColorValues(float r, float g, float b, float r1, float g1, float b1);
	bool CheckColorValidity(float r, float g, float b , float r1 , float b1 , float g1);
public :
	std::vector<std::array<float, 3>> m_Colors;
	std::vector<RequiredColor> RequiredColors;
	unsigned int objectId;
	Gate();
	bool CheckKeyColor(float r, float g , float b);
	void Init();
	void Update();
	void ProcessColor(float r , float g, float b);
	void Draw(ModelLoader& modelLoader);
};
