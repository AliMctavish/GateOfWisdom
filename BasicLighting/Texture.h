#pragma once
#include "Shader.h"

static int textureIndex;
class Texture {
private:
	unsigned int m_Texture;
	void Init();
	void Bind();
	void UnBind();
public:
	Texture();
	~Texture();
	void SetTexture(const char* textureFile);
};
