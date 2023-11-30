#pragma once
#include <vector>
#include "GuiDebugger.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Cube.h"
#include "VertexBuffer.h"
#include "GuiDebugger.h"
#include "Texture.h"
#include "Light.h"
#include "Physics.h"
#include "Player.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  1200

class Renderer {
private:
	bool gameStarted = false;

	GLFWwindow* _window;
	GuiDebugger _gui;
	Physics _physics;
	Player _player;

	Shader shader;
	Shader lightShader;

	std::vector<Light> lights;
	std::vector<Cube> cubes;

	VertexArray vertexArray;
	VertexArray vertexArray2;
	VertexBuffer vertexBuffer = VertexBuffer(VertexType::Cube_Type);
	VertexBuffer vertexBuffer2 = VertexBuffer(VertexType::Cube_Type);

	//Controllers controllers;
public:
	Renderer(GLFWwindow* window);
	void Init();
	void Initialize();
	void Update();
	void Draw();
};
