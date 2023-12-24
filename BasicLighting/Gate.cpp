#include "Gate.h"

Gate::Gate()
{
	Init();
}

void Gate::Init()
{
	objectId = CUBEID;
	Position = glm::vec3(0, 0, 0);
	Size = glm::vec3(7, 7, 7);
	SetObjectColor(1, 1, 1);
	CUBEID++;
}

bool Gate::CheckKeyColor(float r, float g, float b)
{
	for (int i = 0; i < m_Colors.size(); i++)
	{
		if (CheckColorValidity(r, g, b, m_Colors[i][0], m_Colors[i][1], m_Colors[i][2]))
		{
			NumberOfKeysLeft -= 1;
			m_Colors.erase(m_Colors.begin() + i);
			RequiredColors.erase(RequiredColors.begin() + i);
			return true;
		}
	}
	return false;
}

bool Gate::CheckColorValidity(float r, float g, float b, float r1, float g1, float b1)
{
	if (r == r1 && g == g1 && b == b1)
		return true;

	return false;
}


void Gate::ProcessColor(float r, float g, float b)
{
	if (m_IsColorMix)
	{
		std::array<float, 3> lastColor = m_Colors[m_Colors.size() - 1];
		m_Colors.push_back(CalculateColorValues(r, g, b, lastColor[0], lastColor[1], lastColor[2]));
		m_IsColorMix = false;
	}
	else
	{
		m_Colors.push_back({ r,g,b });
		m_IsColorMix = true;
	}
}


std::array<float, 3> Gate::CalculateColorValues(float r, float g, float b, float r1, float g1, float b1)
{
	m_ResultantColor[0] = (r + r1) * 0.5f;
	m_ResultantColor[1] = (g + g1) * 0.5f;
	m_ResultantColor[2] = (b + b1) * 0.5f;
	return m_ResultantColor;
}


void Gate::Update()
{
	BaseObject::Update();
	BaseObject::RotateY();
	BaseObject::Resize();

	for (RequiredColor& req : RequiredColors)
	{
		req.m_Model = glm::mat4(1.0f);
		req.Rotate360OnY();
		req.m_Model = glm::translate(req.m_Model, req.Position);
		req.Resize();
	}
}

void Gate::Draw(ModelLoader& modelLoader)
{
	m_Shader.SetMat4("model", m_Model);
	BaseObject::UseColor("objectColor");
	modelLoader.GetModel(ModelLoader::Type_Gate).Draw(m_Shader);

	for (RequiredColor& req : RequiredColors)
		req.Draw();
}

