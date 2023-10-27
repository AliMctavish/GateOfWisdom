#include "GuiDebugger.h"

GuiDebugger::GuiDebugger()
{
	m_Window = 0;
}

void GuiDebugger::SetWindow(GLFWwindow* window)
{
	m_Window = window;
}

GuiDebugger::~GuiDebugger()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GuiDebugger::StartFrames()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GuiDebugger::EndFrames()
{
	ImGui::Render();
	ImGui::EndFrame();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiDebugger::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void GuiDebugger::Begin(const char* windowTitle)
{
	ImGui::Begin(windowTitle);
}

void GuiDebugger::End()
{
	ImGui::End();
}

void GuiDebugger::Display()
{
	ImGui::Text("this is a text inside opengl");
}
