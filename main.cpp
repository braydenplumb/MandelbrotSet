#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    Vector2f resolution;
    resolution.x = 600;
    resolution.y = 600;
    RenderWindow window(VideoMode(resolution.x, resolution.y),"Mandlebrot", Style::Default);

    // Create a an SFML View for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
    

    // Where is the mouse in relation to world coordinates
    Vector2f mouseWorldPosition;
    // Where is the mouse in relation to screen coordinates
    Vector2i mouseScreenPosition;

    ComplexPlane mandelbrotPlane(resolution.y / resolution.x);

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
        
    VertexArray planePoints(Points);
    planePoints.resize(resolution.x * resolution.y);

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
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, mandelbrotPlane.getView());

            if (event.type == sf::Event::MouseMoved)
            {
                Vector2i pixelPos = sf::Mouse::getPosition(window);
                Vector2f planePosition = window.mapPixelToCoords(pixelPos, mandelbrotPlane.getView());

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
                    Vector2f planePosition = window.mapPixelToCoords(pixelPos, mandelbrotPlane.getView());

                    mandelbrotPlane.setCenter(planePosition);
                    mandelbrotPlane.zoomIn();
                    currentState = CALCULATING;
                }
                
                if (event.mouseButton.button == sf::Mouse::Right)// zoom out
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    Vector2i pixelPos = sf::Mouse::getPosition(window);
                    Vector2f planePosition = window.mapPixelToCoords(pixelPos, mandelbrotPlane.getView());

                    mandelbrotPlane.setCenter(planePosition);
                    mandelbrotPlane.zoomOut();
                    currentState = CALCULATING;
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
            case CALCULATING :
            {
                int pointCounter = 0;
                for (int j = 0; j < resolution.x; j++)
                {
                    for (int i = 0; i < resolution.y; i++)
                    {
                        planePoints[pointCounter].position = { (float)j,(float)i };
                        Vector2f planePosition = window.mapPixelToCoords(Vector2i(j, i), mandelbrotPlane.getView());

                        size_t iterations = mandelbrotPlane.countIterations(planePosition);
                        Uint8 r;
                        Uint8 g;
                        Uint8 b;
                        mandelbrotPlane.iterationsToRGB(iterations, r, g, b);

                        planePoints[pointCounter].color = {r, g, b};

                        pointCounter++;

                        if (pointCounter % (600 * 100) == 0)
                        {
                            window.clear();
                            window.draw(planePoints);
                            window.display();
                        }

                    }
                }

                currentState = DISPLAYING;
                break;
            }
            case DISPLAYING :
                break;
        };

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();
        window.draw(planePoints);
        mandelbrotPlane.loadText(infoText);
        window.draw(infoText);
        window.display();
    }
}