#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include <string>
#include <map>

#include "VertexBufferLayout.h"
#include "Texture.h"

/// <summary>
/// Struct containing all character data necessary to render a letter to the screen
/// </summary>
struct Character {
	Texture* texture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
	Renderable* renderable;
};

class TextRenderer
{
public:
	TextRenderer(FT_Face* face);
	~TextRenderer();

	void DrawText(int xPos, int yPos, std::string text, float fontSize, glm::vec4 color);

	Character LoadCharacterIntoMemory(char characterToLoad);
	
private:
	FT_Face* fontFace;

	static std::map<char, Character> characterCache;
};