#pragma once
#include "SFML/Graphics.hpp"

class MText : public sf::Drawable, public sf::Transformable {
public:
	MText() = delete;
	MText(const sf::Font& font, const sf::String string, const unsigned int charSize, const sf::Color color);

private:
	//Received variables
	const sf::Font* font;
	sf::String string;
	unsigned int charSize;
	sf::Color textColor;
	////////////////////

	sf::VertexArray vertexArray{ sf::PrimitiveType::Triangles };

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/// <summary>
	/// Very similar to sf::Text::addGlyphQuad(), slightly modified for this class.
	/// </summary>
	/// <param name="position">Position of the glyph in the font texture.</param>
	/// <param name="color">Color of the glyph.</param>
	/// <param name="glyph">The glyph to add.</param>
	void AddGlyphQuad(sf::Vector2f position, sf::Color color, const sf::Glyph& glyph);

	void UpdateVertexArray();

	//Getters and Setters
	
	/// <summary>
	/// Get a reference to the font the text is using. If the font is a nullptr, returns an empty font.
	/// </summary>
	const sf::Font& GetFont() const
	{
		if (font == nullptr) {
			return sf::Font();
		}
		return *font;
	}
	/// <summary>
	/// Set the font the text is using.
	/// </summary>
	/// <param name="newFont"></param>
	void SetFont(const sf::Font& newFont)
	{
		font = &newFont;
	}
	/// <summary>
	/// Get the text's string.
	/// </summary>
	const sf::String GetString() const
	{
		return string;
	}
	/// <summary>
	/// Set the string of the text.
	/// </summary>
	/// <param name="newString"></param>
	void SetString(const sf::String newString)
	{
		string = newString;
	}
	/// <summary>
	/// Get the character size of the text.
	/// </summary>
	const unsigned int GetCharacterSize() const
	{
		return charSize;
	}
	/// <summary>
	/// Set the character size of the text.
	/// </summary>
	/// <param name="newCharSize"></param>
	void SetCharacterSize(const unsigned int newCharSize)
	{
		charSize = newCharSize;
	}
	/// <summary>
	/// Get the color of the text.
	/// </summary>
	const sf::Color GetTextColor() const
	{
		return textColor;
	}

	/// <summary>
	/// Set the color of the text.
	/// </summary>
	/// <param name="newTextColor"></param>
	void SetTextColor(const sf::Color newTextColor)
	{
		textColor = newTextColor;
	}
};