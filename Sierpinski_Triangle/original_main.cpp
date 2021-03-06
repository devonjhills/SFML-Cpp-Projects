#include <iostream>
#include <cstdlib>
#include "original.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    //Give user Instructions if input is incorrect
    if(argc <= 1)
    {
        cout << "main [window size] [depth]" << endl;
        return 0;
    }

    //Insufficient # of inputs error
    if(argc < 3)
    {
        cout << "Error: insufficient number of inputs" << endl;
        return -1;
    }

    //convert user input to integers
    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);

    //invalid depth level error
    if(arg2 < 0)
    {
        cout << "Error: Invalid depth level, must be >= 0" << endl;
        return -1;
    }

    //create window based on user inputs
    sf::RenderWindow window(sf::VideoMode(arg1, arg1), "Devon Hills");

    //create mydesign circle using user inputs
    MyDesign circles(arg2, arg1/2, arg1/2, arg1/2);

    //event loop to draw circles
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circles);
        window.display();
        sf::sleep(sf::seconds(1));
    }

    return 0;
}
