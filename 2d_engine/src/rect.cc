#include <ESAT/draw.h>
#include "rect.h"

void Rect::init(uint8_t is_solid, uint16_t width, uint16_t height,
                uint8_t sc_r, uint8_t sc_g, uint8_t sc_b, uint8_t sc_a,
                uint8_t fc_r, uint8_t fc_g, uint8_t fc_b, uint8_t fc_a,
                float px, float py){
  is_solid_ = is_solid;
  width_ = width;
  height_ = height;
  stroke_color_.r = sc_r;
  stroke_color_.g = sc_g;
  stroke_color_.b = sc_b;
  stroke_color_.a = sc_a;
  fill_color_.r = fc_r;
  fill_color_.g = fc_g;
  fill_color_.b = fc_b;
  fill_color_.a = fc_a;
  position_.x = px;
  position_.y = py;
}

//We draw the rectangle taking as the origin point the upper-left vertex. ToDo
//add te scalation and rotation
void Rect::draw(){
  float p[] = {
    position_.x,position_.y,
    position_.x + width_, position_.y,
    position_.x + width_, position_.y + height_,
    position_.x, position_.y + width_,
    position_.x,position_.y,
  };
  if(is_solid_ == 1){
    ESAT::DrawSetFillColor(fill_color_.r, fill_color_.g, fill_color_.b,
                           fill_color_.a);
  }
  ESAT::DrawSetStrokeColor(stroke_color_.r, stroke_color_.g, stroke_color_.b,
                           stroke_color_.a);

  ESAT::DrawSolidPath(p, 5, true);
}