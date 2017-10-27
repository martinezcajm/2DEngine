#ifndef __DRAWABLE_ENTITY_H__
#define __DRAWABLE_ENTITY_H__ 1

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "entity.h"

class DrawableEntity : public Entity{
 public:
  DrawableEntity();
  void init(uint8_t r,uint8_t g,uint8_t b,uint8_t a, float px, float py,
            float rotation, float scalex, float scaley);
  /** @brief moves the entity
  *
  * moves the entity a number of points from it's original position x, y
  *
  * @return void
  * @param px quantity the entity will move in the x axis
  * @aram py quantity the entity will move in the y axis
  */
  void move(float px, float py);
  sf::Vector2f position_;
  float rotation_;
  sf::Vector2f scale_;
  sf::Color color_;
};

#endif