#pragma once
#include "Player.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H  

class Font {
private : 
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
	void Draw(Player &player,std::string text, float x, float y, float scale, glm::vec3 color);
	struct FontCharacter {
		unsigned int TextureID;
		glm::ivec2   Size;
		glm::ivec2   Bearing;
		unsigned int Advance;
	};
	std::map<char, FontCharacter> Characters;
};
