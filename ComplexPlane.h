#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
using namespace sf;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

class ComplexPlane {
    public:
        ComplexPlane(float aspectRatio);
        void zoomIn();
        void zoomOut();
        void setCenter(Vector2f coord);
        View getView();
        void setMouseLocation(Vector2f position);
        void loadText(Text& text);
        static size_t countIterations(Vector2f coord);
        static void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);

    private:
        View m_view;
        float m_aspectRatio;
        float m_zoomCount;
        Vector2f m_mouseLocation;
        
};

#endif