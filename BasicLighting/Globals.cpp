#include "Globals.h"

std::string frames;
double lastTime = 0;
double currentTime = glfwGetTime();
int nbFrames = 0;

void Globals::DeltaTime()
{
	currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		// printf and reset timer
		frames = " FPS : " + std::to_string(100000.0 / double(nbFrames));
		nbFrames = 0;
		lastTime = currentTime;
	}
}
