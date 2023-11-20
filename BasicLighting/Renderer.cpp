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
	texture.SetTexture("Assests/grd.jpg", 1);
	texture2.SetTexture("Assests/bounds.png", 0);
	vertexBuffer.SetCubeWithNormalsAndTexturesAttributes();

	//vertexBuffer.SetCubeWithNormalsAttributs();
	//TODO: fix the buffer its not working well when you add textures

	vertexArray2.Bind();
	vertexBuffer2.Bind();
	vertexBuffer2.SetCubeAttributes();

	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


	Cube lightSource;
	lightSource.SetProgram(lightShader.shader_program);
	lightSource.Position = glm::vec3(50, 10, 20);
	lightSource.SetName("light");
	lights.push_back(lightSource);

	//debugging
	Cube cube;
	cube.SetProgram(shader.shader_program);
	cube.Size = glm::vec3(60, 5, 60);
	cube.Position = glm::vec3(50, -10, 20);
	cube.RotateOnY(90);
	cube.SetName("test" + std::to_string(cubes.size()));
	cubes.push_back(cube);
	lightShader.UnBind();
	_gui.Init();

	shader.Bind();
	// is this a texture ? :| 
	//texture for diffuse mapping
	shader.setInt("material.Diffuse", 0);
	//texture for specular effect
	shader.setInt("material.Specular", 1);
}

float bgColor[] = { 0,0,0 };
std::string frames;
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
	projection = glm::perspective(glm::radians(45.0f), 1200.f / 800.f, 0.1f, 100.0f);
	//CAMERA STUFF SHOULD BE ADDED SOMEWHERE ELSE OUT OF HERE

	shader.Bind();
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);
	vertexArray.Bind();
	shader.setVec3("viewPos", cameraPos);
	//should we bind textures in loop ? 
	texture.Bind();
	texture2.Bind();


	//too many for loops for testing perposses idk how to write perpoesrpes
	for (int i = 0; i < lights.size(); i++)
	{
		shader.setVec3("lightPos[" + std::to_string(i) + ']', lights[i].Position);
		shader.setVec3("lightColor[" + std::to_string(i) + ']', glm::vec3(lights[i].Color[0], lights[i].Color[1], lights[i].Color[2]));
	}

	shader.setInt("LightCount", lights.size());

	for (Cube cube : cubes)
	{
		cube.Update();
		shader.setVec3("light.ambiant", cube.material.Ambiant);
		shader.setVec3("light.diffuse", cube.material.Diffuse);
		shader.setVec3("light.specular", cube.material.Specular);
		shader.setFloat("material.Shininess", cube.material.shininess);
		shader.SetMat4("model", cube.GetModel());
		cube.UseColor("objectColor");
		cube.Draw();

		//todo make colliders 
		// also we should make the jumping crushing 
		// also doing the camera for the player 
		// annddd too much other stuff ! !! !
		if (gameStarted == true)
		{
			if (cameraPos.y < cube.Position.y + 5)
				cameraPos.y;
			else
				cameraPos.y -= 0.1f;
		}
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
		Debugger();
	else
	{
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(_window, mouse_callback);
	}

	processInput(_window, currentTime);
	/* Swap front and back buffers */
	glfwSwapBuffers(_window);
	/* Poll for and process events */
	glfwPollEvents();
}

