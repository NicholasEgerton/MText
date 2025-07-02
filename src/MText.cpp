#include "MText.h"

using namespace sf;

MText::MText(const Font& font, const String string, const unsigned int charSize, const Color textColor) : font(&font), string(string), charSize(charSize), textColor(textColor)
{
    UpdateVertexArray();
}

void MText::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &font->getTexture(charSize);
	target.draw(vertexArray, states);
}

void MText::UpdateVertexArray()
{
    //Clear the vertex array.
    vertexArray.clear();

    //Check if the string is empty, if so, there is no need to update verticies.
    if (string.isEmpty()) {
        return;
    }

    //Set the first glyph to be at the top left of this MText.
    //Must offset down by charSize on the y, as glyphs are constructed from the baseline.
    Vector2f offset{ 0.f, static_cast<float>(charSize) };
    Vector2f glyphPos = getPosition() + offset;

    //Get the line spacing of this font.
    float lineSpacing = font->getLineSpacing(charSize);

    //Loop through each character in the string and add its glyph quad to the vertex array.
    for (const char c : string) 
    {
        const Glyph& glyph{ font->getGlyph(static_cast<char32_t>(c), charSize, false) };
        //Handle special characters:
        if (c == '\r') 
        {
            //Skip the 'r' character.
            continue;
        }
        
        else if (c == '\n')
        {
            //If there is a newline character, add the lineSpacing to the y to move down.
            //Also, set the x back to the far left of the text box.
            glyphPos.x = getPosition().x;
            glyphPos.y += lineSpacing;
            
            //Must continue so that the glyph.advance is not added to the x.
            continue;
        }

        else if (c != ' ' && c != '\t')
        {
            //Only draw the glyph if it is not a whitespace or an indent.
            //If it is, the glyph.advance will still be added.
            AddGlyphQuad(glyphPos, textColor, glyph);
        }

        glyphPos.x += glyph.advance;
    }
}

void MText::AddGlyphQuad(Vector2f position, Color color, const Glyph& glyph)
{
    const Vector2f padding(1.f, 1.f);

    const Vector2f p1 = glyph.bounds.position - padding;
    const Vector2f p2 = glyph.bounds.position + glyph.bounds.size + padding;

    const auto uv1 = Vector2f(glyph.textureRect.position) - padding;
    const auto uv2 = Vector2f(glyph.textureRect.position + glyph.textureRect.size) + padding;

    vertexArray.append({ position + Vector2f(p1.x, p1.y), color, {uv1.x, uv1.y} });
    vertexArray.append({ position + Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertexArray.append({ position + Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertexArray.append({ position + Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertexArray.append({ position + Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertexArray.append({ position + Vector2f(p2.x, p2.y), color, {uv2.x, uv2.y} });
}
