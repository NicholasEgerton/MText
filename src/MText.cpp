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
    //Set the first glyph to be at the top left of this MText.
    //Must offset down by charSize on the y, as glyphs are constructed from the baseline.
    Vector2f offset{ 0.f, static_cast<float>(charSize) };
    Vector2f glyphPos = getPosition() + offset;

    //Loop through
    for (const char c : string) {
        const Glyph& glyph{ font->getGlyph(static_cast<char32_t>(c), charSize, false) };
        AddGlyphQuad(glyphPos, textColor, glyph);
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
