#ifndef __RECT_H__
#define __RECT_H__ 1

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "entity.h"

class Rect : public Entity{
 public:
  void init(uint8_t is_solid, float width, float height, uint8_t sc_r,
            uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
            uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py);
  void draw(sf::RenderWindow &window);
  void move(float px, float py);
  void resize(float width, float height);
  static Rect* Rect::CreateRect();
  
  static const uint8_t kMaxRects = 50;
  uint8_t is_solid_;
  sf::Vector2f position_;
  //Contains the width and height
  sf::Vector2f dimensions_;
  sf::Color rgba_stroke_;
  sf::Color rgba_fill_;
  float rotation_;
  sf::Vector2f scale_;
 private:
  Rect();
  Rect(const Rect& o){};
  static uint32_t total_rects_;
};

#endif