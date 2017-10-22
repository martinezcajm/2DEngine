#ifndef __RECT_H__
#define __RECT_H__ 1

#include <cstdint>
#include <ESAT/math.h>
#include "entity.h"

class Rect : public Entity{
 public:
  Rect();
  void init(uint8_t is_solid, float width, float height, uint8_t sc_r,
            uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
            uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py);
  void draw();
  void move(float px, float py);
  void resize(float width, float height);

  uint8_t is_solid_;
  ESAT::Vec2 position_;
  //Contains the width and height
  ESAT::Vec2 dimensions_;
  //ToDo add rotation and scale factors
  uint8_t rgba_stroke_[4];
  uint8_t rgba_fill_[4];
  float rotation_;
  ESAT::Vec2 scale_;
};

#endif