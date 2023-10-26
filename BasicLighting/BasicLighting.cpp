#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"
#include <iostream>
#include "Texture.h"
#include <vector>
#include "Controllers.h"
#include "VertexArray.h"
#include "Cube.h"
#include "VertexBuffer.h"
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  1200

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	//CONFIGURE IMGUI....
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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "something went wrong with glad !" << std::endl;
		return -1;
	}

	Texture texture;
	texture.SetTexture("Assests/ds.jpg");

	glEnable(GL_DEPTH_TEST);

	VertexArray vertexArray;
	VertexBuffer vertexBuffer;

	Shader shader("VertexShader.shader", "FragmentShader.shader");
	shader.UnBind();

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Make the window's context current */

	/* Loop until the user closes the window */

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init("#version 330");


	Cube cube(shader.shader_program);
	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 5);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glfwSetCursorPosCallback(window, mouse_callback);

		shader.Bind();
		vertexArray.Bind();

		cube.SetLocation(glm::vec3(2, 2, 2));
		cube.Draw();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("hello world from imgui :D");
		ImGui::Text("this is a text inside opengl");

		ImGui::End();

		ImGui::Render();
		ImGui::EndFrame();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



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

		processInput(window);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}