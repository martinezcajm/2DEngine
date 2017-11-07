#ifndef __DRAWABLE_ENTITY_H__
#define __DRAWABLE_ENTITY_H__ 1

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "entity.h"

class DrawableEntity : public Entity{
 public:
  DrawableEntity();
  void init(const uint8_t r, const uint8_t g, const uint8_t b ,const uint8_t a,
            const float px, const float py,
            const float rotation, const float scalex, const float scaley);
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
  /** @Checks if a point collides with the entity
  *
  * Checks if the point passed by reference collides with the boundaries.
  *
  * @return bool returns true if the point collides and false if not.
  */
  //TODO make checkCollision virtual
  bool checkCollision(const sf::Vector2f &position,
                       const sf::FloatRect &boundaries);
  /** @Resets the values of the entity
  *
  * Sets the attributes of the object to return it to a pool and being able
  * to reuse it later.
  *
  * @return void
  */
  void unuse();
  int32_t z_order_;
  float rotation_;
  sf::Vector2f position_;  
  sf::Vector2f scale_;
  sf::Color color_;
};

#endif