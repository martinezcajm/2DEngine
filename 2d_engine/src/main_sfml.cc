#include <SFML/Graphics.hpp>
#include "rect.h"
#include "label.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    Rect *rect_test = Rect::CreateRect();
    Label *label_test = Label::CreateLabel();
    rect_test->init(1,
                    50,100, 
                    255,0,0,255,
                    0,255,0,255,
                    200, 300,
                    0,1,1);
    label_test->init(255,0,0,255,
                     500,400,
                     0,1,1,
                     "Hello world");
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
        label_test->draw(window);
        window.display();
    }
    delete rect_test;
    delete label_test;

    return 0;
}