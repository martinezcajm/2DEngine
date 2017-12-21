// Author: Sebastián Adrover Pedrosa
#ifndef __BALL_H__
#define __BALL_H__ 1

#include "sprite.h"
#include "game_manager.h"

/** @brief Graphic entity Ball
*
* Class used to represent a ball. 
*
*/
class Ball : public Sprite{
 public:
  /** @brief Deletes a ball
  *
  * In case the ball stored it's own texture in the hip it needs to free it.
  */
  virtual ~Ball() {};
  /** @brief Initializes the ball using a texture
  *
  * Initializes the position and transformations of a ball using an 
  * sf::Texture as texture.
  *
  * @return void
  * @param px position x of the ball
  * @param py position y of the ball
  * @param scalex x scale value of the ball
  * @param scaley y scale value of the ball
  * @param speed_x speed of the ball in the x-axis
  * @param speed_y speed of the ball in the y-axis
  * @param texture that will use the ball
  * @param file_path image that will be used for the texture
  */
  void init(const float px, const float py, 
            const float scalex, const float scaley, 
            const int32_t speed_x, const int32_t speed_y,
            const sf::Texture &texture, const std::string &texture_path);
            
  /** @brief Initializes the ball using a buffer from memory for the texture
  *
  * Initializes the position and transformations of a ball using an 
  * sf::Texture as texture from memory.
  *
  * @return void
  * @param px position x of the ball
  * @param py position y of the ball
  * @param scalex x scale value of the ball
  * @param scaley y scale value of the ball
  * @param speed_x speed of the ball in the x-axis
  * @param speed_y speed of the ball in the y-axis
  * @param texture that will use the ball
  * @param error_ocurred indicates if there was an error in the execution
  * @param file_path image that will be used for the texture
  */
  void init(const float px, const float py, 
            const float scalex, const float scaley, 
            const int32_t speed_x, const int32_t speed_y,
            const sf::Texture &texture, uint8_t &error_ocurred, 
            const std::string &texture_path);
            
  /** @brief Initializes the ball using an image file for the texture
  *
  * Initializes the position and transformations of a ball using an 
  * file as texture.
  *
  * @return uint8_t indicates if there was an error in the execution error->1
  *  ok->0
  * @param px position x of the ball
  * @param py position y of the ball
  * @param scalex x scale value of the ball
  * @param scaley y scale value of the ball
  * @param speed_x speed of the ball in the x-axis
  * @param speed_y speed of the ball in the y-axis
  * @param file_path image that will be used for the texture
  */
  uint8_t init(const float px, const float py, 
               const float scalex, const float scaley, 
               const int32_t speed_x, const int32_t speed_y,
               const std::string &file_path);
  
  /** @Factory that creates balls
  *
  * Checks that the number of balls didn't pass the maxim amount established
  * If you wish to create a Ball you must use this method. In case the
  * maximum amount of balls has been reached it will return nullptr. 
  * Otherwise it will return a pointer to a ball.
  *
  * @return Ball* returns the ball created or nullptr if the maximum of
  * balls has been reached
  */
  static Ball* CreateBall();
  
  
  /** @brief Updates the ball in the loop
  *
  * Implementation of the update interface
  *
  * @return void
  */
  virtual void update() override;
  
  sf::Vector2i speed_;
  GameManager& GM = GameManager::instance();
 protected:
  /** @brief Ball constructor
  *
  * Ball constructor used by the factory to create ball
  *
  * @return *Ball
  */
  Ball();
  /** @brief Ball copy constructor
  *
  * Ball copy constructor without anything to disable it.
  *
  * @return *Ball
  */
  Ball(const Ball& o){};
 private:
  
};

#endif
