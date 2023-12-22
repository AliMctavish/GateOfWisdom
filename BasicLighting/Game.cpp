#include "Game.h"

Game::Game(GLFWwindow* window)
{
	_window = window;
}

void Game::Start()
{
	Renderer renderer(_window);

	renderer.Initialize();

	std::string frames;
	double deltaTime = 0;
	double lastTime = 0;
	double currentTime = glfwGetTime();
	int nbFrames = 0;


	while (!glfwWindowShouldClose(_window))
	{
		currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0 / 60.0f) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			frames = " FPS : " + std::to_string(100000.0 / double(nbFrames));
			deltaTime = 100000.0 / double(nbFrames);
			nbFrames = 0;
			lastTime = currentTime;
			
			renderer.Update(frames);
		}
		renderer.Draw();
	}
}
