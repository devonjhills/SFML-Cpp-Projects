#ifndef MYDESIGN_H
#define MYDESIGN_H

#include <SFML/Graphics.hpp>
#include <cmath>

/**
    My design class, recursive circles
*/
class MyDesign: public sf::Drawable
{
public:
    MyDesign(int depth, float radius, float x, float y);

    virtual ~MyDesign(); //destructor

    void setDepth(int depth); //depth setter
    int getDepth() const; // depth getter

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    void subCircles(sf::RenderTarget& target, float radius,
        float x, float y, int n) const;
    int depth; //level of recursion
    float radius, x, y; //koch info
};


#endif
