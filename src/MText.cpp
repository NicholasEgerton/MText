#include "MText.h"

using namespace sf;

MText::MText(const Font& font, const String string, const unsigned int charSize, const Color textColor) : font(&font), string(string), charSize(charSize), textColor(textColor)
{
    UpdateText();
}

void MText::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &font->getTexture(charSize);
	target.draw(vertexArray, states);
}

void MText::UpdateText()
{
    //Clear the vertex array.
    vertexArray.clear();

    //Check if the string is empty, if so, there is no need to update verticies.
    if (string.isEmpty()) {
        return;
    }

    //Make an example symbol of the letter h and add it to the vertex array.
    Vector2f testPosition{ 500.f, 500.f };
    Color testColor{ Color::Blue };
    const Glyph& testGlyph{ font->getGlyph(static_cast<char32_t>('h'), charSize, false) };
    std::vector<Symbol> testSymbol;
    testSymbol.push_back({ testPosition, testColor, testGlyph });

    AddSymbolsToVertexArray(testSymbol);
}

void MText::AddSymbolsToVertexArray(const std::vector<Symbol>& symbols)
{
    //Loop through each glyph and add its quad to the vertex array.
    for (const Symbol& symbol : symbols)
    {
        AddSymbolQuad(symbol);
    }
}

void MText::AddSymbolQuad(const Symbol symbol)
{
    const Vector2f position = symbol.position;
    const Color color = symbol.color;
    const Glyph& glyph = symbol.glyph;

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
