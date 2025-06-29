#pragma once
#include "SFML/Graphics.hpp"

class MText : public sf::Drawable, public sf::Transformable {
public:
	MText() = delete;
	MText(const sf::Font& font, const sf::String string, const unsigned int charSize) : font(&font), string(string), charSize(charSize) {};

private:
	//Received variables
	const sf::Font* font;
	sf::String string;
	unsigned int charSize;
	////////////////////

	sf::Text text{ *font, string, charSize };

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};