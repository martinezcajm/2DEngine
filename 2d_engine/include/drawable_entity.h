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
  * @param py quantity the entity will move in the y axis
  */
  void move(float px, float py);
  /** @brief draws a drawable entity
  *
  * this method is in charge of applying the transformations that are common
  * to all drawable_entities using the transform class of SFML (uses matrix)  
  * and finally drawing it to the window.
  *
  * @return void
  * @param window window in wich the entity will be drawn.
  * @param entity entity that will be drawn.
  * @rotation_origin origin point from wich the rotation will be done.
  */
  void draw(sf::RenderWindow &window, const sf::Drawable &entity, 
            const sf::Vector2f &rotation_origin);
  uint32_t z_order_;
  float rotation_;
  sf::Vector2f position_;  
  sf::Vector2f scale_;
  sf::Color color_;
};

#endif