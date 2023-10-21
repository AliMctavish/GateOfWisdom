#pragma once
#include "Shader.h"

static int VertexIndex;

class VertexArray {
private : 
	unsigned int m_VertexArray;
public :
	VertexArray();
	void InIt();
	void Bind();
	void UnBind();
};
