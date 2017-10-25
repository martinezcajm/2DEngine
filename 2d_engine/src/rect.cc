#include "rect.h"

uint32_t Rect::total_rects_ = 1;

Rect::Rect() : Entity() {
  is_solid_ = 0;
  position_.x = 0;
  position_.y = 0;
  dimensions_.x = 0;
  dimensions_.y = 0;
  rgba_stroke_.r = 0;
  rgba_stroke_.g = 0;
  rgba_stroke_.b = 0;
  rgba_stroke_.a = 0;
  rgba_fill_.r = 0;
  rgba_fill_.g = 0;
  rgba_fill_.b = 0;
  rgba_fill_.a = 0;
  rotation_ = 0.0f;
  scale_.x = 1;
  scale_.y = 1;
  total_rects_ ++;
}

void Rect::init(uint8_t is_solid, float width, float height, uint8_t sc_r,
                uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
                uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py){
  Entity::init();
  is_solid_ = is_solid;
  dimensions_.x = width;
  dimensions_.y = height;
  rgba_stroke_.r = sc_r;
  rgba_stroke_.g = sc_g;
  rgba_stroke_.b = sc_b;
  rgba_stroke_.a = sc_a;
  rgba_fill_.r = fc_r;
  rgba_fill_.g = fc_g;
  rgba_fill_.b = fc_b;
  rgba_fill_.a = fc_a;
  position_.x = px;
  position_.y = py;
}

void Rect::draw(sf::RenderWindow *window){
  sf::RectangleShape rectangle(dimensions_);
  rectangle.setPosition(position_.x, position_.y);
  if(is_solid_){
    rectangle.setFillColor(rgba_stroke_);
  }
  rectangle.setOutlineThickness(2);
  rectangle.setOutlineColor(rgba_fill_);
  rectangle.rotate(rotation_);
  rectangle.scale(scale_.x, scale_.y);
  window->draw(rectangle);
}

void Rect::move(float px, float py){
  position_.x += px;
  position_.y += py;
}

void Rect::resize(float width, float height){
  dimensions_.x = width;
  dimensions_.y = height;
}

Rect* Rect::CreateRect(){
  if(Rect::total_rects_ < kMaxRects){
    Rect* p_rect = new Rect();
    return p_rect;
  }else{
    return nullptr;
  }
}