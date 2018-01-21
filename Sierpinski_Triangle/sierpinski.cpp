#include "sierpinski.hpp"

/**
    Constructor to set initial Sierpinski values and depth
*/
Sierpinski::Sierpinski(int depth, float x, float y, float length)
{
    this->length = length;
    this->x = x;
    this->y = y;

    this->depth = depth;
}

/**
    Destructor
*/
Sierpinski::~Sierpinski()
{
}

/**
    Depth getter
*/
int Sierpinski::getDepth() const
{
    return this->depth;
}

/**
    Depth setter
*/
void Sierpinski::setDepth(int depth)
{
    this->depth = depth;
}


/**
    Implemented draw function to draw Sierpinski triangles
*/
void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    int n = getDepth();

    sf::ConvexShape baseTriangle;
    baseTriangle.setPointCount(3);
    baseTriangle.setPoint(0, sf::Vector2f(length/2,length - (length*(sqrt(3)))/2));
    baseTriangle.setPoint(1, sf::Vector2f(0, length));
    baseTriangle.setPoint(2, sf::Vector2f(length, length));
    //baseTriangle.setFillColor(sf::Color::Green);
    baseTriangle.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));
    target.draw(baseTriangle);

    //call recursive subtriangles function
    subTriangles(target, n, x, y, length);
}


/**
    Function to recursively draw serpinski pattern based on depth (n)
*/
void Sierpinski::subTriangles(sf::RenderTarget& target, int n, float x,
    float y, float length) const
{
    float height = ((length*(sqrt(3)))/2);

    //draw initial upside down triangle
    sf::ConvexShape subTriangle;
    subTriangle.setPointCount(3);
    subTriangle.setPoint(0, sf::Vector2f(x,y));
    subTriangle.setPoint(1, sf::Vector2f(x+length,y));
    subTriangle.setPoint(2, sf::Vector2f(length/2+ x,height + y));
    //subTriangle.setFillColor(sf::Color::Black);
    subTriangle.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));

    target.draw(subTriangle);

    //recursively draw each set of three additional triangles
    if(n > 0)
    {
        subTriangles(target, n-1, x-(length/4), y+height/2, length/2);
        subTriangles(target, n-1, x+((3*length)/4), y+height/2, length/2);
        subTriangles(target, n-1, x+(length)/4, y-height/2, length/2);
    }
}
