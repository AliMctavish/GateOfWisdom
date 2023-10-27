#pragma once
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"

class GuiDebugger{
private : 
	GLFWwindow* m_Window;
public :
	GuiDebugger();
	~GuiDebugger();
	void StartFrames();
	void EndFrames();
	void SetWindow(GLFWwindow* window);
	void Init();
	void Begin(const char* windowTitle);
	void End();
	void Display();


};
