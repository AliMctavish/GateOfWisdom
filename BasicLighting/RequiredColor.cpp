#include "RequiredColor.h"

RequiredColor::RequiredColor()
{
	Init();
}

void RequiredColor::Init()
{
	objectId = CUBEID;
	Position = glm::vec3(0, 0, 0);
	Size = glm::vec3(5,5,5);
	SetObjectColor(0, 1, 1);
	CUBEID++;

	vertexArray.Bind();
	vertexBuffer.Bind();
	vertexArray.UnBind();
}

void RequiredColor::Update()
{
	BaseObject::Update();
	//BaseObject::Resize();
}

void RequiredColor::Draw()
{
	vertexArray.Bind();
	m_Shader.SetMat4("model", m_Model);
	BaseObject::UseColor("objectColor");
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vertexArray.UnBind();
}
	