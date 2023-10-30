#pragma once
#include "Shader.h"

static int VertexIndex;

class VertexArray {
private : 
	uint32_t m_VertexArray;
public :
	VertexArray();
	~VertexArray();
	void Update();
	void Bind();
	void UnBind();
};
