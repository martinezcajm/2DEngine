// Author: Sebastián Adrover Pedrosa
#ifndef __PLAYER_H__
#define __PLAYER_H__ 1

#include "sprite.h"
#include "game_manager.h"

/** @brief Graphic entity Player
*
* Class used to represent a player. 
*
*/
class Player : public Sprite{
 public:
  /** @brief Deletes a player
  *
  * In case the player stored it's own texture in the hip it needs to free it.
  */
  virtual ~Player() {};
  /** @brief Initializes the player using a texture
  *
  * Initializes the position and transformations of a player using an 
  * sf::Texture as texture.
  *
  * @return void
  * @param px position x of the player
  * @param py position y of the player
  * @param scalex x scale value of the player
  * @param scaley y scale value of the player
  * @param speed_x speed of the player in the x-axis
  * @param speed_y speed of the player in the y-axis
  * @param texture that will use the player
  * @param file_path image that will be used for the texture
  */
  void init(const float px, const float py, 
            const float scalex, const float scaley,
            const int32_t speed_x, const int32_t speed_y,
            const sf::Texture &texture, const std::string &texture_path);
  
  /** @brief Initializes the player using a buffer from memory for the texture
  *
  * Initializes the position and transformations of a player using an 
  * sf::Texture as texture from memory.
  *
  * @return void
  * @param px position x of the player
  * @param py position y of the player
  * @param scalex x scale value of the player
  * @param scaley y scale value of the player
  * @param speed_x speed of the player in the x-axis
  * @param speed_y speed of the player in the y-axis
  * @param texture that will use the player
  * @param error_ocurred indicates if there was an error in the execution
  * @param file_path image that will be used for the texture
  */
  void init(const float px, const float py, 
            const float scalex, const float scaley,
            const int32_t speed_x, const int32_t speed_y,
            const sf::Texture &texture, uint8_t &error_ocurred,
            const std::string &texture_path);
    
  
  /** @brief Initializes the player using an image file for the texture
  *
  * Initializes the position and transformations of a player using an 
  * file as texture.
  *
  * @return uint8_t indicates if there was an error in the execution error->1
  *  ok->0
  * @param px position x of the player
  * @param py position y of the player
  * @param scalex x scale value of the player
  * @param scaley y scale value of the player
  * @param speed_x speed of the player in the x-axis
  * @param speed_y speed of the player in the y-axis
  * @param file_path image that will be used for the texture
  */
  uint8_t init(const float px, const float py, 
               const float scalex, const float scaley,
               const int32_t speed_x, const int32_t speed_y,
               const std::string &file_path);


  /** @brief Factory that creates players
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
  
  sf::Vector2i speed_;
  GameManager& GM = GameManager::instance();
 protected:
  /** @brief Player constructor
  *
  * Player constructor used by the factory to create player
  *
  * @return *Player
  */
  Player();
  /** @brief Player copy constructor
  *
  * Player copy constructor without anything to disable it.
  *
  * @return *Player
  */
  Player(const Player& o){};
 private: 
};

#endif
