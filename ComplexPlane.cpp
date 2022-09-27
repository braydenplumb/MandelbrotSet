#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <cmath>
#include <sstream>

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * aspectRatio);
    m_view.setCenter(0.0, 0.0);
    m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    int x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    int y_size = BASE_HEIGHT * pow(BASE_ZOOM, m_zoomCount);
    m_view.setSize(x_size, y_size);
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    int x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    int y_size = BASE_HEIGHT * pow(BASE_ZOOM, m_zoomCount);
    m_view.setSize(x_size, y_size);
}

void ComplexPlane::setCenter(Vector2f coord)
{
    m_view.setCenter(coord);
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
    m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
    // Figure out string stream stuff
    stringstream infoStream;

    infoStream << "(" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")";

    text.setString(infoStream.str());

}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    size_t size = 1;
    return size;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

    if (count == -1) {
        r = 0;
        g = 0;
        b = 0;
    } else if (count == 0) {
        r = 255;
        g = 0;
        b = 0;
    } else {
        // colour gradient:      Red -> Blue -> Green -> Red -> Black
        // corresponding values:  0  ->  16  ->  32   -> 64  ->  127 (or -1)
        if (count < 16) {
            r = 16 * (16 - count);
            g = 0;
            b = 16 * count - 1;
        } else if (count < 32) {
            r = 0;
            g = 16 * (count - 16);
            b = 16 * (32 - count) - 1;
        } else if (count < 64) {
            r = 8 * (count - 32);
            g = 8 * (64 - count) - 1;
            b = 0;
        } else { // range is 64 - 127
            r = 255 - (count - 64) * 4;
            g = 0;
            b = 0;
        }
    }
}