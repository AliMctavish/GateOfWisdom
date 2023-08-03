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


	const char* vertex_shader_source = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 vecPos;\n"
		"void main()\n"
		"{"
		"gl_Position = vec4(vecPos.x,vecPos.y,vecPos.z,1.0);\n"
		"}";

	const char* fragment_shader_source =
		"#version 330 core\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{"
		"fragColor = vec4(1.0,0,1.0,1.0);"
		"}";



	unsigned int vertex_shader;

	vertex_shader =  glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source,NULL);
	glCompileShader(vertex_shader);


	int success;
	char infoLog[512];
	glGetShaderiv(vertex_shader,GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512,NULL, infoLog);
		std::cout << "something wrong with your vertex shader" << infoLog << std::endl;
	}

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	int success2;
	char infoLog2[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success2);
	if (!success2)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog2);
		std::cout << "something wrong with your fragment shader" << infoLog2 << std::endl;
	}



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