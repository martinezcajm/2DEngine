#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include "drawable_entity.h"

typedef enum SpriteOrigin
{
  kMemory,
  kImage,
  kSpriteHandler
} SpriteOrigin;

class Sprite : public DrawableEntity{
 public:
  /** @Deletes a sprite
  *
  * In case the sprite stored it's own texture in the hip it needs to free it.
  */
  ~Sprite();
  /** @Initializes the sprite using a texture
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
  */
  void init(float px, float py,
            float rotation, float scalex, float scaley,
            const sf::Texture &texture);
  /** @Initializes the sprite using a buffer from memory
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
  * @param uint8_t indicates if there was an error in the execution
  */
  void init(float px, float py,
            float rotation, float scalex, float scaley,
            const sf::Texture& texture, uint8_t *error_ocurred);
  /** @Initializes the sprite using an image file
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
  * @param image_file image that will be used for the texture
  */
  uint8_t Sprite::init(float px, float py,
                float rotation, float scalex, float scaley,
                const std::string &file_path);
  /** @Draws the graphic entity Sprite
  *
  * Draws the sprite using SFML to the window passed by reference 
  *
  * @return void
  * @param window SFML RenderWindow passed by reference
  */
  void draw(sf::RenderWindow &window);
  /** @Factory that creates sprites
  *
  * Checks that the number of sprites didn't pass the maxim amount established
  * If you wish to create a Sprite you must use this method. In case the
  * maximum amount of sprites has been reached it will return nullptr. 
  * Otherwise it will return a pointer to a sprite.
  *
  * @return Sprite* returns the sprite created or nullptr if the maximum of
  * sprites has been reached
  */
  static Sprite* Sprite::CreateSprite();
  
  static const uint8_t kMaxSprites = 50;
  sf::Sprite sprite_;
  /** @Checks if a point collides with the sprite
  *
  * Checks if the point passed by reference collides with the sprite.
  *
  * @return bool returns true if the point collides and false if not.
  */
  bool checkCollision(sf::Vector2f& position);

 protected:
  static uint32_t total_sprites_;
  Sprite();
  Sprite(const Sprite& o){};
  //A texture owned only by this sprite, it will be freed by the sprite ones
  //it's life ends (not necessarily destruction)
  sf::Texture *own_texture_;

 private:
  SpriteOrigin origin_;
  
};

#endif