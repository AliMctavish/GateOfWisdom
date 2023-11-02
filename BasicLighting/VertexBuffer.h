#pragma once
#include "Shader.h"
#include "RawVertexData.h"


enum VertexType {
	Cube_Type = 0,
	Surface_Type = 1,
	Pyramid_Type = 2
};

class VertexBuffer {
private : 
	uint32_t m_VertexBuffer;
	VertexType m_Type;
public : 
	VertexBuffer(VertexType type);
	~VertexBuffer();

	uint32_t inline GetBuffer() { return m_VertexBuffer; }
	void Bind();
	void SetAttributes();
	void UnBind();
};
