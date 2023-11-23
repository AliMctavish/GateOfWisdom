#pragma once
#include "Shader.h"

static int textureCounter;
class Texture {
private:
	void Init();
	uint32_t m_Texture;
public:
	uint32_t m_TextureIndex;
	void Bind();
	void UnBind();
	Texture();
	~Texture();
	void SetTexture(const char* textureFile, int num);
};
