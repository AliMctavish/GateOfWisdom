#include "Game.h"

Game::Game(GLFWwindow* window)
{
	_window = window;
}

void Game::Start()
{
	Renderer renderer(_window);

	renderer.Initialize();

	while (!glfwWindowShouldClose(_window))
	{
		renderer.Update();
	}
}
 