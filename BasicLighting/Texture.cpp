#include "Texture.h"
#include "TextureLoader.h"


Texture::Texture()
{
	Bind();
	Init();
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

	textureIndex++;
}

void Texture::Bind()
{
	glGenTextures(1, &m_Texture);
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTexture(const char* textureFile, int num)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	stbi_uc* data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
	if (data)
	{
		if(num == 1)
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
