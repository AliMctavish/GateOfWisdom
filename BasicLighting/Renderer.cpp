#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float deltaTime = 0.0f;
float lastFrame = 0.0f;


glm::vec3 lightPos = glm::vec3(1, 3, 2);
glm::vec3 lightSize = glm::vec3(1, 1, 1);
std::vector<Cube> cubes;

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
	vertexBuffer.SetCubeWithNormalsAttributes();

	vertexArray2.Bind();
	vertexBuffer2.Bind();

	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


	lightSource.SetProgram(lightShader.shader_program);
	lightSource.Position = glm::vec3(50, 10, 20);
	lightSource.SetName("light");


	//debugging
	Cube cube;
	cube.SetProgram(shader.shader_program);
	cube.Size = glm::vec3(60, 5, 60);
	cube.Position = glm::vec3(50, -10, 20);
	cube.RotateOnY(90);
	cube.Color[0] = 0.8;
	cube.Color[1] = 0.6;
	cube.Color[2] = 0;
	cube.SetName("test" + std::to_string(cubes.size()));
	cubes.push_back(cube);

	shader.UnBind();
	lightShader.UnBind();
	_gui.Init();
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
	view = glm::lookAt(controllers.cameraPos, controllers.cameraFront + controllers.cameraPos, controllers.cameraUp);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1200.f / 800.f, 0.1f, 100.0f);
	//CAMERA STUFF SHOULD BE ADDED SOMEWHERE ELSE OUT OF HERE

	shader.Bind();
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);
	vertexArray.Bind();
	shader.setVec3("lightPos", lightSource.Position);
	shader.setVec3("viewPos", controllers.cameraPos);
	
	shader.setVec3("light.ambiant", glm::vec3(0.3f));
	shader.setVec3("light.diffuse", glm::vec3(0.8f));
	shader.setVec3("light.specular", glm::vec3(0.3f));

	for (Cube cube : cubes)
	{
		cube.Update();
		shader.setVec3("material.Ambiant", cube.material.Ambiant);
		shader.setVec3("material.Diffuse", cube.material.Diffuse);
		shader.setVec3("material.Specular", cube.material.Specular);
		shader.setFloat("material.Shininess", cube.material.shininess);
		shader.SetMat4("model", cube.GetModel());
		cube.SetColor("objectColor");
		cube.Draw();
	}


	lightShader.Bind();
	lightSource.Update();
	lightShader.SetMat4("view", view);
	lightShader.SetMat4("projection", projection);
	lightShader.SetMat4("model", lightSource.GetModel());

	lightSource.SetColor("objectColor");

	
	vertexArray2.Bind();
	lightSource.Draw();

	//glfwSetCursorPosCallback(_window, mouse_callback);
	Debugger();

	controllers.processInput(_window, currentTime);
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

	ImGui::ColorEdit3("Object2 Color", lightSource.Color, 0);

	ImGui::SliderFloat("Move On X", &lightSource.Position.x, -50, 50, "%.3f", 0);
	ImGui::SliderFloat("Move On Y", &lightSource.Position.y, -50, 50, "%.3f", 0);
	ImGui::SliderFloat("Move On Z", &lightSource.Position.z, -50, 50, "%.3f", 0);

	_gui.End();

	_gui.Begin("Light Source");
	ImGui::SliderFloat("2Rsize object", &lightSource.Size.x, 0, 10, "%.3f", 1);
	ImGui::SliderFloat("2Rotate on x Axis", &lightSource.rotateX, 0, 10, "%.3f", 1);
	ImGui::SliderFloat("2Rotate on y Axis", &lightSource.rotateY, 0, 10, "%.3f", 1);
	ImGui::SliderFloat("2Rotate on z Axis", &lightSource.rotateZ, 0, 10, "%.3f", 1);

	_gui.End();

	_gui.Begin("World Settings");

	ImGui::Text(frames.c_str());

	if (ImGui::Button("Create Cube", ImVec2(121, 20)))
	{
		Cube cube;
		cube.SetProgram(shader.shader_program);
		cube.SetName("test" + std::to_string(cubes.size()));
		cubes.push_back(cube);
	}

	ImGui::ColorEdit3("BackgroundColor", bgColor, 0);

	_gui.End();

	_gui.EndFrames();
}
