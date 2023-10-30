#pragma once
#include "Texture.h"


class ShaderManager {
private : 
	Texture texture;
	Texture texture2;
public : 
	void AddTextures();
	void Initialize(Shader& shader);
	void Update();
};