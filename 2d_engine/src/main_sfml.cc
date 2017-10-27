#include <SFML/Graphics.hpp>
#include "rect.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    Rect *rect_test = Rect::CreateRect();
    rect_test->init(1,
                    50,100, 
                    255,0,0,255,
                    0,255,0,255,
                    200, 300);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        rect_test->draw(window);
        window.display();
    }

    return 0;
}