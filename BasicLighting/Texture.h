#pragma once
#include "Shader.h"

static int textureIndex;
class Texture {
private:
	unsigned int m_Texture;
	void Init();
public:
	Texture();
	void SetTexture(const char* textureFile);
	void Bind();
	void UnBind();
};
