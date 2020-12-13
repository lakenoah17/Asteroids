#include "TextRenderer.h"
#include <iostream>

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
        Character currCharacter;

        unsigned int index = FT_Get_Char_Index((*fontFace), text[i]);
        FT_Load_Glyph((*fontFace), index, FT_LOAD_DEFAULT);

        //Loads new characters into the cache
        if (characterCache.find(text[i]) == characterCache.end())
        {
            FT_Render_Glyph((*fontFace)->glyph, FT_RENDER_MODE_NORMAL);

            currCharacter = LoadCharacterIntoMemory(text[i], xPos, yPos, fontSize);
        }
        else {
            currCharacter = characterCache[text[i]];
        }

        currCharacter.renderable->model = glm::translate(glm::mat4(1.0f), glm::vec3(xPos, yPos, 0));
        currCharacter.renderable->mvp = currCharacter.renderable->proj * currCharacter.renderable->view * currCharacter.renderable->model;

        currCharacter.texture->Bind();

        Renderer::Draw(currCharacter.renderable);

        currCharacter.texture->UnBind();

        /* increment pen position */
        xPos += ((*fontFace)->glyph->advance.x >> 6)*fontSize;
        yPos += ((*fontFace)->glyph->advance.y >> 6)*fontSize;

        // load character glyph 
        std::cout << i << std::endl;
    }
}

Character TextRenderer::LoadCharacterIntoMemory(char characterToLoad, float xPos, float yPos, float scale) {
    //xPos += (currCharacter.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)

    // now store character for later use
    Character characterToReturn = {
        new Texture((*fontFace)->glyph->bitmap.buffer, (*fontFace)->glyph->bitmap.width, (*fontFace)->glyph->bitmap.rows),
        glm::ivec2((*fontFace)->glyph->bitmap.width, (*fontFace)->glyph->bitmap.rows),
        glm::ivec2((*fontFace)->glyph->bitmap_left, (*fontFace)->glyph->bitmap_top),
        (*fontFace)->glyph->advance.x
    };

    float w = characterToReturn.size.x * scale;
    float h = characterToReturn.size.y * scale;
    // update VBO for each character
    float vertices[16] = {
        xPos,     yPos + h,   0.0f, 0.0f,
        xPos,     yPos,       0.0f, 1.0f,
        xPos + w, yPos,       1.0f, 1.0f,
        xPos + w, yPos + h,   1.0f, 0.0f,
    };

    unsigned int* indicies = new unsigned int[6]{
        0, 1, 2,
        2, 3, 0
    };

    characterToReturn.renderable = Renderer::CreateRenderable("res/shaders/Text.shader", vertices, 16, 4, indicies, 6);
    characterToReturn.renderable->model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    characterToReturn.renderable->mvp = characterToReturn.renderable->proj * characterToReturn.renderable->view * characterToReturn.renderable->model;

    characterCache.insert(std::pair<char, Character>(characterToLoad, characterToReturn));

    return characterToReturn;
}