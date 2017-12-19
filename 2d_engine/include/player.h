#ifndef __PLAYER_H__
#define __PLAYER_H__ 1

#include "sprite.h"

/** @Graphic entity Player
*
* Class used to represent a player. 
*
*/
class Player : public Sprite{
 public:
  /** @Deletes a player
  *
  * In case the player stored it's own texture in the hip it needs to free it.
  */
  ~Player();
  /** @Initializes the player using a texture
  *
  * Initializes the position and transformations of a player using an 
  * sf::Texture as texture.
  *
  * @return uint8_t indicates if there was an error in the execution error->1
  *   ok->0
  * @param px position x of the player
  * @param py position y of the player
  * @param scalex x scale value of the player
  * @param scaley y scale value of the player
  * @param speed_x speed of the player in the x-axis
  * @param speed_y speed of the player in the y-axis
  * @param texture that will use the player
  * @param file_path image that will be used for the texture
  */
  uint8_t init(const float px, const float py, 
            const float scalex, const float scaley,
            const uint8_t speed_x, const uint8_t speed_y,
            const sf::Texture &texture, const std::string &texture_path);
  
  /** @Factory that creates players
  *
  * Checks that the number of players didn't pass the maxim amount established
  * If you wish to create a Player you must use this method. In case the
  * maximum amount of players has been reached it will return nullptr. 
  * Otherwise it will return a pointer to a player.
  *
  * @return Player* returns the player created or nullptr if the maximum of
  * players has been reached
  */
  static Player* CreatePlayer();
  
  
  /** @brief Updates the player in the loop
  *
  * Implementation of the update interface
  *
  * @return void
  */
  virtual void update() override;
  
  uint8_t speed_x_;
  uint8_t speed_y_;
 protected:
  /** @Player constructor
  *
  * Player constructor used by the factory to create player
  *
  * @return *Player
  */
  Player();
  /** @Player copy constructor
  *
  * Player copy constructor without anything to disable it.
  *
  * @return *Player
  */
  Player(const Player& o){};
 private:  
};

#endif
