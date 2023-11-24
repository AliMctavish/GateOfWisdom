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


	Light lightSource;
	lightSource.SetProgram(lightShader.shader_program);
	lightSource.Position = glm::vec3(50, 10, 20);
	lightSource.SetName("light");
	lights.push_back(lightSource);

	//debugging
	//Cube cube;
	//cube.SetProgram(shader.shader_program);
	//cube.Size = glm::vec3(60, 5, 60);
	//cube.Position = glm::vec3(50, -10, 20);
	//cube.RotateOnY(90);
	//cube.SetName("test" + std::to_string(cubes.size()));
	//cubes.push_back(cube);
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
bool grounded = false;
bool isJumping = false;
float acceleration = 0.05f;

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

		int cubeXX = cube.Position.x + cube.Size.x;
		int cubeX = cube.Position.x;
		int cubeYY = cube.Position.y + cube.Size.y + 1;
		int cubeY = cube.Position.y;
		int cubeZZ = cube.Position.z + cube.Size.z;
		int cubeZ = cube.Position.z;

		int cameraXX = cameraPos.x + 3;
		int cameraX = cameraPos.x;
		int cameraYY = cameraPos.y + 2;
		int cameraY = cameraPos.y;
		int cameraZZ = cameraPos.z + 2;
		int cameraZ = cameraPos.z;





		if (gameStarted == true)
		{
			/*if (cubeXX < cameraX && cubeZZ < cameraZ && cubeYY < cameraY &&
				cubeX < cameraXX && cubeY < cameraYY && cubeZ < cameraZZ)
			{
				cameraPos.y;
				std::cout << "triggerd !" << std::endl;

			}*/
			if (grounded == false || cube.collided)
			{
				if (cameraY < cubeYY && cubeY < cameraYY && cameraX < cubeXX
					&& cubeX < cameraXX && cameraZ < cubeZZ && cubeZ < cameraZZ)
				{

					float distance = cameraPos.y - cube.Position.y;
					cameraPos.y = cube.Position.y + distance;
					std::cout << "triggerd !" << std::endl;
					std::cout << distance << std::endl;

					//std::cout << acceleration << std::endl;

					cube.collided = true;
					grounded = true;
					isJumping = false;
					acceleration = 0.05f;
				}
				else
				{
					grounded = false;
					cube.collided = false;
				}
			}

			if (grounded == false)
				cameraPos.y -= 0.00001f * deltaTime;

			if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				cube.collided = false;
				grounded = false;
				isJumping = true;
			}

			if (isJumping)
			{
				cameraPos.y += acceleration;
				acceleration -= 0.00005;
			}

		}
		//std::cout << cube.Position.x << std::endl;
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

