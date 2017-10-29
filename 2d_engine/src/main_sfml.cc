#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"

int main()
{
  
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  Rect *rect_test = Rect::CreateRect();
  Label *label_test = Label::CreateLabel();
  sf::Texture texture;
  texture.loadFromFile("../data/enemy.png");
  Sprite *sprite_test = Sprite::CreateSprite();
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
  sprite_test->init(0,0,
                   0,1,1,
                   texture);

  sf::Clock deltaClock;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);
      if (event.type == sf::Event::Closed){
          window.close();
      }
    }
    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

    window.clear();
    rect_test->draw(window);
    label_test->draw(window);
    sprite_test->draw(window);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
  delete rect_test;
  delete label_test;
  delete sprite_test;

  return 0;
}