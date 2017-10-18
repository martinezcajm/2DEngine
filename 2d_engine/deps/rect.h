#ifndef __RECT_H__
#define __RECT_H__ 1

#include <cstdint>
#include "entity.h"

struct Position {
  float x;
  float y;
};

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

class Rect : public Entity{
 public:
  void init(uint8_t is_solid, uint16_t width, uint16_t height, uint8_t sc_r,
            uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
            uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py);
  void draw();

  uint8_t is_solid_;
  uint16_t width_;
  uint16_t height_;
  //ToDo add rotation and scale factors
  Color stroke_color_;
  Color fill_color_;
  Position position_;
};

#endif