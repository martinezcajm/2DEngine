#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "background.h"


typedef enum UiStatus
{
  kIdle,
  kDraw,
  kSelection,
  kWrite
} UiStatus;

typedef enum UiEditType
{
  kNull,
  kRect,
  kLabel
} UiEditType;

void UiPreloadCommonValues(DrawableEntity &d_entity){
  if (ImGui::TreeNode("Position")){
    ImGui::InputFloat("x", &d_entity.position_.x, 1.0f, 1.0f);
    ImGui::InputFloat("y", &d_entity.position_.y, 1.0f, 1.0f);
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Color")){
    float color[4] = { 0.f, 0.f, 0.f, 0.f };
    color[0] = static_cast<float>(d_entity.color_.r/255.f);
    color[1] = static_cast<float>(d_entity.color_.g/255.f); 
    color[2] = static_cast<float>(d_entity.color_.b/255.f); 
    color[3] = static_cast<float>(d_entity.color_.a/255.f); 
    if (ImGui::ColorEdit4("Rect Color", color)) {
      d_entity.color_.r = static_cast<sf::Uint8>(color[0] * 255.f);
      d_entity.color_.g = static_cast<sf::Uint8>(color[1] * 255.f);
      d_entity.color_.b = static_cast<sf::Uint8>(color[2] * 255.f);
      d_entity.color_.a = static_cast<sf::Uint8>(color[3] * 255.f);
    }
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Transformation")){
    ImGui::InputFloat("rotation", &d_entity.rotation_, 1.0f, 1.0f);
    ImGui::InputFloat("scalex", &d_entity.scale_.x, 1.0f, 1.0f);
    ImGui::InputFloat("scaley", &d_entity.scale_.y, 1.0f, 1.0f);
    ImGui::TreePop();
  } 
}

int main()
{
  uint8_t is_drawing = 0;
  uint8_t num_rectangles = 0;
  sf::Vector2f mouse_position = {0,0};
  sf::Vector2f draw_origin_point = {0,0};
  sf::Vector2f draw_end_point = {0,0};
  UiStatus status = UiStatus::kIdle;
  UiEditType edit_type = UiEditType::kLabel;
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);
  Rect *rect_selection = nullptr;
  Label *label_selection = nullptr;
  Rect *rect_container[Rect::kMaxRects];
  for(int i = 0; i < Rect::kMaxRects; i++){
    rect_container[i] = Rect::CreateRect();
  }
  sf::Font font;
  font.loadFromFile("../data/fonts/arial.ttf");
  Label *label_test = Label::CreateLabel();
  Sprite *sprite_from_image = Sprite::CreateSprite();
  Background *bg = Background::CreateBackground();
  sf::Texture texture;
  texture.loadFromFile("../data/icons/draw.png");
  
  Sprite *sprite_test = Sprite::CreateSprite();
  label_test->init(255,0,0,255,
                   500,400,
                   0,1,1,
                   "Hello world", font);
  sprite_test->init(0,0,
                   0,1,1,
                   texture);
  sprite_from_image->init(50,0,
                   0,1,1,
                   "../data/icons/draw.png");
  bg->init("../data/bg.png",window.getSize().x,window.getSize().y);

  bg->speed_.x = 1;
  //bg->speed_.y = 5;
  bg->scrolls_horizontally_ = 1;
  //bg->scrolls_vertically_ = 1;

  label_selection = label_test;

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
          event.mouseButton.button == sf::Mouse::Left &&
          !ImGui::IsAnyWindowHovered()) {
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
            //edit_type = UiEditType::kNull;
            for (auto const rectangle : rect_container){  
              if (rectangle->active_ && 
                  rectangle->checkCollision(mouse_position)){
                rect_selection = rectangle;
                edit_type = UiEditType::kRect;
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
      //To give a sense of mode selection, we give a redish color when the 
      //button is the currently selected and a blueish one whe it's not.
      if(status == UiStatus::kDraw){
        ImGui::PushStyleColor(ImGuiCol_Button, 
        ImVec4(0.65f,0.14f,0.14f,1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 
        ImVec4(0.6f,0.08f,0.08f,1.0f));
      }else{
        ImGui::PushStyleColor(ImGuiCol_Button, 
        ImVec4(0.0f,0.26f,0.69f,1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
        ImVec4(0.0f,0.21f,0.52f,1.0f)); 
      }
      
      if (ImGui::Button("Rect create")) {
        if(status == UiStatus::kDraw){
          status = UiStatus::kIdle;
          is_drawing = 0;
        }else{
          status = UiStatus::kDraw;
        }
      }
      ImGui::PopStyleColor(2);
      ImGui::SameLine();
      if(status == UiStatus::kSelection){
        ImGui::PushStyleColor(ImGuiCol_Button, 
        ImVec4(0.65f,0.14f,0.14f,1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 
        ImVec4(0.6f,0.08f,0.08f,1.0f));
      }else{
        ImGui::PushStyleColor(ImGuiCol_Button, 
        ImVec4(0.0f,0.26f,0.69f,1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
        ImVec4(0.0f,0.21f,0.52f,1.0f)); 
      }
      if (ImGui::Button("Selector")) {
        if(status == UiStatus::kSelection){
          status = UiStatus::kIdle;
        }else{
          status = UiStatus::kSelection;
        }
        is_drawing = 0;
      }
      ImGui::PopStyleColor(2);
      ImGui::SameLine();
      if(status == UiStatus::kWrite){
        ImGui::PushStyleColor(ImGuiCol_Button, 
        ImVec4(0.65f,0.14f,0.14f,1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 
        ImVec4(0.6f,0.08f,0.08f,1.0f));
      }else{
        ImGui::PushStyleColor(ImGuiCol_Button, 
        ImVec4(0.0f,0.26f,0.69f,1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
        ImVec4(0.0f,0.21f,0.52f,1.0f)); 
      }
      if (ImGui::Button("Text")) {
        if(status == UiStatus::kWrite){
          status = UiStatus::kIdle;
        }else{
          status = UiStatus::kWrite;
        }
        is_drawing = 0;
      }
      ImGui::PopStyleColor(2);
      ImGui::End();


    ImGui::Begin("Selection");

    if (ImGui::CollapsingHeader("Edit")){

      if(edit_type == UiEditType::kRect){
        UiPreloadCommonValues(*rect_selection);
      }else if(edit_type == UiEditType::kLabel){
        UiPreloadCommonValues(*label_selection);
        if (ImGui::TreeNode("label")){
          ImGui::InputInt("font size", 
                          &label_selection->font_size_,
                          1, 1);
          ImGui::InputText("text", label_selection->text_, 50);
          ImGui::TreePop();
        }
      }
    } 

    ImGui::End();
    window.clear();
    bg->update();
    bg->draw(window);
    for (auto const rectangle : rect_container){  
      if (rectangle->active_){
        rectangle->draw(window);
      }
    }
      
    label_test->draw(window);
    sprite_test->draw(window);
    sprite_from_image->draw(window);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
  for(int i = 0; i < Rect::kMaxRects; i++){
    delete rect_container[i];
  }
  delete label_test;
  delete sprite_test;
  delete sprite_from_image;

  return 0;
}