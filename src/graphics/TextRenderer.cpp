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
        FT_UInt  glyph_index = GetCharIndex(text[i]);
        FT_Error error;

        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Glyph(*fontFace, glyph_index, FT_LOAD_DEFAULT);
        if (error)
            continue;  /* ignore errors */

          /* convert to an anti-aliased bitmap */
        error = FT_Render_Glyph((*fontFace)->glyph, FT_RENDER_MODE_NORMAL);
        if (error)
            continue;

       

        /* increment pen position */
        //xPos += slot->advance.x >> 6;
        //yPos += slot->advance.y >> 6; /* not useful for now */
    }
}