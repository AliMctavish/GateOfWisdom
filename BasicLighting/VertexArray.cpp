#include "VertexArray.h"

VertexArray::VertexArray()
{
	VertexIndex += 1;
	glGenVertexArrays(VertexIndex, &m_VertexArray);
	Bind();
}

void VertexArray::InIt()
{
}

void VertexArray::Bind()
{
	glBindVertexArray(m_VertexArray);
}

void VertexArray::UnBind()
{
}
