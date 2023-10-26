#pragma once
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Cube.h"
#include "VertexBuffer.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  1200

class Renderer {
private:
	GLFWwindow* _window;
	Shader shader;
	Cube cube;
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
public:
	Renderer(GLFWwindow* window);
	void Init();
	void Initialize();
	void Update();
};
