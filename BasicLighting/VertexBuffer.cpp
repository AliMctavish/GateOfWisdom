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
	InitializeVertexBuffer();
}

void VertexBuffer::InitializeVertexBuffer()
{
	RawVertexData rawData;

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	switch (m_Type)
	{
	case VertexType::Cube_Type:
	{
		std::array<float, Cube_With_Normals_And_Texture_Data_Buffer_Size> arrayData = rawData.CubeWithNormalsData();
		glBufferData(GL_ARRAY_BUFFER, sizeof(arrayData), &arrayData, GL_STATIC_DRAW);
		SetCubeWithNormalsAndTexturesAttributes();
		break;
	}
	case VertexType::Surface_Type:
	{
		std::array<float, Flat_Surface_Data_Buffer_With_Texture> arrayData = rawData.FlatSurface();
		std::array<float, arrayData.size()> vert = arrayData;
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert), &vert, GL_STATIC_DRAW);
		SetCubeWithNormalsAndTexturesAttributes();
		break;
	}
	case VertexType::Pyramid_Type:
	{
		std::array<float, Pyramid_Data_Buffer> arrayData = rawData.PyramidData();
		std::array<float, arrayData.size()> vert = arrayData;
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert), &vert, GL_STATIC_DRAW);
		SetCubeAttributes();
		break;
	}
	}
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
