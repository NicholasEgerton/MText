#include <SFML/Graphics.hpp>
#include "MText.h"

using namespace sf;

int main()
{
    RenderWindow window = RenderWindow(VideoMode({1920u, 1080u}), "MTextExample");

    const Font roboto("resources/fonts/cambria.ttc");

    MText mText{ roboto, String("hello world"), 30 };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
