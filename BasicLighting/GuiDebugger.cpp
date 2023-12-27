#include "GuiDebugger.h"


GuiDebugger::GuiDebugger()
{
	m_Window = 0;
}

void GuiDebugger::SetWindow(GLFWwindow* window)
{
	m_Window = window;
}

float bgColor[] = { 0.0,0.0,0.0 };

void GuiDebugger::SetupImGuiStyle(bool bStyleDark_, float alpha_)
{
	ImGuiStyle& style = ImGui::GetStyle();

	// light style from Pacôme Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
	style.Alpha = 1.0f;
	style.FrameRounding = 3.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

	if (bStyleDark_)
	{
		for (int i = 0; i <= ImGuiCol_COUNT; i++)
		{
			ImVec4& col = style.Colors[i];
			float H, S, V;
			ImGui::ColorConvertRGBtoHSV(col.x, col.y, col.z, H, S, V);

			if (S < 0.1f)
			{
				V = 1.0f - V;
			}
			ImGui::ColorConvertHSVtoRGB(H, S, V, col.x, col.y, col.z);
			if (col.w < 1.00f)
			{
				col.w *= alpha_;
			}
		}
	}
	else
	{
		for (int i = 0; i <= ImGuiCol_COUNT; i++)
		{
			ImVec4& col = style.Colors[i];
			if (col.w < 1.00f)
			{
				col.x *= alpha_;
				col.y *= alpha_;
				col.z *= alpha_;
				col.w *= alpha_;
			}
		}
	}
}