void Renderer::Debugger()
{
	_gui.StartFrames();

	//why the variables not chagnging in here?
	_gui.Begin("Objects Coordinates");



	for (int i = 0; i < cubes.size(); i++)
	{
		ImGui::Text(cubes[i].GetName().c_str());
		ImGui::PushID(cubes[i].cubeId);
		ImGui::SliderFloat("Move2 On X", &cubes[i].Position.x, -50, 50, "%.3f", 0);
		ImGui::SliderFloat("Move2 On Y", &cubes[i].Position.y, -50, 50, "%.3f", 0);
		ImGui::SliderFloat("Move2 On Z", &cubes[i].Position.z, -50, 50, "%.3f", 0);
		ImGui::SliderFloat("Rsizex object", &cubes[i].Size.x, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizey object", &cubes[i].Size.y, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizez object", &cubes[i].Size.z, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rotate on x Axis", &cubes[i].rotateX, 0, 10, "%.3f", 0);
		ImGui::SliderFloat("Rotate on z Axis", &cubes[i].rotateY, 0, 10, "%.3f", 0);
		ImGui::Text("Object Material");
		ImGui::ColorEdit3(cubes[i].GetName().c_str(), cubes[i].Color, 0);
		ImGui::SliderFloat2("Ambiant", &cubes[i].material.Ambiant[0], 0, 10, "%.3f", 0);
		ImGui::SliderFloat2("Diffuse", &cubes[i].material.Diffuse[0], 0, 10, "%.3f", 0);
		ImGui::SliderFloat2("Specular", &cubes[i].material.Specular[0], 0, 10, "%.3f", 0);
		ImGui::SliderFloat("Shininess", &cubes[i].material.shininess, 0, 100, "%.3f", 0);
		ImGui::PopID();
	}

	_gui.End();

	_gui.Begin("Object Coordinates2");

	for (int i = 0; i < lights.size(); i++)
	{
		ImGui::Text(lights[i].GetName().c_str());
		ImGui::PushID(lights[i].cubeId);
		ImGui::ColorEdit3("Object2 Color", lights[i].Color, 0);

		ImGui::SliderFloat("Move On X", &lights[i].Position.x, -50, 50, "%.3f", 0);
		ImGui::SliderFloat("Move On Y", &lights[i].Position.y, -100, 100, "%.3f", 0);
		ImGui::SliderFloat("Move On Z", &lights[i].Position.z, -50, 50, "%.3f", 0);

		ImGui::SliderFloat("2Rsize object", &lights[i].Size.x, 0, 10, "%.3f", 1);
		ImGui::SliderFloat("2Rotate on x Axis", &lights[i].rotateX, 0, 10, "%.3f", 1);
		ImGui::SliderFloat("2Rotate on y Axis", &lights[i].rotateY, 0, 10, "%.3f", 1);
		ImGui::SliderFloat("2Rotate on z Axis", &lights[i].rotateZ, 0, 10, "%.3f", 1);
		ImGui::PopID();

	}
	_gui.End();

	_gui.Begin("World Settings");

	ImGui::Text(frames.c_str());

	if (ImGui::Button("Create Cube", Button_Size))
	{
		Cube cube;
		cube.SetProgram(shader.shader_program);
		cube.SetName("test" + std::to_string(cubes.size()));
		cubes.push_back(cube);
	}

	if (ImGui::Button("Create Light", Button_Size))
	{
		Cube cube;
		cube.SetProgram(lightShader.shader_program);
		cube.SetName("test" + std::to_string(cubes.size()));
		lights.push_back(cube);
	}

	if (ImGui::Button("Start Game", Button_Size))
		gameStarted = true;


	if (ImGui::Button("Save Map", Button_Size))
	{
		std::ofstream newStream("Data.txt");
		newStream << "#Light_Coordinates" << std::endl;
		for (Cube light : lights)
		{
			newStream << light.Position.x << " " <<
				light.Position.y << " " <<
				light.Position.z << " " <<
				light.Color[0] << " " <<
				light.Color[1] << " " <<
				light.Color[2] << std::endl;


			std::cout << "saving data" << std::endl;
		}
		newStream.close();
	}

	if (ImGui::Button("Load Map", Button_Size))
	{
		std::ifstream newStream("Data.txt");
		std::string line;
		bool isColors = false;

		while (std::getline(newStream, line))
		{
			if (line.find("#Light_Coordinates") != std::string::npos)
				continue;

			std::stringstream subStream(line);
			std::string subString;
			std::vector<std::string> stringList;

			while (std::getline(subStream, subString, ' '))
			{
				//std::cout << "Loading data into project" << std::endl;
				//std::cout << subString << std::endl;
				stringList.push_back(subString);
			}

			Cube cube;
			cube.SetProgram(lightShader.shader_program);

			cube.Position = glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2]));
			cube.SetObjectColor(std::stof(stringList[3]), std::stof(stringList[4]), std::stof(stringList[5]));


			//cube.SetObjectColor();
			cube.SetName("test" + std::to_string(cubes.size()));
			lights.push_back(cube);
		}

		newStream.close();
	}


	ImGui::ColorEdit3("BackgroundColor", bgColor, 0);

	_gui.End();

	_gui.EndFrames();
}

