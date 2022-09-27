#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Mandelbrot Set", Style::Default);

    Font mainFont;
    mainFont.loadFromFile("fonts/VT323-Regular.ttf");

    Text titleText;
    titleText.setFont(mainFont);
    titleText.setString("Welcome to the Mandelbrot Set!");
    titleText.setCharacterSize(30);
    titleText.setColor(Color::White);
    titleText.setPosition(Vector2f(10, 10));

    // Main while-loop which loops forever until the game is exited
    while (window.isOpen())
    {
        /*
        ##############################
        Handle User Input
        ##############################
        */
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                {
                    window.close();
                }
        }

        /*
        ##############################
        Update the Scene
        ##############################
        */


        /*
        ##############################
        Draw the Scene
        ##############################
        */

        // Clear the Window
        window.clear();

        // Draw Stuff
        window.draw(titleText);

        // Display Draw Buffer
        window.display();

    }

    return 0;
}