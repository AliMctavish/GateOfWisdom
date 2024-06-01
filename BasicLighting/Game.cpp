#include "Game.h"

Game::Game(GLFWwindow* window)
{
	_window = window;
}



void Game::Start()
{
	Renderer renderer(_window);

	renderer.Initialize();

	double deltaTime = 0;
	double lastTime = 0;
	double currentTime = glfwGetTime();


    while (!glfwWindowShouldClose(_window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;

        if (deltaTime >= 0.02f) {
            lastTime = currentTime;
            renderer.Update();
        }

        renderer.Draw();
    }
}
