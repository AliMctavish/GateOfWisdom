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
	shader.SetShaders("Shaders/VertexShader.shader", "Shaders/FragmentShader.shader");
	lightShader.SetShaders("Shaders/LightVertexShader.shader", "Shaders/LightFragmentShader.shader");
	modelShader.SetShaders("Shaders/ModelVertexShader.shader", "Shaders/ModelFragmentShader.shader");

	testSprite.SetTexture("Assests/aim.png");

	vertexArray.Bind();
	vertexBuffer.Bind();
	vertexArray.UnBind();
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	_gui.Init();
	_machine.SetShader(lightShader);
	_gate.SetShader(lightShader);
	font.SetView(_player.Projection);
	_player.SetShader(shader);

	glfwSwapInterval(0);

	FileManager::LoadFile(lights, cubes, keys, enemies, _machine, _gate, lightShader, shader, modelShader, modelLoader, level,_player);
}

void Renderer::Update()
{
	_player.Update();
	testSprite.Update();
	_gate.Update();

	if (glm::distance(_player.Position, _gate.Position) <= 20)
	{
		_player.inRangeOfGateObject = true;
		if (_player.hasKey)
			if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
			{
				Key IndexedKey = keys[_player.GetPickedKeyIndex()];
				if (_gate.CheckKeyColor(IndexedKey.Color[0], IndexedKey.Color[1], IndexedKey.Color[2]))
				{
					_player.NumberOfKeys += 1;
					_player.hasKey = false;
					_player.CorrectKey = true;
					keys.erase(keys.begin() + _player.GetPickedKeyIndex());
				}
				else
					_player.MaybePickedKeyValid = false;
			}
	}
	else {
		_player.inRangeOfGateObject = false;
		_player.CorrectKey = false;
		_player.MaybePickedKeyValid = true;
	}

	if (glm::distance(_player.Position, _machine.Position) <= 10)
	{
		_player.inRangeOfMachineObject = true;
		if (_player.hasLight && _machine.m_Lights.size() != 2)
		{
			if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
			{
				_machine.AddLight(lights[_player.GetPickedLightIndex()]);
				lights[_player.GetPickedLightIndex()].ResetValues();
				_player.hasLight = false;
			}
		}

		if (_player.hasKey)
			if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
			{
				_machine.AssignToKey(keys[_player.GetPickedKeyIndex()]);
			}


		if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS && !_player.hasKey)
			_machine.ResetLights();
	}
	else
		_player.inRangeOfMachineObject = false;

	_machine.Update();

	//checks if the player has collided with a ground (cube) if so then this 
	//loop will stop and the player will save the collided cube 
	if (!_player.CollidedWithCube)
		for (int i = 0; i < cubes.size(); i++)
		{
			if (_physics.CheckCollision(cubes[i], _player))
			{
				_player.AssignCollidedCube(i);
				break;
			}
		}
	//if the player has collided with a cube it will update the checker only 
	//on this cube ! 
	if (_player.grounded && _player.CollidedWithCube)
		if (!_physics.CheckCollision(cubes[_player.GetCollidedCubeIndex()], _player))
			_player.CollidedWithCube = false;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update();
		if (_gameState.Started)
		{
			enemies[i].MoveTowardsPlayer(_player);
			if (glm::distance(enemies[i].Position, _player.Position) <= 10)
			{
				enemies[i].InRangeWithPlayerPosition = true;
				if (_player.hasKey)
					keys[_player.GetPickedKeyIndex()].SetObjectColor(1, 1, 1);
			}
			else
				enemies[i].InRangeWithPlayerPosition = false;
		}
	}

	if (_gameState.Started)
	{
		_physics.UpdateGravity(_player);

		if (_player.grounded && !_player.isJumping)
		{
			_player.Position.y = cubes[_player.GetCollidedCubeIndex()].Position.y + 7;
			_player.SetMatrix();
		}

		if (_player.Position.y < -100)
		{
			_gameState.Lose = true;
		}

		if (_gameState.Lose)
		{
			this->Clear();
			if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS)
			{
				FileManager::LoadFile(lights, cubes, keys, enemies, _machine, _gate, lightShader, shader, modelShader, modelLoader, level ,_player);
				_gameState.Lose = false;
			}
		}

		if (_gate.m_Colors.size() <= 0)
		{
			this->Clear();
			_gameState.Win = true;

			if (glfwGetKey(_window, GLFW_KEY_ENTER) == GLFW_PRESS)
				this->NextLevel();
		}

		//will stop the object generator only after i make a mode for waves 
		//objectGenerator.SetModelLoader(modelLoader);
		//objectGenerator.GenerateEnemy(enemies, modelShader);
		//objectGenerator.GenerateLight(lights, lightShader);
	}

	for (int i = 0; i < keys.size(); i++)
	{
		keys[i].Update(_player, _window);

		if (!_player.hasKey && !_player.hasLight)
			if (_physics.IsCollided(keys[i].Position, _player.Position, glm::vec3(3, 3, 3)))
			{
				_player.inRangeOfKeyObject = true;
				if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
				{
					keys[i].isPickedUp = true;
					_player.hasKey = true;
					_player.inRangeOfKeyObject = false;
					_player.AssignPickedKey(i);
				}
			}
	}

	for (int i = 0; i < lights.size(); i++)
	{
		// clean the code soon
		if (!_player.hasLight && !_player.hasKey)
			if (glm::distance(lights[i].Position, _player.Position) <= 10)
			{
				if (!lights[i].isPushing && !lights[i].isPickedUp)
					_player.inRangeOfLightObject = true;

				if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS && !_player.hasLight)
				{
					_player.hasLight = true;
					lights[i].isPickedUp = true;
					_player.AssignPickedLight(i);
				}
			}

		lights[i].Update(_player, _window);


		if (lights[i].isPushing)
		{
			lights[i].Push();
			if (glm::distance(lights[i].Position, _player.Position) > 300)
			{
				lights[i].ResetValues();
				continue;
			}
		}
		//this part of the code will override the update method of the light 
		//in the matrix part
		//when you are not picking up the object ! 
		if (!lights[i].isPickedUp && !lights[i].isPushing)
			lights[i].SinMove();
	}


	for (Cube& cube : cubes)
	{
		cube.Update();

		for (Light& light : lights)
			if (light.isPushing)
				if (_physics.IsCollidedTest(cube.Position, light.Position, cube.Size))
				{
					light.isPushing = false;
					light.isPickedUp = false;
				}
	}
	if (!_gameState.TextMode)
		processInput(_window, _player);
}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	testSprite.Draw();

	modelShader.Bind();
	modelShader.SetMat4("view", _player.View);
	modelShader.SetMat4("projection", _player.Projection);


	for (Enemy& enemy : enemies)
		enemy.Draw(modelLoader);

	modelShader.UnBind();

	vertexArray.Bind();
	shader.Bind();
	_player.Draw();

	for (int i = 0; i < lights.size(); i++)
	{
		shader.setVec3("lightPos[" + std::to_string(i) + ']', lights[i].Position);
		shader.setVec3("lightColor[" + std::to_string(i) + ']', glm::vec3(lights[i].Color[0], lights[i].Color[1], lights[i].Color[2]));
	}

	shader.setInt("LightCount", lights.size());

	for (Cube& cube : cubes)
		cube.Draw();

	shader.UnBind();

	lightShader.Bind();
	lightShader.SetMat4("view", _player.View);
	lightShader.SetMat4("projection", _player.Projection);

	for (Light& light : lights)
		light.Draw(modelLoader);

	//this is a tricky solution for now ! 
	if (!_gameState.Lose || !_gameState.Win)
	{
		_gate.Draw(modelLoader);
		_machine.Draw(modelLoader);
	}

	for (Key& key : keys)
		key.Draw(modelLoader);

	lightShader.UnBind();

	if (level != "Level0")
	{
		font.Draw("number of enemies : " + std::to_string(enemies.size()), -0.8, 0.8, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));
		font.Draw("Number Of Keys Left : " + std::to_string(_gate.RequiredColors.size()), -0.8, 0.9, 0.001f, glm::vec3(0.9, 0.9f, 0.1f));
	}


	if (_player.inRangeOfKeyObject)
		font.Draw("Press 'E' to collect", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

	if (!_gameState.Win || !_gameState.Lose)
		if (_player.inRangeOfGateObject)
		{
			if (!_player.hasKey && !_player.CorrectKey)
				font.Draw("You should provide a key to open the gate", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));
			else if (_player.hasKey && _player.MaybePickedKeyValid)
				font.Draw("Press 'E' to put the key", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

			if (!_player.MaybePickedKeyValid)
				font.Draw("Key color not match !", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

			if (_player.CorrectKey)
			{
				font.Draw("Well Done!", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));
				font.Draw(" ' " + std::to_string(_gate.RequiredColors.size()) + " ' " + " keys left !", -0.4, 0.6, 0.001f, glm::vec3(0.1, 0.8f, 0.2f));
			}
		}

	if (_player.inRangeOfLightObject)
		font.Draw("Press 'E' to pick up", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

	if (_player.inRangeOfMachineObject && !_player.hasLight && _machine.m_Lights.size() == 0)
		font.Draw("You need light to use this machine", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

	if (_player.inRangeOfMachineObject && _player.hasKey && _machine.m_Lights.size() > 0)
		font.Draw("Press 'E' to modify key color", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

	if (_player.inRangeOfMachineObject && _player.hasLight)
		font.Draw("Press 'E' to plug in the light", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

	if (_machine.m_Lights.size() == 2 && _player.inRangeOfMachineObject && !_player.hasKey)
	{
		font.Draw("The machine is full", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));
		font.Draw("Press 'R' to reset the machine", -0.4, 0.6, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));
	}

	//game states
	if (_gameState.Lose)
		font.Draw("You are dead click 'R' to restart !", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));

	if (_gameState.Win)
	{
		font.Draw("You have passed the gate !", -0.4, 0.4, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));
		font.Draw("Press 'Enter' to move to the next level!", -0.4, 0.1, 0.001f, glm::vec3(0.5, 0.8f, 0.2f));
	}

	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		_gameState.Started = false;

	if (!_gameState.Started && !_gameState.EditMode)
	{
		if (!_gameState.About)
		{
			font.Draw("Gate Of Wisdom", -0.35, 0.4, 0.002f, glm::vec3(0.1, 0.6f, 0.2f));

			font.Draw("1- Start Game", -0.35, 0.0, 0.0015f, glm::vec3(0.1, 0.6f, 0.2f));
			font.Draw("2- Edit Mode", -0.35, -0.1, 0.0015f, glm::vec3(0.1, 0.6f, 0.2f));
			font.Draw("3- About", -0.35, -0.2, 0.0015f, glm::vec3(0.1, 0.6f, 0.2f));
			font.Draw("4- Exit", -0.35, -0.3, 0.0015f, glm::vec3(0.1, 0.6f, 0.2f));

			if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS)
			{
				if (level == "Level0")
				{
					this->Clear();
					this->NextLevel();
					_gameState.Started = true;
					_gameState.EditMode = false;
				}
				else
					_gameState.Started = true;
			}

			if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS)
			{
				this->Clear();
				_gameState.EditMode = true;
			}
			if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS)
				_gameState.About = true;
			if (glfwGetKey(_window, GLFW_KEY_4) == GLFW_PRESS)
				glfwSetWindowShouldClose(_window, 1);
		}

		if (_gameState.About == true)
		{
			font.Draw("This game is made by 'ali fadil' ", -0.6, 0.1, 0.0012f, glm::vec3(0.1, 0.6f, 0.2f));
			font.Draw("Using a personal game engine built with opengl and c++", -0.6, -0.05, 0.0012f, glm::vec3(0.1, 0.6f, 0.2f));
			if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				_gameState.About = false;
		}
	}
	if (!_gameState.Started)
	{
		//after adding this function it gave me the ability to control the mouse callback !?
		glfwSetCursorEnterCallback(_window, GLFW_FALSE);
		glfwSetCursorPosCallback(_window, NULL);
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (_gameState.EditMode)
			_gui.Debugger(lights, cubes, enemies, keys, shader, lightShader, modelShader, modelLoader, _machine, _gate, _gameState , level,_player);

		_gui.SetupImGuiStyle(true, 1);
	}
	else {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(_window, mouse_callback);
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(_window);
	/* Poll for and process events */
	glfwPollEvents();
}

//there is memory leak in clearing things , must be somthing still exist
void Renderer::Clear()
{
	lights.clear();
	cubes.clear();
	keys.clear();
	enemies.clear();
	_gate.RequiredColors.clear();
	_player.ResetValues();
}

void Renderer::NextLevel()
{
	level.back()++;
	FileManager::LoadFile(lights, cubes, keys, enemies, _machine, _gate, lightShader, shader, modelShader, modelLoader, level,_player);
	_gameState.Win = false;
	_gameState.Started = true;
}
