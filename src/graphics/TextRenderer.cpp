#include "TextRenderer.h"

std::map<char, Character> TextRenderer::characterCache;

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

        Character currCharacter;

        //Loads new characters into the cache
        if (characterCache.find(text[i]) == characterCache.end())
        {
            currCharacter = LoadCharacterIntoMemory(text[i], xPos, yPos, fontSize);
        }
        else {
            currCharacter = characterCache[text[i]];
        }

        xPos += currCharacter.bearing.x * fontSize;
        yPos -= (currCharacter.size.y - currCharacter.bearing.y) * fontSize;

        //Currently breaks code. Need to look more into texture rendering
        /*glBindTexture(GL_TEXTURE_2D, currCharacter.textureID);

        currCharacter.renderable->vao->Bind();
        currCharacter.renderable->ib->Bind();
        currCharacter.renderable->vb->Bind();*/

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

Character TextRenderer::LoadCharacterIntoMemory(char characterToLoad, float xPos, float yPos, float scale) {
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
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    //xPos += (currCharacter.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)

    // now store character for later use
    Character characterToReturn = {
        texture,
        glm::ivec2((*fontFace)->glyph->bitmap.width, (*fontFace)->glyph->bitmap.rows),
        glm::ivec2((*fontFace)->glyph->bitmap_left, (*fontFace)->glyph->bitmap_top),
        (*fontFace)->glyph->advance.x
    };

    float w = characterToReturn.size.x * scale;
    float h = characterToReturn.size.y * scale;
    // update VBO for each character
    float vertices[24] = {
        xPos,     yPos + h,   0.0f, 0.0f,
        xPos,     yPos,       0.0f, 1.0f,
        xPos + w, yPos,       1.0f, 1.0f,
        xPos,     yPos + h,   0.0f, 0.0f,
        xPos + w, yPos,       1.0f, 1.0f,
        xPos + w, yPos + h,   1.0f, 0.0f,
    };

    unsigned int* indicies = new unsigned int[6]{
        2, 1, 0,
        0, 3, 2
    };

    characterToReturn.renderable = Renderer::CreateRenderable("res/shaders/Text.shader", vertices, 24, 4, indicies, 6);

    characterCache.insert(std::pair<char, Character>(characterToLoad, characterToReturn));

    return characterToReturn;
}