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

	Character LoadCharacterIntoMemory(char characterToLoad, float scale);
	
private:
	FT_Face* fontFace;

	unsigned int GetCharIndex(char charToFind);

	static std::map<char, Character> characterCache;
};