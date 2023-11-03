#include "Renderer.h"
#include "Controllers.h"

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
	lightSource.SetName("light");



	shader.UnBind();
	lightShader.UnBind();
	_gui.Init();
}

float bgColor[] = { 0,0,0 };
void Renderer::Update()
{
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;


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
	shader.setVec3("lightPos", lightSource.Position);
	shader.setVec3("viewPos", cameraPos);

	for (Cube cube : cubes)
	{
		cube.Update();
		shader.SetMat4("model", cube.GetModel());
		cube.SetColor("objectColor");
		cube.Draw();
	}



	lightShader.Bind();
	lightSource.Update();
	lightSource.SinMove();
	lightShader.SetMat4("view", view);
	lightShader.SetMat4("projection", projection);
	lightShader.SetMat4("model", lightSource.GetModel());
	lightSource.SetColor("objectColor");
	vertexArray2.Bind();
	lightSource.Draw();


	//glfwSetCursorPosCallback(_window, mouse_callback);
	Debugger();

	processInput(_window);
	/* Swap front and back buffers */
	glfwSwapBuffers(_window);
	/* Poll for and process events */
	glfwPollEvents();
}

void Renderer::Debugger()
{
	_gui.StartFrames();


	_gui.Begin("Objects Coordinates");
	for (Cube cube : cubes)
	{
		ImGui::Text("ocube.GetName()")
		if (ImGui::Button("xCoord right" + cube.GetName(), ImVec2(150, 20)))
			cube.Position.x++;
		if (ImGui::Button("xCoord left" + cube.GetName(), ImVec2(150, 20)))
			cube.Position.x--;
		if (ImGui::Button("zCoord forward" + cube.GetName(), ImVec2(150, 20)))
			cube.Position.y++;
		if (ImGui::Button("zCoord backward" + cube.GetName(), ImVec2(150, 20)))
			cube.Position.y--;
		if (ImGui::Button("yCoord up" + cube.GetName(), ImVec2(150, 20)))
			cube.Position.z++;
		if (ImGui::Button("yCoord down" + cube.GetName(), ImVec2(150, 20)))
			cube.Position.z--;
		ImGui::ColorEdit3("Object1 Color" + cube.GetName(), cube.Color, 0);
		ImGui::SliderFloat("Move2 On X" + cube.GetName(), &cube.Position.x, -50, 50, "%.3f", 0);
		ImGui::SliderFloat("Move2 On Y" + cube.GetName(), &cube.Position.y, -50, 50, "%.3f", 0);
		ImGui::SliderFloat("Move2 On Z" + cube.GetName(), &cube.Position.z, -50, 50, "%.3f", 0);
		ImGui::SliderFloat("Rsizex object" + cube.GetName(), &cube.Size.x, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizey object" + cube.GetName(), &cube.Size.y, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizez object" + cube.GetName(), &cube.Size.z, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rotate on x Axis" + cube.GetName(), &cube.rotateX, 0, 10, "%.3f", 0);
		ImGui::SliderFloat("Rotate on y Axis" + cube.GetName(), &cube.rotateY, 0, 10, "%.3f", 0);
		ImGui::SliderFloat("Rotate on z Axis", &lightSource.Position.x, 0, 10, "%.3f", 0);
	}
	_gui.End();





	_gui.Begin("Object Coordinates2");

	ImGui::Text("lightSource");
	if (ImGui::Button("2xCoord right", ImVec2(150, 20)))
		lightSource.Position.x++;
	if (ImGui::Button("2xCoord left", ImVec2(150, 20)))
		lightSource.Position.x--;
	if (ImGui::Button("2zCoord forward", ImVec2(150, 20)))
		lightSource.Position.y++;
	if (ImGui::Button("2zCoord backward", ImVec2(150, 20)))
		lightSource.Position.y--;
	if (ImGui::Button("2yCoord up", ImVec2(150, 20)))
		lightSource.Position.z++;
	if (ImGui::Button("2yCoord down", ImVec2(150, 20)))
		lightSource.Position.x--;

	ImGui::ColorEdit3("Object2 Color", lightSource.Color, 0);

	ImGui::SliderFloat("Move On X", &lightSource.Position.x, -50, 50, "%.3f", 0);
	ImGui::SliderFloat("Move On Y", &lightSource.Position.y, -50, 50, "%.3f", 0);
	ImGui::SliderFloat("Move On Z", &lightSource.Position.z, -50, 50, "%.3f", 0);

	_gui.End();

	_gui.Begin("Object Orientation2");
	ImGui::SliderFloat("2Rsize object", &lightSource.Size.x, 0, 10, "%.3f", 1);
	ImGui::SliderFloat("2Rotate on x Axis", &lightSource.rotateX, 0, 10, "%.3f", 1);
	ImGui::SliderFloat("2Rotate on y Axis", &lightSource.rotateY, 0, 10, "%.3f", 1);
	ImGui::SliderFloat("2Rotate on z Axis", &lightSource.rotateZ, 0, 10, "%.3f", 1);

	_gui.End();

	_gui.Begin("World Settings");
	if (ImGui::Button("Create Cube", ImVec2(121, 20)))
	{
		Cube cube;
		cube.SetProgram(shader.shader_program);
		cube.SetName("test");
		cubes.push_back(cube);
	}

	ImGui::ColorEdit3("BackgroundColor", bgColor, 0);

	_gui.End();

	_gui.EndFrames();
}
