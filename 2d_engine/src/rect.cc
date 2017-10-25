#include <ESAT/draw.h>
#include "rect.h"

uint32_t Rect::total_rects_ = 1;

Rect::Rect() : Entity() {
  //Entity::Entity();
  is_solid_ = 0;
  position_.x = 0;
  position_.y = 0;
  dimensions_.x = 0;
  dimensions_.y = 0;
  rgba_stroke_[0] = 0;
  rgba_stroke_[1] = 0;
  rgba_stroke_[2] = 0;
  rgba_stroke_[3] = 0;
  rgba_fill_[0] = 0;
  rgba_fill_[1] = 0;
  rgba_fill_[2] = 0;
  rgba_fill_[3] = 0;
  rotation_ = 0.0f;
  scale_.x = 0;
  scale_.y = 0;
  total_rects_ ++;
}

void Rect::init(uint8_t is_solid, float width, float height, uint8_t sc_r,
                uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
                uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py){
  Entity::init();
  is_solid_ = is_solid;
  dimensions_.x = width;
  dimensions_.y = height;
  rgba_stroke_[0] = sc_r;
  rgba_stroke_[1] = sc_g;
  rgba_stroke_[2] = sc_b;
  rgba_stroke_[3] = sc_a;
  rgba_fill_[0] = fc_r;
  rgba_fill_[1] = fc_g;
  rgba_fill_[2] = fc_b;
  rgba_fill_[3] = fc_a;
  position_.x = px;
  position_.y = py;
}

//We draw the rectangle taking as the origin point the upper-left vertex. ToDo
//add te scalation and rotation
void Rect::draw(){
  float p[] = {
    position_.x,position_.y,
    position_.x + dimensions_.x, position_.y,
    position_.x + dimensions_.x, position_.y + dimensions_.y,
    position_.x, position_.y + dimensions_.y,
    position_.x,position_.y,
  };
  if(is_solid_){
	  ESAT::DrawSetFillColor(rgba_fill_[0], rgba_fill_[1], rgba_fill_[2], rgba_fill_[3]);
	  
  }
  ESAT::DrawSetStrokeColor(rgba_stroke_[0], rgba_stroke_[1], rgba_stroke_[2], rgba_stroke_[3]);

  ESAT::DrawSolidPath(p, 5, true);
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