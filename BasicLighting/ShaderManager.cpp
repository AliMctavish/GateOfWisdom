#include "ShaderManager.h"


void ShaderManager::AddTextures()
{
	texture.SetTexture("Assests/ds.jpg", 1);
	texture2.SetTexture("Assests/face.png", 0);
}

void ShaderManager::Initialize(Shader& shader)
{

	shader.SetShaders("VertexShader.shader", "FragmentShader.shader");


	//anything related to shader inputs
//	shader.setInt("textureFrag", 0);
//	shader.setInt("textureFrag2", 1);
	//

	shader.UnBind();
}

void ShaderManager::Update()
{
	//texture.Bind();
	//texture2.Bind();
}
