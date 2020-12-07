#include "TextRenderer.h"

TextRenderer::TextRenderer(FT_Face* face)
	:fontFace(face)
{
}

unsigned int TextRenderer::GetCharIndex(char charToFind) {
	return FT_Get_Char_Index(*fontFace, charToFind);
}

void TextRenderer::DrawText(int xPos, int yPos, std::string text, int fontSize) {
    for (int i = 0; i < text.length(); i++)
    {
        // load character glyph 
        if (FT_Load_Char((*fontFace), text[i], FT_LOAD_RENDER))
        {
            continue;
        }

        //Loads new characters into the cache
        if (characterCache.find(text[i]) == characterCache.end())
        {
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                (*fontFace)->glyph->bitmap.width,
                (*fontFace)->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                (*fontFace)->glyph->bitmap.buffer
            );

            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2((*fontFace)->glyph->bitmap.width, (*fontFace)->glyph->bitmap.rows),
                glm::ivec2((*fontFace)->glyph->bitmap_left, (*fontFace)->glyph->bitmap_top),
                (*fontFace)->glyph->advance.x
            };

            characterCache.insert(std::pair<char, Character>(text[i], character));
        }
        
        
    }
}