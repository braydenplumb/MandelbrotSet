#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <complex>

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

View ComplexPlane::getView(){
    return m_view;
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
    size_t size = 0;

    complex<long double> c (coord.x, coord.y);
    complex<long double> z (0, 0);

    z = z*z + c;

    while( ((z.real()*z.real() + z.imag() * z.imag()) <= 10) && ((int)size <= MAX_ITER) )
    {
      z = z*z + c;
      size++;
    }
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
        if (count < 4) {
            r = 254;
            g = 168;
            b = 95;
        }
        else if (count < 14) {
            r = 206;
            g = 127;
            b = 129;
        }
        
        else if (count < 28) {
            r = 226;
            g = 97;
            b = 89;
        } else if (count < 64) {
            r = 226;
            g = 28;
            b = 97;
        } else { // range is 64 - 127
            r = 56;
            g = 22;
            b = 49;
        }
    }
}