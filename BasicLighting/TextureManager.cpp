#include "TextureManager.h"

void TextureManager::Initialize(Shader& shader)
{
	texture.SetTexture("Assests/ds.jpg", 1);
	texture2.SetTexture("Assests/face.png", 0);

	shader.SetShaders("VertexShader.shader", "FragmentShader.shader");

	shader.setInt("textureFrag", 0);
	shader.setInt("textureFrag2", 1);

	shader.UnBind();
}

void TextureManager::Update()
{
	texture.Bind();
	texture2.Bind();
}
