#pragma once
#include "Shader.h"
#define Cube_Data_Size 180

class VertexBuffer {
private : 
	uint32_t m_VertexBuffer;
public : 
	VertexBuffer();
	~VertexBuffer();
	void Bind();
	float* BufferData();
	void UnBind();
};
