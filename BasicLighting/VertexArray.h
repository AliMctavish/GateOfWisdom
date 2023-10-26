#pragma once
#include "Shader.h"

static int VertexIndex;

class VertexArray {
private : 
	unsigned int m_VertexArray;
public :
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
};
