#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"

typedef enum UiStatus
{
    kDraw,
    kSelection
} UiStatus;

int main()
{
  uint8_t is_drawing = 0;
  uint8_t num_rectangles = 0;
  sf::Vector2i draw_origin_point = {0,0};
  sf::Vector2i draw_end_point = {0,0};
  UiStatus status = UiStatus::kSelection;
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);
  Rect *rect_container[Rect::kMaxRects];
  for(int i = 0; i < Rect::kMaxRects; i++){
    rect_container[i] = Rect::CreateRect();
  }
  //Rect *rect_test = Rect::CreateRect();
  Label *label_test = Label::CreateLabel();
  sf::Texture texture;
  texture.loadFromFile("../data/enemy.png");
  Sprite *sprite_test = Sprite::CreateSprite();
  /*rect_test->init(1,
                  50,100, 
                  255,0,0,255,
                  0,255,0,255,
                  200, 300,
                  0,1,1);*/
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
      if (event.type == sf::Event::MouseButtonPressed && 
          event.mouseButton.button == sf::Mouse::Left ) {
        if(status == UiStatus::kDraw){
          is_drawing = 1;
          draw_origin_point = sf::Mouse::getPosition(window);
          rect_container[num_rectangles]->init(1,
           0,0, 
           255,0,0,255,
           0,255,0,255,
           draw_origin_point.x, draw_origin_point.y,
           0,1,1);
          }
        }
        if (event.type == sf::Event::MouseButtonReleased && 
          event.mouseButton.button == sf::Mouse::Left ) {
          if(status == UiStatus::kDraw){
            draw_end_point = sf::Mouse::getPosition(window); 
            //We check that the user is not drawing a line (origin.x or y 
            //equals to endpoint.x or y)
            if((draw_origin_point.x!=draw_end_point.x) &&
               (draw_origin_point.y!=draw_end_point.y)){
              rect_container[num_rectangles]->resize(
                 draw_end_point.x - draw_origin_point.x,
                 draw_end_point.y - draw_origin_point.y);
              num_rectangles++;
            }
          }
        }
      }
      if(is_drawing){
        draw_end_point = sf::Mouse::getPosition(window); 
        rect_container[num_rectangles]->resize(
           draw_end_point.x - draw_origin_point.x,
           draw_end_point.y - draw_origin_point.y);
      }

      ImGui::SFML::Update(window, deltaClock.restart());

      ImGui::Begin("Options");
      if (ImGui::Button("Rect create")) {
        status = UiStatus::kDraw;
      }
      if (ImGui::Button("Selector")) {
        status = UiStatus::kSelection;
        is_drawing = 0;
      }
      ImGui::End();

      window.clear();
      for (auto const rectangle : rect_container){  
        if (rectangle->active_){
          rectangle->draw(window);
        }
      }
      //rect_test->draw(window);
      label_test->draw(window);
      sprite_test->draw(window);
      ImGui::SFML::Render(window);
      window.display();
    }
  ImGui::SFML::Shutdown();
  for(int i = 0; i < Rect::kMaxRects; i++){
    delete rect_container[i];
  }
  //delete rect_test;
  delete label_test;
  delete sprite_test;

  return 0;
}