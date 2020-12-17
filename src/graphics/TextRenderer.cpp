#include "TextRenderer.h"
#include <iostream>

std::map<char, Character> TextRenderer::characterCache;

/// <summary>
/// Initializes the TextRenderer
/// </summary>
/// <param name="face">The font face to render with</param>
TextRenderer::TextRenderer(FT_Face* face)
	:fontFace(face)
{
}

/// <summary>
/// Draws the specified text to the screen at the specified position
/// </summary>
/// <param name="xPos">The left most x-coordinate of the text</param>
/// <param name="yPos">The bottom most y-coordinate of the text</param>
/// <param name="text">The text to render</param>
/// <param name="fontSize">The scale to render the font at</param>
/// <param name="color">The color of the text</param>
void TextRenderer::DrawText(int xPos, int yPos, std::string text, float fontSize, glm::vec4 color) {
    //Loops through every letter in the string
    for (int i = 0; i < text.length(); i++)
    {
        Character currCharacter;

        //Gets the atlas index of the character in the font and loads it
        unsigned int index = FT_Get_Char_Index((*fontFace), text[i]);
        FT_Load_Glyph((*fontFace), index, FT_LOAD_DEFAULT);

        //Loads new characters into the cache if the character hasn't already been loaded into memory
        if (characterCache.find(text[i]) == characterCache.end())   
        {
            //Renders the character
            FT_Render_Glyph((*fontFace)->glyph, FT_RENDER_MODE_NORMAL);

            currCharacter = LoadCharacterIntoMemory(text[i]);
        }
        else {
            //If it already exist use it
            currCharacter = characterCache[text[i]];
        }

        //x and pos position of the character adjusted to follow bearingas and a baseline
        float x = xPos + (currCharacter.bearing.x * fontSize);
        float y = yPos - (currCharacter.size.y - currCharacter.bearing.y) * fontSize;

        currCharacter.renderable->model = glm::scale(
            glm::mat4(1.0f),
            glm::vec3(fontSize, fontSize, 0)
        );

        currCharacter.renderable->model = glm::translate(currCharacter.renderable->model, glm::vec3(x, y, 0));
        
        currCharacter.renderable->mvp = currCharacter.renderable->proj * currCharacter.renderable->view * currCharacter.renderable->model;
        currCharacter.renderable->shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
        
        //Binds the texture and draw it to the screen
        currCharacter.texture->Bind();

        Renderer::Draw(currCharacter.renderable);

        xPos += (currCharacter.advance >> 6);
    }
}

/// <summary>
/// Loads new characters into the cache using the FreeType library
/// </summary>
/// <param name="characterToLoad">Character to load</param>
/// <returns>A Character struct containing all of the character data necessary for rendering</returns>
Character TextRenderer::LoadCharacterIntoMemory(char characterToLoad) {
    
    Character characterToReturn = {
        new Texture((*fontFace)->glyph->bitmap.buffer, (*fontFace)->glyph->bitmap.width, (*fontFace)->glyph->bitmap.rows),
        glm::ivec2((*fontFace)->glyph->bitmap.width, (*fontFace)->glyph->bitmap.rows),
        glm::ivec2((*fontFace)->glyph->bitmap_left, (*fontFace)->glyph->bitmap_top),
        (*fontFace)->glyph->advance.x
    };

    float w = characterToReturn.size.x;
    float h = characterToReturn.size.y;

    // update VBO for each character
    float vertices[16] = {
        0, h,   0.0f, 0.0f,
        0, 0,   0.0f, 1.0f,
        w, 0,   1.0f, 1.0f,
        w, h,   1.0f, 0.0f,
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