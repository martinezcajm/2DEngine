#include "rect.h"

uint32_t Rect::total_rects_ = 1;

Rect::Rect() : DrawableEntity() {
  is_solid_ = 0;
  dimensions_.x = 0;
  dimensions_.y = 0;
  rgba_fill_.r = 0;
  rgba_fill_.g = 0;
  rgba_fill_.b = 0;
  rgba_fill_.a = 0;
  total_rects_ ++;
}

void Rect::init(uint8_t is_solid, float width, float height, uint8_t sc_r,
                uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
                uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py,
                float rotation, float scalex, float scaley){
  DrawableEntity::init(sc_r,sc_g,sc_b,sc_a, px,py, rotation, scalex,scaley);
  is_solid_ = is_solid;
  dimensions_.x = width;
  dimensions_.y = height;
  rgba_fill_.r = fc_r;
  rgba_fill_.g = fc_g;
  rgba_fill_.b = fc_b;
  rgba_fill_.a = fc_a;
}

//TODO create the rectangle shape out of draw
void Rect::draw(sf::RenderWindow &window){
  sf::RectangleShape rectangle(dimensions_);
  rectangle.setPosition(position_.x, position_.y);
  if(is_solid_){
    rectangle.setFillColor(color_);
  }
  rectangle.setOutlineThickness(2);
  rectangle.setOutlineColor(rgba_fill_);
  rectangle.rotate(rotation_);
  rectangle.scale(scale_.x, scale_.y);
  window.draw(rectangle);
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

//TODO implement destructor that will free the rectangle shape