#pragma once
#include "Texture.h"


class TextureManager {
private : 
	Texture texture;
	Texture texture2;
public : 
	void Initialize(Shader& shader);
	void Update();
};