#pragma once
#include "GuiDebugger.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Cube.h"
#include "VertexBuffer.h"
#include "GuiDebugger.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  1200

class Renderer {
private:
	GLFWwindow* _window;
	GuiDebugger _gui;
	Shader shader;
	Texture texture;
	Texture texture2;
	Cube cube;
	Cube cube2;
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
public:
	Renderer(GLFWwindow* window);
	void Init();
	void Initialize();
	void Update();
	void Debugger();
};
