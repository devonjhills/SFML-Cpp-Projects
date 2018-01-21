#include "original.hpp"

/**
    Constructor to set initial circle values and depth
*/
MyDesign::MyDesign(int depth, float radius, float x, float y)
{
    this->radius = radius;
    this->depth = depth;
    this->x = x;
    this->y = y;
}

/**
    Destructor
*/
MyDesign::~MyDesign()
{
}

/**
    Depth getter
*/
int MyDesign::getDepth() const
{
    return this->depth;
}

/**
    Depth setter
*/
void MyDesign::setDepth(int depth)
{
    this->depth = depth;
}


/**
    Implemented draw function to draw circles
*/
void MyDesign::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    int n = getDepth();

    subCircles(target, radius, x, y, n);
}


/**
    Recursive function to create all subcircles based on depth (n)
*/
void MyDesign::subCircles(sf::RenderTarget& target, float radius,
    float x, float y, int n) const
{
    sf::CircleShape subc(radius,1000);
    subc.setPosition(x-radius,y-radius);
    subc.setFillColor(sf::Color::Transparent);
    subc.setOutlineThickness(1);
    subc.setOutlineColor(sf::Color(rand()%255, rand()%255, rand()%255));


    target.draw(subc);
    //draw circles, 4 recursive statements
    if(n > 0)
    {
        subCircles(target, radius/2, x-radius/2, y, n-1);
        subCircles(target, radius/2, x+radius/2, y, n-1);
        subCircles(target, radius/2, x, y-radius/2, n-1);
        subCircles(target, radius/2, x, y+radius/2, n-1);
    }
}
