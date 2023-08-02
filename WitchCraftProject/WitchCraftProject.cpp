#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH  640



void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "the lagacy", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "something went wrong with glad !" << std::endl;
		return -1;
	}

	//HERE IS THE DRAWING DETAILS
	float vertices[] =
	{
		-0.5,-0.5,0,
		0.5,-0.5,0,
		0.5,0.5,0,
	};

	unsigned int VBO = 0;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);








	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Make the window's context current */

	GLfloat number = 0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		number += 0.001;
		glClearColor(0, sin(number), 0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}