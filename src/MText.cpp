#include "MText.h"

using namespace sf;

void MText::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(text, states);
}
