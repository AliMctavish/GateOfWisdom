#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(VertexType type)
{
	m_Type = type;
	m_VertexBuffer = 0;
}

VertexBuffer::~VertexBuffer()
{
	UnBind();
}

void VertexBuffer::Bind()
{
	float* vertices = nullptr;
	RawVertexData rawData;

	if (m_Type == VertexType::Cube_Type)
		vertices = rawData.CubeData();
	else if (m_Type == VertexType::Pyramid_Type)
		vertices = rawData.PyramidData();


	float vert[Cube_Data_Size];
	for (int i = 0; i < Cube_Data_Size; i++)
		vert[i] = vertices[i];

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), &vert, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	delete[] vertices;
}

void VertexBuffer::SetAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
