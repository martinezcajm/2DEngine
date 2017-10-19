#include <ESAT/draw.h>
#include "rect.h"

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