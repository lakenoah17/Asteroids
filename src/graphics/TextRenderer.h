#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include <string>
#include <map>

#include "VertexBufferLayout.h"

struct Character {
	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
	VertexBuffer* vb;
};

class TextRenderer
{
public:
	TextRenderer(FT_Face* face);
	~TextRenderer();

	void DrawText(int xPos, int yPos, std::string text, int fontSize);

	Character LoadCharacterIntoMemory(char characterToLoad);
	
private:
	FT_Face* fontFace;

	unsigned int GetCharIndex(char charToFind);

	static std::map<char, Character> characterCache;
};