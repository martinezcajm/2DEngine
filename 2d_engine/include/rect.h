#ifndef __RECT_H__
#define __RECT_H__ 1

#include "drawable_entity.h"

class Rect : public DrawableEntity{
 public:
  void init(uint8_t is_solid, float width, float height, uint8_t sc_r,
            uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
            uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py,
            float rotation, float scalex, float scaley);
  /** @Draws the graphic entity Rectangle
  *
  * Draws the rectangle using SFML to the window passed by reference 
  *
  * @return void
  * @param window SFML RenderWindow passed by reference
  */
  void draw(sf::RenderWindow &window);
  /** @Changes the size of the rect
  *
  * Sets the value of width and height for the rect to the ones indicated by 
  *parameter. 
  *
  * @width new width of the rectangle
  * @height new height of the rectangle
  */
  void resize(const float width, const float height);
  /** @Factory that creates rect
  *
  * Checks that the number of rects didn't pass the maxim amount established
  * If you wish to create a Rect you must use this method. In case the maximum
  * amount of rects has been reached it will return nullptr. Otherwise it will
  *return a pointer to a rect.
  *
  * @return Rect* returns the rect created or nullptr if the maximum of rects 
  *has been reached
  */
  static Rect* Rect::CreateRect();
  /** @Checks if a point collides with the rect
  *
  * Checks if the point passed by reference collides with the rect.
  *
  * @return bool returns true if the point collides and false if not.
  */
  bool checkCollision(sf::Vector2f& position);
  
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