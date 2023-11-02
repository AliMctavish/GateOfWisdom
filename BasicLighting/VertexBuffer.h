#pragma once
#include "Shader.h"
#define Cube_Data_Size 180

class VertexBuffer {
private : 
	uint32_t m_VertexBuffer;
public : 
	VertexBuffer();
	~VertexBuffer();
	uint32_t inline GetBuffer() { return m_VertexBuffer; }
	void Bind();
	void SetAttributes();
	float* BufferData();
	void UnBind();
};
