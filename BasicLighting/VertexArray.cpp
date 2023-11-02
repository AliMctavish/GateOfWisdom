#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArray);
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
