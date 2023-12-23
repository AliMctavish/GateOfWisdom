#pragma once
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"
#include "FileManager.h"
#include "Light.h"
#include "Cube.h"
#include "Enemy.h"
#include "Key.h"
#include "Machine.h"



#define Button_Size ImVec2(121,20)
#define Selector_Size ImVec2(130,10)


class GuiDebugger{
private : 
	GLFWwindow* m_Window;

	FileManager fileManager;
	uint16_t selectedTexture = 0;
	std::string selectedMap = " ";
	bool m_MapSelector = false;
public :
	GuiDebugger();
	~GuiDebugger();
	void StartFrames();
	void EndFrames();
	void SetupImGuiStyle(bool bStyleDark_, float alpha_);
	void SetWindow(GLFWwindow* window);
	void Init();
	void Begin(const char* windowTitle);
	void End();
	void Debugger(std::vector<Light> &lights , std::vector<Cube> &cubes,std::vector<Enemy> &enemies,std::vector<Key> &keys,
		Shader &shader , Shader &lightShader , Shader& modelShader
		, ModelLoader& modelLoader,Machine &_machine,bool &gameStarted);
	void Display();
};
