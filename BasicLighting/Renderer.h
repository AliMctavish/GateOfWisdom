#pragma once
#include "Shader.h"

class Renderer {
private:
	GLFWwindow* window;
public:
	Renderer();
	void Init();
	void StartRenderer();
	void UpdateRenderer();


};
