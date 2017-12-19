// sprite.h
// Jose Maria Martinez
// Header of the functions of the 2d entity sprite.
#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include "drawable_entity.h"

typedef enum SpriteOrigin
{
  kSpriteOrigin_Unknown,
  kSpriteOrigin_Memory,
  kSpriteOrigin_Image,
  kSpriteOrigin_Handler
} SpriteOrigin;

/** @brief Graphic entity Sprite
*
* Class used to represent a sprite. 
*
*/
class Sprite : public DrawableEntity{
 public:
  /** @brief Deletes a sprite
  *
  * In case the sprite stored it's own texture in the hip it needs to free it.
  */
  virtual ~Sprite();
  /** @brief Initializes the sprite using a texture
  *
  * Initializes the position and transformations of a sprite using an 
  * sf::Texture as texture.
  *
  * @return void
  * @param px position x of the sprite
  * @param py position y of the sprite
  * @param rotation value of rotation of the sprite in degrees
  * @param scalex x scale value of the sprite
  * @param scaley y scale value of the sprite
  * @param texture that will use the sprite
  * @param file_path image that will be used for the texture
  */
  void init(const float px, const float py,
            const float rotation, const float scalex, const float scaley,
            const sf::Texture &texture, const std::string &file_path);
  /** @brief Initializes the sprite using a buffer from memory
  *
  * Initializes an Sprite with its own texture that will be stored in memory.
  * In case the allocation of the texture fails it will return a 0. If all 
  * went well 1
  *
  * @return void
  * @param px position x of the sprite
  * @param py position y of the sprite
  * @param rotation value of rotation of the sprite in degrees
  * @param scalex x scale value of the sprite
  * @param scaley y scale value of the sprite
  * @param texture referency of the texture we wish to do the copy
  * @param error_ocurred indicates if there was an error in the execution
  * @param file_path image that will be used for the texture
  */
  void init(const float px, const float py,
            const float rotation, const float scalex, const float scaley,
            const sf::Texture& texture, uint8_t &error_ocurred,
            const std::string &file_path);
  /** @brief Initializes the sprite using an image file
  *
  * Initializes an Sprite with its own texture through an image file.
  * In case the allocation of the texture fails it will return a 0. If all 
  * went well 1
  *
  * @return uint8_t indicates if there was an error in the execution error->1
  *  ok->0
  * @param px position x of the sprite
  * @param py position y of the sprite
  * @param rotation value of rotation of the sprite in degrees
  * @param scalex x scale value of the sprite
  * @param scaley y scale value of the sprite
  * @param file_path image that will be used for the texture
  */
  uint8_t init(const float px, const float py,
               const float rotation, const float scalex, const float scaley,
               const std::string &file_path);
  /** @brief Draws the graphic entity Sprite
  *
  * Draws the sprite using SFML to the window passed by reference 
  *
  * @return void
  * @param window SFML RenderWindow passed by reference
  */
  virtual void draw(sf::RenderWindow &window) override;
  /** @brief Factory that creates sprites
  *
  * Checks that the number of sprites didn't pass the maxim amount established
  * If you wish to create a Sprite you must use this method. In case the
  * maximum amount of sprites has been reached it will return nullptr. 
  * Otherwise it will return a pointer to a sprite.
  *
  * @return Sprite* returns the sprite created or nullptr if the maximum of
  * sprites has been reached
  */
  static Sprite* CreateSprite();
  /** @brief Resets the values of the sprite
  *
  * Sets the attributes of the sprite to a default value
  * to return it to a pool and being able to reuse it later.
  *
  * @return void
  */
  virtual void unuse() override;
  /** @brief Getter for origin
  * Returns the origin of the texture, it will vary depending on how the 
  * sprite was initiallized
  *
  * @return void
  */
  SpriteOrigin origin();
  /** @brief Updates the sprite in the loop
  *
  * Implementation of the update interface
  *
  * @return void
  */
  virtual void update() override;
  /** @brief gets the boundaries of the rect entity
  *
  * Implementation of the getBoundaries interface. Gets the boundaries of the
  * Rect as an sf::FloatRect taking into account it's transformations.
  *
  * @return sf::FloatRect boundaries of the rect.
  */
  sf::FloatRect getBoundaries() override;

  static const uint8_t kMaxSprites = 50;
  sf::Sprite sprite_;
  std::string texture_dir_;

 protected:
  static uint32_t total_sprites_;
  /** @brief Sprite constructor
  *
  * Sprite constructor used by the factory to create sprite
  *
  * @return *Sprite
  */
  Sprite();
  /** @brief Sprite copy constructor
  *
  * Sprite copy constructor without anything to disable it.
  *
  * @return *Sprite
  */
  Sprite(const Sprite& o){};
  //A texture owned only by this sprite, it will be freed by the sprite once
  //it's life ends (not necessarily destruction)
  sf::Texture *own_texture_;
  /** @brief releases the texture of the sprite
  *
  * Releases the texture of the sprite in case it's origin allocated memory.
  *
  * @return void
  */
  void release();
 private:
  SpriteOrigin origin_;
  
};

#endif
