#pragma once
#include "Shader.h"

static int textureIndex;
class Texture {
private:
	void Init();
public:
	unsigned int m_Texture;
	void Bind();
	void UnBind();
	Texture();
	~Texture();
	void SetTexture(const char* textureFile, int num);
};
