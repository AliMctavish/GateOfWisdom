#pragma once
#include "Shader.h"

static class Globals {
private : 
	double m_LastTime;
	double m_CurrentTime;
	int m_NbFrames;
	std::string m_Frames;
public : 
	void static DeltaTime();
};
