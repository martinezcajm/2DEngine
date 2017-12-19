#ifndef __RECT_H__
#define __RECT_H__ 1

#include "drawable_entity.h"

/** @Graphic entity Label
*
* Class used to represent Rectangles.
*
*/
class Rect : public DrawableEntity{
 public:
  /** @Destroys the Rect
  *
  * Destructor of the rect
  *
  * @return void
  */
  virtual ~Rect();
  /** @Initializes the Rect
  *
  * Initializes the different values of a rect
  *
  * @return void
  * @param is_solid used to indicate if the rect has fill color
  * @param width width dimension of the rectangle
  * @param height height dimension of the rectangle
  * @param sc_r color red component of the inner color 
  * @param sc_g color blue component of the inner color 
  * @param sc_b color green component of the inner color 
  * @param sc_a alpha channel of the inner color
  * @param fc_r color red component of the fill color 
  * @param fc_g color blue component of the fill color 
  * @param fc_b color green component of the fill color 
  * @param fc_a alpha channel of the fill color 
  * @param px x position in the window
  * @param py y position in the window
  * @param rotation rotation in degrees
  * @param scalex scale quantity at x axis
  * @param scaley scale quantity at y axis
  */
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
  void draw(sf::RenderWindow &window) override;
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
  static Rect* CreateRect();
  /** @Resets the values of the rect
  *
  * Sets the attributes of the rect to a default value
  * to return it to a pool and being able to reuse it later.
  *
  * @return void
  */
  void unuse() override;
  /** @brief Updates the rect in the loop
  *
  * Implementation of the update interface
  *
  * @return void
  */
  void update() override;
  /** @brief gets the boundaries of the rect entity
  *
  * Implementation of the getBoundaries interface. Gets the boundaries of the
  * Rect as an sf::FloatRect taking into account it's transformations.
  *
  * @return sf::FloatRect boundaries of the rect.
  */
  sf::FloatRect getBoundaries() override;
  
  static const uint8_t kMaxRects = 50;
  uint8_t is_solid_;
  //Contains the width and height
  sf::Vector2f dimensions_;
  sf::Color rgba_fill_;
protected:
  /** @Rect constructor
  *
  * Rect constructor used by the factory to create rects
  *
  * @return *Rect
  */
  Rect();
  /** @Rect copy constructor
  *
  * Rect copy constructor without anything to disable it.
  *
  * @return *Rect
  */
  Rect(const Rect& o){};
  static uint32_t total_rects_;
};

#endif
