#include "Texture.h"
#include "TextureLoader.h"


Texture::Texture()
{
	m_TextureIndex = 0;
	glGenTextures(1, &m_Texture);
}

Texture::~Texture()
{
	UnBind();
}

void Texture::Init()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_TextureIndex = textureCounter;
	//m_uniformTexture = "texture" + std::to_string(m_TextureIndex);
	textureCounter++;
}

void Texture::Bind()
{
	//commented the part were you can send two texture uniforms in one shader
	//glUniform1i(glGetUniformLocation(m_Program, m_uniformTexture.c_str()), m_TextureIndex);
	glActiveTexture(GL_TEXTURE0 + m_TextureIndex);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Texture::UnBind()
{
	//it was texture unbinding problem ! 
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTexture(const char* textureFile, int num)
{
	Bind();
	Init();
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	stbi_uc* data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (num == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}


	stbi_image_free(data);
}

void Texture::SetTexutreType(uint16_t textureIndex)
{
	if (textureIndex == 1)
		SetTexture("Assests/wall.jpg", 1);
	else if (textureIndex == 2)
		SetTexture("Assests/grd.jpg", 1);
	else if (textureIndex == 3)
		SetTexture("Assests/box.png", 0);
	else if (textureIndex == 4)
		SetTexture("Assests/artifact.jpg", 1);
	else if (textureIndex == 5)
		SetTexture("Assests/artifact2.jpg", 1);
}
