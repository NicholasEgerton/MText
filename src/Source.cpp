#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window = RenderWindow(VideoMode({1920u, 1080u}), "MTextExample");

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
