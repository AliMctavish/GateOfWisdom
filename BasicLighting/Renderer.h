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

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  1200

class Renderer {
private:
	bool gameStarted = false;
	GLFWwindow* _window;
	GuiDebugger _gui;
	Shader shader;
	Shader lightShader;
	//TODO make texture part of cube object 
	//TODO make list of textures
	std::vector<Light> lights;
	std::vector<Cube> cubes;
	//std::vector<BaseObject> objects;
	
	//TODO make vectors in unique pointers to make project faster!
	//nope its not faster its actually slower and you dont need it sincce the object is the same
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
	void Debugger();
};
