#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H  
#include <glm/gtc/matrix_transform.hpp>

class Font {
private : 
	struct FontCharacter {
		unsigned int TextureID;
		glm::ivec2   Size;
		glm::ivec2   Bearing;
		unsigned int Advance;
	};
	glm::mat4 m_Projection = glm::perspective(glm::radians(75.0f), 1200.f / 800.f, 0.1f, 10.0f);
	FT_Library m_FreeType;
	FT_Face m_Face;
	Shader m_Shader;
	VertexBuffer m_VBO = VertexBuffer(VertexType::Text_Font_Type);
	VertexArray m_VAO;
	void Init();
	void ProcessFontTexture();
	void ShaderInit();
	void GenerateBuffer();
public: 
	Font();
	void SetView (glm::mat4 playerMat);
	void Draw(std::string text, float x, float y, float scale, glm::vec3 color);
	std::map<char, FontCharacter> Characters;
};
