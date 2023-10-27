#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	m_VertexBuffer = 0;
	Bind();
}

VertexBuffer::~VertexBuffer()
{
	UnBind();
}

void VertexBuffer::Bind()
{
	float* vertices = BufferData();
	float vert[Cube_Data_Size];
	for (int i = 0; i < Cube_Data_Size; i++)
		vert[i] = vertices[i];

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), &vert, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	delete[] vertices;
}

float* VertexBuffer::BufferData()
{
	float* vertices = new float[Cube_Data_Size] {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.5f, 0.0f,

		 0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.5f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.5f,

		-0.5f,  0.5f, -0.5f,  0.0f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.5f
	};

	return vertices;
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
