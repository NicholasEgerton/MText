#include <SFML/Graphics.hpp>
#include "MText.h"
#include "Errors.h"
#include <stdexcept>

using namespace sf;

int main()
{
    try {
        //Create a new window.
        RenderWindow window = RenderWindow(VideoMode({ 1920u, 1080u }), "MTextExample");
        window.setVerticalSyncEnabled(true);

        //Load the font roboto.
        const Font roboto("resources/fonts/cambria.ttc");

        //Create the example MText object.
        MText mText{ roboto, String("hello world!\nA new paragraph!\nThis:\tis a tab!\n\tAnd this is an tabbed paragraph!"), 70, Color::White };

        try {
            //Loop continously while the window is open.
            while (window.isOpen())
            {
                while (const std::optional event = window.pollEvent())
                {
                    //Close the window if it has been requested to.
                    if (event->is<Event::Closed>())
                    {
                        window.close();
                    }
                }

                //Clear the window.
                window.clear();

                window.draw(mText);

                //Display the contents.
                window.display();
            }
        }

        catch (const std::exception& e) {
            std::string msg{ "Runtime Error: " };
            msg += e.what();
            Errors::ShowError(msg);
            return EXIT_FAILURE;
        }
    }

    catch (const std::exception& e) {
        std::string msg{ "Initialisation Error: " };
        msg += e.what();
        Errors::ShowError(msg);
        return EXIT_FAILURE;
    }

    catch (...) {
        Errors::ShowError("An unknown error occured.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
