#pragma once
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"
#include "FileManager.h"
#include "Light.h"
#include "Cube.h"

#define Button_Size ImVec2(121,20)


class GuiDebugger{
private : 
	GLFWwindow* m_Window;
	FileManager fileManager;
	const char* selectedTexture = "Assests/grd.jpg";
public :
	GuiDebugger();
	~GuiDebugger();
	void StartFrames();
	void EndFrames();
	void SetWindow(GLFWwindow* window);
	void Init();
	void Begin(const char* windowTitle);
	void End();
	void Debugger(std::vector<Light> &lights , std::vector<Cube> &cubes,
		Shader &shader , Shader &lightShader
		,std::string &frames , bool &gameStarted);
	void Display();
};
