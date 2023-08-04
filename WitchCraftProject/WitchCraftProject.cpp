#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

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

std::string ReadShaderFromFile(std::string fileName)
{
	std::ifstream fileStream;
	std::stringstream result;
	std::string resultAsString;

	fileStream.open(fileName);

	result << fileStream.rdbuf();

	
	fileStream.close();
	return resultAsString;
};

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
		//POSITIONS   //COLORS
		-0.5,-0.5,0,  1,0,0,
		0.5,-0.5,0,	  0,1,0,
		0,0.5,0,      0,0,1,
	};
	unsigned int indecies[] =
	{
		0,1,2,
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int EAO;
	glGenBuffers(1, &EAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), &indecies, GL_STATIC_DRAW);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (3* sizeof(float)));
	glEnableVertexAttribArray(1);

	
	std::string vertex_shader_source =  ReadShaderFromFile("VertexShader.shader");
	std::string fragment_shader_source = ReadShaderFromFile("FragmentShader.shader");

	const char* vertex_shader_source_result = vertex_shader_source.c_str();
	const char* fragment_shader_source_result = vertex_shader_source.c_str();


	std::cout << fragment_shader_source_result;
	unsigned int vertex_shader;

	vertex_shader =  glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source_result, NULL);
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
	glShaderSource(fragment_shader, 1, &fragment_shader_source_result, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "something wrong with your fragment shader" << infoLog << std::endl;
	}

	unsigned int shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "something wrong with the shader program" << infoLog << std::endl;
	}

	glUseProgram(shader_program);


	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);



	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Make the window's context current */

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);

		float glTime = glfwGetTime();
		float uniformValue = glGetUniformLocation(shader_program, "colorTest");
		glUniform4f(uniformValue, sin(glTime), 0, 1, 1);


		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		processInput(window);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}