void GuiDebugger::Debugger(std::vector<Light>& lights, std::vector<Cube>& cubes,
	std::vector<Enemy>& enemies, std::vector<Key>& keys, Shader& shader,
	Shader& lightShader, Shader& modelShader, ModelLoader& modelLoader, Machine& machine, Gate& gate, GameState& gameState)
{
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 5);


	StartFrames();

	Begin("Enemies Coordinates");

	for (int i = 0; i < enemies.size(); i++)
	{
		ImGui::Text(enemies[i].GetName().c_str());
		ImGui::PushID(enemies[i].objectId);
		ImGui::SliderFloat("Move3 On X", &enemies[i].Position.x, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Move3 On Y", &enemies[i].Position.y, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Move3 On Z", &enemies[i].Position.z, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Rsizex3 object", &enemies[i].Size.x, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizey3 object", &enemies[i].Size.y, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizez3 object", &enemies[i].Size.z, 0, 100, "%.3f", 0);
		if (ImGui::Button("Delete", Button_Size)) { enemies.erase(enemies.begin() + i); }
		ImGui::PopID();
	}

	End();


	Begin("State Coordinates");
	ImGui::Text(machine.GetName().c_str());
	ImGui::PushID(machine.objectId);
	ImGui::ColorEdit3("Object Color", machine.Color, 0);
	ImGui::SliderFloat("Move On X", &machine.Position.x, -250, 250, "%.3f", 0);
	ImGui::SliderFloat("Move On Y", &machine.Position.y, -250, 250, "%.3f", 0);
	ImGui::SliderFloat("Move On Z", &machine.Position.z, -250, 250, "%.3f", 0);
	ImGui::SliderFloat("Rotate On Y", &machine.rotateY, -10, 10, "%.3f", 0);
	ImGui::PopID();
	ImGui::Text(gate.GetName().c_str());
	ImGui::PushID(gate.objectId);
	ImGui::ColorEdit3("Object2 Color", gate.Color, 0);
	ImGui::SliderFloat("Move2 On X", &gate.Position.x, -250, 250, "%.3f", 0);
	ImGui::SliderFloat("Move2 On Y", &gate.Position.y, -250, 250, "%.3f", 0);
	ImGui::SliderFloat("Move2 On Z", &gate.Position.z, -250, 250, "%.3f", 0);
	ImGui::SliderFloat("Rotate2 On Y", &gate.rotateY, -150, 150, "%.3f", 0);
	ImGui::PopID();
	End();


	Begin("Keys Coordinates");


	for (int i = 0; i < keys.size(); i++)
	{
		ImGui::Text(keys[i].GetName().c_str());
		ImGui::PushID(keys[i].objectId);
		ImGui::ColorEdit3("Object2 Color", keys[i].Color, 0);
		ImGui::SliderFloat("Move3 On X", &keys[i].Position.x, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Move3 On Y", &keys[i].Position.y, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Move3 On Z", &keys[i].Position.z, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Rsizex3 object", &keys[i].Size.x, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizey3 object", &keys[i].Size.y, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizez3 object", &keys[i].Size.z, 0, 100, "%.3f", 0);
		if (ImGui::Button("Delete", Button_Size)) { keys.erase(keys.begin() + i); }
		ImGui::PopID();
	}

	End();

	Begin("Objects Coordinates");

	for (int i = 0; i < cubes.size(); i++)
	{
		ImGui::Text(cubes[i].GetName().c_str());
		ImGui::PushID(cubes[i].cubeId);
		ImGui::SliderFloat("Move2 On X", &cubes[i].Position.x, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Move2 On Y", &cubes[i].Position.y, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Move2 On Z", &cubes[i].Position.z, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Rsizex object", &cubes[i].Size.x, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizey object", &cubes[i].Size.y, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rsizez object", &cubes[i].Size.z, 0, 100, "%.3f", 0);
		ImGui::SliderFloat("Rotate on x Axis", &cubes[i].rotateX, 0, 10, "%.3f", 0);
		ImGui::SliderFloat("Rotate on z Axis", &cubes[i].rotateY, 0, 10, "%.3f", 0);
		ImGui::Text("Object Material");
		ImGui::ColorEdit3(cubes[i].GetName().c_str(), cubes[i].Color, 0);
		ImGui::SliderFloat2("Ambiant", &cubes[i].material.Ambiant[0], 0, 10, "%.3f", 0);
		ImGui::SliderFloat2("Diffuse", &cubes[i].material.Diffuse[0], 0, 10, "%.3f", 0);
		ImGui::SliderFloat2("Specular", &cubes[i].material.Specular[0], 0, 10, "%.3f", 0);
		ImGui::SliderFloat("Shininess", &cubes[i].material.shininess, 0, 100, "%.3f", 0);
		if (ImGui::Button("Delete", Button_Size)) { cubes.erase(cubes.begin() + i); }
		ImGui::PopID();
	}
	End();

	Begin("Lights Coordinates2");

	for (int i = 0; i < lights.size(); i++)
	{
		ImGui::Text(lights[i].GetName().c_str());
		ImGui::PushID(lights[i].objectId);
		ImGui::ColorEdit3("Object2 Color", lights[i].Color, 0);

		ImGui::SliderFloat("Move On X", &lights[i].Position.x, -250, 250, "%.3f", 0);
		ImGui::SliderFloat("Move On Y", &lights[i].Position.y, -100, 100, "%.3f", 0);
		ImGui::SliderFloat("Move On Z", &lights[i].Position.z, -250, 250, "%.3f", 0);

		ImGui::SliderFloat("2Rsize object", &lights[i].Size.x, 0, 10, "%.3f", 1);
		if (ImGui::Button("Delete", Button_Size)) { lights.erase(lights.begin() + i); }
		ImGui::PopID();

	}
	End();
	Begin("Scene Settings");
	if (ImGui::Button("Show WireFrame"))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (ImGui::Button("Hide WireFrame"))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	End();

	Begin("World Settings");


	if (m_TextureSelector)
	{
		Begin("Select Texture");
		ImGui::Text("Select your texture file name");
		ImGui::Text("Texture should be saved in 'Assests' folder");
		ImGui::Text("so you can just type the name of the file you saved");
		ImGui::Text("Note : only JPG files");
		ImGui::InputText(" FileName ", selectedTexture, IM_ARRAYSIZE(selectedTexture));
		if (ImGui::Button("Create", Button_Size))
		{
			Cube cube;
			cube.SetShader(shader);
			cube.SetName("object" + std::to_string(cubes.size()));
			std::string str = selectedTexture;
			cube.SetTextureData("Assests/" + str);
			cubes.push_back(cube);
			m_TextureSelector = false;
			gameState.TextMode = false;
		}
		End();
	}

	if (ImGui::Button("Create Cube", Button_Size))
	{
		m_TextureSelector = true;
		gameState.TextMode = true;
	}

	if (ImGui::Button("Create Light", Button_Size))
	{
		Light light;
		light.SetShader(lightShader);
		//light.SetModel(modelLoader);
		light.SetName("object" + std::to_string(cubes.size()));
		lights.push_back(light);
	}

	if (ImGui::Button("Create Enemy", Button_Size))
	{
		Enemy enemy;
		enemy.SetShader(modelShader);
		//enemy.SetModel(modelLoader);
		enemy.SetName("enemy" + std::to_string(enemies.size()));
		enemies.push_back(enemy);
	}
	if (ImGui::Button("Create Key", Button_Size))
	{
		Key key;
		key.SetShader(lightShader);
		//key.SetModel(modelLoader);
		key.SetName("key" + std::to_string(keys.size()));
		keys.push_back(key);
	}

	if (ImGui::Button("Start Game", Button_Size))
	{
		gate.m_Colors.clear();

		for (Light& light : lights)
			gate.ProcessColor(light.Color[0], light.Color[1], light.Color[2]);

		float offset = 0;
		for (int i = 0; i < gate.m_Colors.size(); i++) {
			RequiredColor requiredColor;
			requiredColor.SetShader(lightShader);
			if (i < gate.m_Colors.size())
				requiredColor.SetObjectColor(gate.m_Colors[i][0], gate.m_Colors[i][1], gate.m_Colors[i][2]);
			requiredColor.SetPosition(gate.Position + 10.f + offset + glm::vec3(0, 30, 0));
			gate.RequiredColors.push_back(requiredColor);
			offset += 10;
		}
		gameState.Started = true;
	}

	if (ImGui::Button("Select Map", Button_Size))
	{
		m_MapSelector = true;
	}
	if (m_MapSelector)
	{
		Begin("Select Map");
		if (ImGui::Selectable("Level0", false, 0, Selector_Size))
			selectedMap = "Level0";
		if (ImGui::Selectable("Level1", false, 0, Selector_Size))
			selectedMap = "Level1";
		else if (ImGui::Selectable("Level2", false, 0, Selector_Size))
			selectedMap = "Level2";
		else if (ImGui::Selectable("Level3", false, 0, Selector_Size))
			selectedMap = "Level3";
		else if (ImGui::Selectable("Level4", false, 0, Selector_Size))
			selectedMap = "Level4";
		else if (ImGui::Selectable("Level5", false, 0, Selector_Size))
			selectedMap = "Level5";
		else if (ImGui::Selectable("Level6", false, 0, Selector_Size))
			selectedMap = "Level6";
		else if (ImGui::Selectable("Level7", false, 0, Selector_Size))
			selectedMap = "Level7";
		else if (ImGui::Selectable("Level8", false, 0, Selector_Size))
			selectedMap = "Level8";
		else if (ImGui::Selectable("Level9", false, 0, Selector_Size))
			selectedMap = "Level9";

		if (ImGui::Button("Select", Button_Size))
		{
			lights.clear();
			cubes.clear();
			keys.clear();
			enemies.clear();
			FileManager::LoadFile(lights, cubes, keys, enemies, machine, gate, lightShader, shader, modelShader, modelLoader, selectedMap);
			m_MapSelector = false;
		}
		if (ImGui::Button("Save Map", Button_Size))
		{
			FileManager::SaveFile(lights, cubes, keys, enemies, machine, gate, selectedMap);
			m_MapSelector = false;
		}
		End();
	}

	if (ImGui::Button("Exit", Button_Size))
	{
		gate.m_Colors.clear();

		for (Light& light : lights)
			gate.ProcessColor(light.Color[0], light.Color[1], light.Color[2]);

		float offset = 0;
		for (int i = 0; i < gate.m_Colors.size(); i++) {
			RequiredColor requiredColor;
			requiredColor.SetShader(lightShader);
			if (i < gate.m_Colors.size())
				requiredColor.SetObjectColor(gate.m_Colors[i][0], gate.m_Colors[i][1], gate.m_Colors[i][2]);
			requiredColor.SetPosition(gate.Position + 10.f + offset + glm::vec3(0, 30, 0));
			gate.RequiredColors.push_back(requiredColor);
			offset += 10;
		}
		gameState.EditMode = false;
		gameState.Started = false;
	}



	ImGui::ColorEdit3("BackgroundColor", bgColor, 0);
	End();
	EndFrames();
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

}

