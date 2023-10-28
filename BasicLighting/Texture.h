#pragma once
#include "Shader.h"

static int textureIndex;
class Texture {
private:
	void Init();
	unsigned int m_Texture;
public:
	void Bind();
	void UnBind();
	Texture();
	~Texture();
	void SetTexture(const char* textureFile, int num);
};
