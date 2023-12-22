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
#include "Model.h"
#include "ModelLoader.h"
#include "EntityManager.h"
#include "ObjectGenerator.h"
#include "Sprite.h"
#include "Font.h"
#include "Key.h"
#include "Machine.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  1200

class Renderer {
private:
	bool gameStarted = false;

	GLFWwindow* _window;
	GuiDebugger _gui;
	Physics _physics;
	Player _player;
	Machine _machine;

	Shader shader;
	Shader lightShader;
	Shader modelShader;


	ModelLoader modelLoader;
	
	

	std::vector<Light> lights;
	std::vector<Cube> cubes;
	std::vector<Enemy> enemies;
	std::vector<Key> keys;
	EntityManager entityManager;

	ObjectGenerator objectGenerator;

	VertexArray vertexArray;
	VertexBuffer vertexBuffer = VertexBuffer(VertexType::Cube_Type);

	Sprite testSprite;
	Font font;

	//VertexBuffer vertexBuffer2 = VertexBuffer(VertexType::Surface_Type);

	//Controllers controllers;
public:
	Renderer(GLFWwindow* window);
	void Init();
	void Initialize();
	void Update(std::string &deltaTime);
	void Draw();
};
