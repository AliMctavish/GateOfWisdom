#include "VertexArray.h"

VertexArray::VertexArray()
{
	VertexIndex += 1;
	glGenVertexArrays(VertexIndex, &m_VertexArray);
	Bind();
}

VertexArray::~VertexArray()
{
	UnBind();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_VertexArray);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}
