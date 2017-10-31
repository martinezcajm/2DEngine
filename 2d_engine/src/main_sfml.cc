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
  kIdle,
  kDraw,
  kSelection,
  kWrite
} UiStatus;

int main()
{
  uint8_t is_drawing = 0;
  uint8_t num_rectangles = 0;
  sf::Vector2f mouse_position = {0,0};
  sf::Vector2f draw_origin_point = {0,0};
  sf::Vector2f draw_end_point = {0,0};
  UiStatus status = UiStatus::kSelection;
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  float color[3] = { 0.f, 0.f, 0.f };
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);
  uint8_t element_selected = 0;
  Rect *selection = nullptr;
  Rect *rect_container[Rect::kMaxRects];
  for(int i = 0; i < Rect::kMaxRects; i++){
    rect_container[i] = Rect::CreateRect();
  }
  //Rect *rect_test = Rect::CreateRect();
  Label *label_test = Label::CreateLabel();
  sf::Texture texture;
  texture.loadFromFile("../data/icons/draw.png");
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
        mouse_position = static_cast<sf::Vector2f>(
                         sf::Mouse::getPosition(window));
        if(status == UiStatus::kDraw){
          is_drawing = 1;
          draw_origin_point = mouse_position;
          rect_container[num_rectangles]->init(1,
           0,0, 
           255,0,0,255,
           0,255,0,255,
           draw_origin_point.x, draw_origin_point.y,
           0,1,1);
          }else if(status == UiStatus::kSelection){
            //element_selected = 0;
            for (auto const rectangle : rect_container){  
              if (rectangle->active_ && 
                  rectangle->checkCollision(mouse_position)){
                selection = rectangle;
                element_selected = 1;
              }
            }
          }
        }
        if (event.type == sf::Event::MouseButtonReleased && 
          event.mouseButton.button == sf::Mouse::Left ) {
          if(status == UiStatus::kDraw){
            mouse_position = static_cast<sf::Vector2f>(
                         sf::Mouse::getPosition(window));
            draw_end_point = mouse_position; 
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
        mouse_position = static_cast<sf::Vector2f>(
                         sf::Mouse::getPosition(window));
        draw_end_point = mouse_position; 
        rect_container[num_rectangles]->resize(
           draw_end_point.x - draw_origin_point.x,
           draw_end_point.y - draw_origin_point.y);
      }

      ImGui::SFML::Update(window, deltaClock.restart());

      ImGui::Begin("Options");
      if (ImGui::Button("Rect create")) {
        if(status == UiStatus::kDraw){
          status = UiStatus::kIdle;
          is_drawing = 0;
        }else{
          status = UiStatus::kDraw;
        }
      }
      ImGui::SameLine();
      if (ImGui::Button("Selector")) {
        if(status == UiStatus::kSelection){
          status = UiStatus::kIdle;
        }else{
          status = UiStatus::kSelection;
        }
        is_drawing = 0;
      }
      ImGui::SameLine();
      if (ImGui::Button("Text")) {
        if(status == UiStatus::kWrite){
          status = UiStatus::kIdle;
        }else{
          status = UiStatus::kWrite;
        }
        is_drawing = 0;
      }
      ImGui::End();
      static bool no_titlebar = false;
    static bool no_border = true;
    static bool no_resize = false;
    static bool no_move = false;
    static bool no_scrollbar = false;
    static bool no_collapse = false;
    static bool no_menu = false;


    ImGui::Begin("Selection");
      if(element_selected){
        if (ImGui::CollapsingHeader("Info")){
          ImGui::Text("position:{x:%f, y:%f} \n", selection->position_.x,
           selection->position_.y);
        }
        if (ImGui::CollapsingHeader("Edit")){
          if (ImGui::TreeNode("Position"))
          {
            ImGui::InputFloat("x", &selection->position_.x);
            ImGui::InputFloat("y", &selection->position_.y);
            ImGui::TreePop();
          }
          if (ImGui::TreeNode("Color"))
          {
            if (ImGui::ColorEdit3("Rect Color", color)) {
              selection->color_.r = static_cast<sf::Uint8>(color[0]);
              selection->color_.g = static_cast<sf::Uint8>(color[1]);
              selection->color_.b = static_cast<sf::Uint8>(color[2]);
              //selection->color_.a = static_cast<sf::Uint8>(color[3]);
            }
            ImGui::TreePop();
          }
          if (ImGui::TreeNode("Transformation"))
          {
            ImGui::InputFloat("rotation", &selection->rotation_);
            ImGui::InputFloat("scale", &selection->scale_.x);
            ImGui::TreePop();
          } 
        } 
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
      //ImGui::ShowTestWindow();
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