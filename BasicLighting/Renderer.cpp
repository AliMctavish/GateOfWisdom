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
	_physics.SetVariables(_window, _player);
	_gui.SetWindow(_window);
	modelLoader.InitializeModels();
}

void Renderer::Initialize()
{
	shader.SetShaders("VertexShader.shader", "FragmentShader.shader");
	lightShader.SetShaders("LightVertexShader.shader", "LightFragmentShader.shader");
	modelShader.SetShaders("ModelVertexShader.shader", "ModelFragmentShader.shader");




	vertexArray.Bind();
	vertexBuffer.Bind();

	vertexArray2.Bind();

	//vertexBuffer2.Bind();

	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	lightShader.UnBind();
	_gui.Init();

	shader.Bind();
	modelShader.Bind();

	FileManager::LoadFile(lights, cubes, lightShader, shader, "Level1");
}

std::string frames;
double deltaTime = 0;
double lastTime = 0;
double currentTime = glfwGetTime();
int nbFrames = 0;

void Renderer::Update()
{
	currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		// printf and reset timer
		frames = " FPS : " + std::to_string(100000.0 / double(nbFrames));
		deltaTime = 100000.0 / double(nbFrames);
		nbFrames = 0;
		lastTime = currentTime;
	}

	_player.Update();

	for (Cube& cube : cubes)
	{
		cube.Update();

		if (_physics.CheckCollision(cube, _player))
			break;
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update();
		enemies[i].MoveTowardsPlayer(_player);

		for (int j = 0; j < lights.size(); j++)
		{
			if (enemies.size() > 0 && lights.size() > 0)
				if (_physics.IsCollidedTest(enemies[i].Position, lights[j].Position, enemies[i].Size) && lights[j].isPushing)
				{
					enemies.erase(enemies.begin() + i);
					lights.erase(lights.begin() + j);
				}
		}
	}


	if (gameStarted == true)
	{
		_physics.UpdateGravity(deltaTime, _player);
		objectGenerator.GenerateEnemy(enemies, modelShader);
		objectGenerator.GenerateLight(lights, lightShader);
	}

	for (int i = 0; i < lights.size(); i++)
	{
		// clean the code soon
		_physics.CheckLightCollision(lights[i], _player);

		lights[i].Update(_player, _window);

		if (lights[i].isPushing)
		{
			lights[i].Position += 0.5f * lights[i].direction;
			if (glm::distance(lights[i].Position, _player.Position) > 300)
			{
				lights.erase(lights.begin() + i);
				continue;
			}
		}

	}
}

double posx = 2;
double posy = 2;
int index = 0;
void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_player.SetMatrix();

	//why the fuck there is nothing showing on the screen ?????????????
	//okay .... basically you should send the view matrix for the camera !!!-_-
	modelShader.Bind();

	//abstract this motherfucker plz !.
	modelShader.SetMat4("view", _player.View);
	modelShader.SetMat4("projection", _player.Projection);

	for (Enemy& enemy : enemies)
	{
		enemy.Draw(modelLoader);
	}
	modelShader.UnBind();



	shader.Bind();

	shader.SetMat4("view", _player.View);
	shader.SetMat4("projection", _player.Projection);
	shader.setVec3("viewPos", _player.Position);
	vertexArray.Bind();

	//too many for loops for testing perposses idk how to write perpoesrpes
	for (int i = 0; i < lights.size(); i++)
	{
		shader.setVec3("lightPos[" + std::to_string(i) + ']', lights[i].Position);
		shader.setVec3("lightColor[" + std::to_string(i) + ']', glm::vec3(lights[i].Color[0], lights[i].Color[1], lights[i].Color[2]));
	}

	shader.setInt("LightCount", lights.size());


	for (Cube& cube : cubes)
	{
		for (Light& light : lights)
		{
			//hmmmm is this the way i should work with ? 
			if (_physics.IsCollidedTest(cube.Position, light.Position, cube.Size))
				light.isPushing = false;
		}
		cube.Draw();
	}
	shader.UnBind();

	lightShader.Bind();
	lightShader.SetMat4("view", _player.View);
	lightShader.SetMat4("projection", _player.Projection);

	for (Light& light : lights)
	{
		if (!light.isPickedUp)
			light.SinMove();

		light.Draw(modelLoader);
	}
	lightShader.UnBind();



	//why using second vertex array ? 
	//vertexArray2.Bind();

	if (gameStarted == false)
	{
		//after adding this function it gave me the ability to control the mouse callback !?
		glfwSetCursorEnterCallback(_window, GLFW_FALSE);

		glfwSetCursorPosCallback(_window, NULL);
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_gui.Debugger(lights, cubes, enemies, shader, lightShader, modelShader, frames, gameStarted);
		_gui.SetupImGuiStyle(true, 1);


		if (glfwGetKey(_window, GLFW_KEY_P) == GLFW_PRESS)
		{
			Cube cube;
			cube.SetShader(shader);
			cube.Position = _player.Position;
			cube.SetName("test" + std::to_string(cubes.size()));
			cube.SetTextureData(1);
			cubes.push_back(cube);
		}
		if (glfwGetKey(_window, GLFW_KEY_L) == GLFW_PRESS)
		{
			Light light;
			light.SetShader(shader);
			light.Position = _player.Position;
			light.SetName("test" + std::to_string(cubes.size()));
			lights.push_back(light);
		}
	}
	else
	{
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(_window, mouse_callback);

		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			gameStarted = false;
		//glfwSetWindowShouldClose(window, true);
	}
	processInput(_window, deltaTime, _player);
	/* Swap front and back buffers */
	glfwSwapBuffers(_window);
	/* Poll for and process events */
	glfwPollEvents();
}

