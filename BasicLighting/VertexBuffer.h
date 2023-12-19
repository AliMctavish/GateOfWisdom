#pragma once
#include "Shader.h"
#include "RawVertexData.h"

enum VertexType {
	Cube_Type = 0,
	Surface_Type = 1,
	Pyramid_Type = 2,
	Text_Font_Type = 3
};

class VertexBuffer {
private : 
	VertexType m_Type;
public : 
	uint32_t m_VertexBuffer;
	VertexBuffer(VertexType type);
	~VertexBuffer();

	uint32_t inline GetBuffer() { return m_VertexBuffer; }
	void Bind();
	void InitializeVertexBuffer();
	void SetFontAtteributes();
	void SetCubeAttributes();
	void SetCubeWithNormalsAttributes();
	void SetCubeWithNormalsAndTexturesAttributes();
	void UnBind();
};
