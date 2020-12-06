#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>


class TextRenderer
{
public:
	TextRenderer(FT_Face* face);
	~TextRenderer();

	void DrawText(int xPos, int yPos, std::string text, int fontSize);
	
private:
	FT_Face* fontFace;

	unsigned int GetCharIndex(char charToFind);
};