#include "Font.h"


Font::Font()
{
	Init();
	ShaderInit();
	ProcessFontTexture();
	GenerateBuffer();
}

void Font::SetView(glm::mat4 projectionMatrix)
{
	m_Shader.Bind();
	m_Shader.SetMat4("projection", projectionMatrix);
	m_Shader.UnBind();
}


void Font::ShaderInit()
{
	m_Shader.SetShaders("FontVertexShader.shader", "FontFragmentShader.shader");
}


void Font::GenerateBuffer()
{
	m_VAO.Bind();
	m_VBO.Bind();
	m_VBO.UnBind();
	m_VAO.UnBind();
}


void Font::Init()
{
	if (FT_Init_FreeType(&m_FreeType))
	{
		std::cout << "Could not init FreeType Library" << std::endl;
		return;
	}

	if (FT_New_Face(m_FreeType, "Fonts/arialbi.ttf", 0, &m_Face))
	{
		std::cout << "Failed to load font" << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(m_Face, 0, 48);

	if (FT_Load_Char(m_Face, 'X', FT_LOAD_RENDER))
	{
		std::cout << "Failed to load Glyph" << std::endl;
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Font::ProcessFontTexture()
{
	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
		{
			std::cout << "Failed to load Glyph" << std::endl;
			continue;
		}

		unsigned int textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, m_Face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		FontCharacter character = {
			textureId,
			glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
			glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
			m_Face->glyph->advance.x
		};
		Characters.insert(std::pair<char, FontCharacter>(c, character));
	}

	FT_Done_Face(m_Face);
	FT_Done_FreeType(m_FreeType);
}

void Font::Draw(std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state	

	m_Shader.Bind();
	m_Shader.Set3Float("textColor", color.x, color.y, color.z);
	//m_Shader.UnBind();

	glActiveTexture(GL_TEXTURE0);
	m_VAO.Bind();

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		FontCharacter ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO.GetBuffer());
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	m_VAO.UnBind();
	glBindTexture(GL_TEXTURE_2D, 0);
	m_Shader.UnBind();
}
