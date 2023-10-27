#include "Renderer.h"
#include "Controllers.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void Renderer::Init()
{
	_window = nullptr;
}

Renderer::Renderer(GLFWwindow* window)
{
	Init();
	_window = window;
	_gui.SetWindow(_window);
}

void Renderer::Initialize()
{

	Texture texture;	
	texture.SetTexture("Assests/ds.jpg");

	glEnable(GL_DEPTH_TEST);

	shader.SetShaders("VertexShader.shader", "FragmentShader.shader");
	shader.UnBind();

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


	cube.SetProgram(shader.shader_program);

	_gui.Init();
}

void Renderer::Update()
{
	glClearColor(0, 0, 0, 5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Bind();
	vertexArray.Bind();

	cube.SetLocation(glm::vec3(2, 2, 2));
	cube.Draw();


	//glfwSetCursorPosCallback(window, mouse_callback);

	Debugger();

	//CAMERA STUFF SHOULD BE ADDED SOMEWHERE ELSE OUT OF HERE
	glm::mat4 view;
	const float radius = 10.0f;
	float camX = sin(glfwGetTime() * 0.01) * radius;
	float camZ = cos(glfwGetTime() * 0.01) * radius;

	view = glm::translate(view, glm::vec3(0.0f, -8.0f, 20.0f));
	view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1200.f / 800.f, 0.1f, 100.0f);

	int viewLoc = glGetUniformLocation(shader.shader_program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shader.shader_program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	//CAMERA STUFF SHOULD BE ADDED SOMEWHERE ELSE OUT OF HERE


	processInput(_window);
	/* Swap front and back buffers */
	glfwSwapBuffers(_window);
	/* Poll for and process events */
	glfwPollEvents();
}

void Renderer::Debugger()
{
	_gui.StartFrames();
	_gui.Begin("the universe is expanding");
	_gui.End();

	_gui.Begin("no its not ! ");
	_gui.End();

	_gui.EndFrames();
}
