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
		vertices = rawData.CubeWithNormalsData();
	else if (m_Type == VertexType::Pyramid_Type)
		vertices = rawData.PyramidData();


	float vert[Cube_With_Normals_And_Texture_Data];
	for (int i = 0; i < Cube_With_Normals_And_Texture_Data; i++)
		vert[i] = vertices[i];

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), &vert, GL_STATIC_DRAW);

	// texture coord attribute
	delete[] vertices;
}

void VertexBuffer::SetCubeAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void VertexBuffer::SetCubeWithNormalsAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}	

void VertexBuffer::SetCubeWithNormalsAndTexturesAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
