#ifndef __RECT_H__
#define __RECT_H__ 1

#include "drawable_entity.h"

class Rect : public DrawableEntity{
 public:
  void init(uint8_t is_solid, float width, float height, uint8_t sc_r,
            uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
            uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py,
            float rotation, float scalex, float scaley);
  void draw(sf::RenderWindow &window);
  void resize(float width, float height);
  static Rect* Rect::CreateRect();
  
  static const uint8_t kMaxRects = 50;
  uint8_t is_solid_;
  //Contains the width and height
  sf::Vector2f dimensions_;
  sf::Color rgba_fill_;
 private:
  Rect();
  Rect(const Rect& o){};
  static uint32_t total_rects_;
};

#endif