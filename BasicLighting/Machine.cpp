#include "Machine.h"

Machine::Machine()
{
	Init();
}

void Machine::ResetLights()
{
	m_Lights.clear();
	m_ResultantColor[0] = 0;
	m_ResultantColor[1] = 0;
	m_ResultantColor[2] = 0;
}

void Machine::AddLight(Light& light)
{
	if (m_Lights.size() <= 2)
		m_Lights.push_back(light);
	else
		MachineIsFull = true;
}

void Machine::UpdateLightsPosition()
{
	if (m_Lights.size() == 1)
	{
		m_Lights[0].Center = Position;
		m_Lights[0].Position = Center + glm::vec3(3, -1, -3.3);
		m_Lights[0].isPickedUp = false;
		m_Lights[0].m_Model = glm::mat4(1.0f);
		m_Lights[0].m_Model = glm::translate(m_Lights[0].m_Model, m_Lights[0].Center);
		m_Lights[0].m_Model = glm::rotate(m_Lights[0].m_Model, rotateY, glm::vec3(0, 1, 0));
		m_Lights[0].m_Model = glm::translate(m_Lights[0].m_Model, m_Lights[0].Position);
		m_Lights[0].Rotate();
		CalculateColorValue(m_Lights[0].Color[0], m_Lights[0].Color[1], m_Lights[0].Color[2], 0, 0, 0);
	}
	if (m_Lights.size() == 2)
	{
		m_Lights[0].Center = Position;
		m_Lights[0].Position = Center + glm::vec3(3, -1, -3.3);
		m_Lights[0].isPickedUp = false;
		m_Lights[0].m_Model = glm::mat4(1.0f);
		m_Lights[0].m_Model = glm::translate(m_Lights[0].m_Model, m_Lights[0].Center);
		m_Lights[0].m_Model = glm::rotate(m_Lights[0].m_Model, rotateY, glm::vec3(0, 1, 0));
		m_Lights[0].m_Model = glm::translate(m_Lights[0].m_Model, m_Lights[0].Position);
		m_Lights[0].Rotate();
		m_Lights[1].Center = Position;
		m_Lights[1].Position = Center + glm::vec3(3, 2.5, -3.3);
		m_Lights[1].isPickedUp = false;
		m_Lights[1].m_Model = glm::mat4(1.0f);
		m_Lights[1].m_Model = glm::translate(m_Lights[1].m_Model, m_Lights[1].Center);
		m_Lights[1].m_Model = glm::rotate(m_Lights[1].m_Model, rotateY, glm::vec3(0, 1, 0));
		m_Lights[1].m_Model = glm::translate(m_Lights[1].m_Model, m_Lights[1].Position);

		CalculateColorValue(m_Lights[0].Color[0],
			m_Lights[0].Color[1],
			m_Lights[0].Color[2],
			m_Lights[1].Color[0],
			m_Lights[1].Color[1],
			m_Lights[1].Color[2]);
		m_Lights[1].Rotate();
	}
}

void Machine::Init()
{
	objectId = CUBEID;
	Position = glm::vec3(0, 0, 0);
	Size = glm::vec3(1.5, 1.5, 1.5);
	CUBEID++;
}

void Machine::AssignToKey(Key& key)
{
	key.SetObjectColor(m_ResultantColor[0], m_ResultantColor[1], m_ResultantColor[2]);
}


void Machine::CalculateColorValue(float x, float y, float z, float x1, float y1, float z1)
{
	if (x1 == 0 && y1 == 0 && z1 == 0) {
		m_ResultantColor[0] = x;
		m_ResultantColor[1] = y;
		m_ResultantColor[2] = z;
	}
	else {
	m_ResultantColor[0] = (x + x1) * 0.5f;
	m_ResultantColor[1] = (y + y1) * 0.5f;
	m_ResultantColor[2] = (z + z1) * 0.5f;
	}
}

void Machine::Update()
{
	//its time to make this work :"|
	m_Direction = glm::normalize(Position);

	//BaseObject::Update();
	m_Model = glm::mat4(1.0f);
	//RotateOnY(m_Angle);
	m_Model = glm::translate(m_Model, Position);
	m_Model = glm::rotate(m_Model, rotateY, glm::vec3(0, 1, 0));
	BaseObject::Resize();

	if (m_Lights.size() > 0)
		UpdateLightsPosition();
}

void Machine::RotateOnY(float angle)
{
	m_Model = glm::rotate(m_Model, rotateY, glm::vec3(0, 1, 0));
}

void Machine::Draw()
{
	m_Shader.SetMat4("model", m_Model);
	BaseObject::UseColor("objectColor");
	m_ModelLoader.GetModel(ModelLoader::Type_Machine).Draw(m_Shader);

	for (Light& light : m_Lights)
		light.Draw();
}
