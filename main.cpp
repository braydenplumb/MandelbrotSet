#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

sf::Color getColor(int);
enum building{
  CALCULATING,
  DISPLAYING,
};

int main()
{
    // Create a video mode object
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y),"Mandlebrot", Style::Fullscreen);

    // Create a an SFML View for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
    

    // Where is the mouse in relation to world coordinates
    Vector2f mouseWorldPosition;
    // Where is the mouse in relation to screen coordinates
    Vector2i mouseScreenPosition;

    ComplexPlane mandelbrotPlane(1);

    Font mainFont;
    mainFont.loadFromFile("fonts/VT323-Regular.ttf");

    Text infoText;
    infoText.setFont(mainFont);
    infoText.setString("Mandelbrot Set");
    infoText.setCharacterSize(30);
    infoText.setColor(Color::White);
    infoText.setPosition(Vector2f(10, 10));

    //Construct an object of type ComplexPlane
    //Construct Font and Text objects
        
    VertexArray Points;

    //Create an enum class state variable with states CALCULATINGand DISPLAYING
    enum states {
        CALCULATING,
        DISPLAYING
    };

    states currentState = CALCULATING;
    

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }

            // get the current mouse position in the window
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

            // convert it to world coordinates
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            if (event.type == sf::Event::MouseMoved)
            {
                Vector2i pixelPos = sf::Mouse::getPosition(window);
                Vector2f planePosition = window.mapPixelToCoords(pixelPos);

                mandelbrotPlane.setMouseLocation(planePosition);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) //zoom in
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    Vector2i pixelPos = sf::Mouse::getPosition(window);
                    Vector2f planePosition = window.mapPixelToCoords(pixelPos);

                    mandelbrotPlane.setCenter(planePosition);
                    mandelbrotPlane.zoomIn();
                }
                
                if (event.mouseButton.button == sf::Mouse::Right)// zoom out
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    Vector2i pixelPos = sf::Mouse::getPosition(window);
                    Vector2f planePosition = window.mapPixelToCoords(pixelPos);

                    mandelbrotPlane.setCenter(planePosition);
                    mandelbrotPlane.zoomOut();
                }
              //Set the state to CALCULATING to generate the new complex plane view in the update segment
            // mousemove event
              
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */



        switch (currentState)
        {
            CALCULATING:

                break;
            DISPLAYING:

                break;
        };

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        mandelbrotPlane.loadText(infoText);

        window.draw(infoText);

        window.display();
    }
}