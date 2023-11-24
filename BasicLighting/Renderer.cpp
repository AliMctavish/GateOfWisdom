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
	_physics.SetWindow(_window);
	_gui.SetWindow(_window);
}

void Renderer::Initialize()
{
	shader.SetShaders("VertexShader.shader", "FragmentShader.shader");
	lightShader.SetShaders("LightVertexShader.shader", "LightFragmentShader.shader");

	vertexArray.Bind();
	vertexBuffer.Bind();
	vertexBuffer.SetCubeWithNormalsAndTexturesAttributes();

	vertexArray2.Bind();
	vertexBuffer2.Bind();
	vertexBuffer2.SetCubeAttributes();

	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	lightShader.UnBind();
	_gui.Init();

	shader.Bind();
}

float bgColor[] = { 0,0,0 };
std::string frames;
double deltaTime = 0;
double lastTime = 0;
double currentTime = glfwGetTime();
int nbFrames = 0;


void Renderer::Update()
{
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		// printf and reset timer
		frames = " FPS : " + std::to_string(100000.0 / double(nbFrames));
		deltaTime = 100000.0 / double(nbFrames);
		nbFrames = 0;
		lastTime = currentTime;
	}

	//CAMERA STUFF SHOULD BE ADDED SOMEWHERE ELSE OUT OF HERE
	glm::mat4 view;
	const float radius = 10.0f;
	float camX = sin(glfwGetTime() * 0.01) * radius;
	float camZ = cos(glfwGetTime() * 0.01) * radius;
	view = glm::translate(view, glm::vec3(-10.0f, 10.0f, 20.0f));
	view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(70.0f), 1200.f / 800.f, 0.1f, 100.0f);
	//CAMERA STUFF SHOULD BE ADDED SOMEWHERE ELSE OUT OF HERE
	shader.Bind();
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);
	vertexArray.Bind();
	shader.setVec3("viewPos", cameraPos);

	//too many for loops for testing perposses idk how to write perpoesrpes
	for (int i = 0; i < lights.size(); i++)
	{
		shader.setVec3("lightPos[" + std::to_string(i) + ']', lights[i].Position);
		shader.setVec3("lightColor[" + std::to_string(i) + ']', glm::vec3(lights[i].Color[0], lights[i].Color[1], lights[i].Color[2]));
	}

	shader.setInt("LightCount", lights.size());

	for (Cube& cube : cubes)
	{
		cube.Update();
		shader.setVec3("light.ambiant", cube.material.Ambiant);
		shader.setVec3("light.diffuse", cube.material.Diffuse);
		shader.setVec3("light.specular", cube.material.Specular);
		shader.setFloat("material.Shininess", cube.material.shininess);
		shader.SetMat4("model", cube.GetModel());
		shader.setInt("texture0", cube.texture.m_TextureIndex);
		cube.texture.Bind();
		cube.UseColor("objectColor");

		if (gameStarted == true)
			_physics.CheckCollision(cube, cameraPos, deltaTime);

		
		
		cube.Draw();
	}


	lightShader.Bind();

	lightShader.SetMat4("view", view);
	lightShader.SetMat4("projection", projection);

	for (int i = 0; i < lights.size(); i++)
	{
		lights[i].Update();
		//lights[i].SinMove();
		lightShader.SetMat4("model", lights[i].GetModel());
		lights[i].UseColor("objectColor");
		lights[i].Draw();
	}

	vertexArray2.Bind();

	if (gameStarted == false)
	{
		_gui.Debugger(lights, cubes, shader, lightShader, frames, gameStarted);
	}
	else
	{
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(_window, mouse_callback);
	}
	processInput(_window, deltaTime);
	/* Swap front and back buffers */
	glfwSwapBuffers(_window);
	/* Poll for and process events */
	glfwPollEvents();
}

