#ifndef SIERPINKSI_H
#define SIERPINSKI_H

#include <SFML/Graphics.hpp>
#include <cmath>

/**
    Sierpniski triangle class
*/
class Sierpinski: public sf::Drawable
{
public:
    Sierpinski(int depth, float x, float y, float length);

    virtual ~Sierpinski(); //destructor

    void setDepth(int depth); //depth setter
    int getDepth() const; // depth getter

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    void subTriangles(sf::RenderTarget& target, int n, float x,
        float y, float length) const;
    int depth; //level of recursion
    float x, y, length; //triangle info
};


#endif
