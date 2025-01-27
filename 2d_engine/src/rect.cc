// rect.cc
// Jose Maria Martinez
// Implementation of rect. Representation of a Rectangle in the engine.
//Comments for the functions can be found at the header
#include "rect.h"

uint32_t Rect::total_rects_ = 0;

Rect::Rect() : DrawableEntity() {
  is_solid_ = 0;
  dimensions_.x = 0;
  dimensions_.y = 0;
  rgba_fill_.r = 0;
  rgba_fill_.g = 0;
  rgba_fill_.b = 0;
  rgba_fill_.a = 0;
  total_rects_ ++;
  type_ = kRect;
}

Rect::~Rect(){ }

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

void Rect::draw(sf::RenderWindow &window){
  sf::RectangleShape rectangle(dimensions_);
  if(is_solid_){
    rectangle.setFillColor(color_);
  }else{
    rectangle.setFillColor(sf::Color{0,0,0,0});
  }
  rectangle.setOutlineThickness(2);
  rectangle.setOutlineColor(rgba_fill_);
  sf::Vector2f rotation_origin = {(dimensions_.x/2)*scale_.x
                                  ,(dimensions_.y/2)*scale_.y};
  DrawableEntity::drawWithTransform(window, rectangle, rotation_origin);
}

void Rect::resize(const float width, const float height){
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

void Rect::unuse(){
  is_solid_ = 0;
  dimensions_.x = 0;
  dimensions_.y = 0;
  rgba_fill_.r = 0;
  rgba_fill_.g = 0;
  rgba_fill_.b = 0;
  rgba_fill_.a = 0;
  DrawableEntity::unuse();
}

void Rect::update(){}

sf::FloatRect Rect::getBoundaries(){
  sf::RectangleShape rectangle(dimensions_);
  rectangle.setOutlineThickness(2);
  sf::Vector2f rotation_origin = { (dimensions_.x / 2)*scale_.x,
                                   (dimensions_.y / 2)*scale_.y};
  sf::Transform t;
  t.translate(position_);
  t.rotate(rotation_, rotation_origin);
  t.scale(scale_);
  
  sf::FloatRect boundaries = rectangle.getLocalBounds();
  return t.transformRect(boundaries);
}