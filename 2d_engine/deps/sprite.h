#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include "drawable_entity.h"

class Sprite : public DrawableEntity{
 public:
  void init(float px, float py,
            float rotation, float scalex, float scaley,
            const sf::Texture &texture);
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
};

#endif