#ifndef __WALL_H__
#define __WALL_H__ 1

#include "rect.h"

/** 
*
* Class used to represent Walls.
*
*/
class Wall : public Rect{
 public:
  /** @Destroys the Wall
  *
  * Destructor of the wall
  *
  * @return void
  */
  virtual ~Wall(){};
  
  /** @Factory that creates wall
  *
  * Checks that the number of walls didn't pass the maxim amount established
  * If you wish to create a Wall you must use this method. In case the maximum
  * amount of walls has been reached it will return nullptr. Otherwise it will
  *return a pointer to a wall.
  *
  * @return Wall* returns the wall created or nullptr if the maximum of walls 
  *has been reached
  */
  static Wall* CreateWall();

  /** @Initializes the Wall
  *
  * Initializes the different values of a wall
  *
  * @return void
  * @param width width dimension of the wall
  * @param height height dimension of the wall
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
  * @param scalex scale quantity at x axis
  * @param scaley scale quantity at y axis
  */
  void init(float width, float height, uint8_t sc_r,
            uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
            uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py,
            float scalex, float scaley);
 private:
  /** @Wall constructor
  *
  * Wall constructor used by the factory to create walls
  *
  * @return *Wall
  */
  Wall();
  /** @Wall copy constructor
  *
  * Wall copy constructor without anything to disable it.
  *
  * @return *Wall
  */
  Wall(const Wall& o){};
};

#endif
