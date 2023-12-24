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
        deltaTime = currentTime - lastTime;
        nbFrames++;

        if (deltaTime >= 1.0 / 68.0f) {
            frames = " FPS : " + std::to_string(1.0 / deltaTime);
            nbFrames = 0;
            lastTime = currentTime;
            std::cout << deltaTime << std::endl;
            renderer.Update(frames);
        }

        renderer.Draw();
    }
}
