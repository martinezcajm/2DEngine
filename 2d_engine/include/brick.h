#ifndef __BRICK_H__
#define __BRICK_H__ 1

#include "rect.h"
#include "game_manager.h"

/** 
*
* Class used to represent Bricks.
*
*/
class Brick : public Rect{
 public:
  /** @Destroys the Brick
  *
  * Destructor of the brick
  *
  * @return void
  */
  virtual ~Brick(){};
  
  /** @Factory that creates brick
  *
  * Checks that the number of bricks didn't pass the maxim amount established
  * If you wish to create a Brick you must use this method. In case the maximum
  * amount of bricks has been reached it will return nullptr. Otherwise it will
  *return a pointer to a brick.
  *
  * @return Brick* returns the brick created or nullptr if the maximum of bricks 
  *has been reached
  */
  static Brick* CreateBrick();

  /** @Initializes the Brick
  *
  * Initializes the different values of a brick
  *
  * @return void
  * @param width width dimension of the brick
  * @param height height dimension of the brick
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
  * @param lives lives of the brick
  */
  void init(float width, float height, uint8_t sc_r,
            uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
            uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py,
            float rotation, float scalex, float scaley, uint8_t lives);

  /** @brief Updates the brick in the loop
  *
  * Implementation of the update interface
  *
  * @return void
  */
  void update() override;
  
  int lives_;
  int score_;
  GameManager& GM = GameManager::instance();
 private:
  /** @Brick constructor
  *
  * Brick constructor used by the factory to create bricks
  *
  * @return *Brick
  */
  Brick();
  /** @Brick copy constructor
  *
  * Brick copy constructor without anything to disable it.
  *
  * @return *Brick
  */
  Brick(const Brick& o){};
};

#endif
