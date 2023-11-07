#pragma once
#include <iostream>
#include <vector>
#include "Renderer.h"

class Game {
public:
	GLFWwindow* _window;
	Game(GLFWwindow* window);

	void Start();
};


