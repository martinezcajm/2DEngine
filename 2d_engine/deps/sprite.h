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
  * Initializes the position and transformations of a sprite using memory data
  *
  * @return void
  * @param px position x of the sprite
  * @param py position y of the sprite
  * @param rotation value of rotation of the sprite in degrees
  * @param scalex x scale value of the sprite
  * @param scaley y scale value of the sprite
  * @param embeddedImageData data of the image to be loaded as texture
  */
  void init(float px, float py,
            float rotation, float scalex, float scaley,
            const char *embeddedImageData);
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
  * maximum amount of labels has been reached it will return nullptr. 
  * Otherwise it will return a pointer to a sprite.
  *
  * @return Sprite* returns the sprite created or nullptr if the maximum of
  * sprites has been reached
  */
  static Sprite* Sprite::CreateSprite();
  
  static const uint8_t kMaxSprites = 50;
  sf::Sprite sprite_;

 private:
  Sprite();
  Sprite(const Sprite& o){};
  static uint32_t total_sprites_;
  SpriteOrigin origin_;
};

#endif