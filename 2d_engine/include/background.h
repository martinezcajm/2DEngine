#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__ 1

#include "sprite.h"

class Background : public Sprite{
 public:
  /** @Initializes the sprite using a texture
  *
  * Initializes the position and transformations of a sprite using an 
  * sf::Texture as texture.
  *
  * @return uint8_t indicates if there was an error in the execution error->1
  *  ok->0
  * @param px position x of the sprite
  * @param py position y of the sprite
  * @param rotation value of rotation of the sprite in degrees
  * @param scalex x scale value of the sprite
  * @param scaley y scale value of the sprite
  * @param texture that will use the sprite
  */
  uint8_t init(const std::string &file_path, uint32_t width, uint32_t height);
  /** @Updates the background position
  *
  * Updates the position of the background in the x,y axis if they are 
  *active
  *
  * @return void
  */
  void update();
  /** @Draws the graphic entity Background
  *
  * Draws the background using SFML to the window passed by reference, note
  * that the background doesn't use the transformationso of it's parent,
  * you can set them bou they won't have any effect over the background. 
  *
  * @return void
  * @param window SFML RenderWindow passed by reference
  */
  void draw(sf::RenderWindow &window);
  /** @Factory that creates backgrounds
  *
  * Checks that the number of sprites didn't pass the maxim amount established
  * If you wish to create a Background you must use this method. In case the
  * maximum amount of sprites has been reached it will return nullptr. 
  * Otherwise it will return a pointer to a background. Note that it 
  * specifically uses the number of sprites as the background is by logic an
  * sprite with movement.
  *
  * @return Background* returns the background created or nullptr if the 
  * maximum of sprites has been reached
  */
  static Background* Background::CreateBackground();

  uint8_t scrolls_horizontally_;
  uint8_t scrolls_vertically_;
  sf::Vector2i speed_;
  sf::Vector2i dimensions_;
  //used to move the background, it indicate from wich x and y is being
  //showed the texture, it's not the position of the background!
  sf::Vector2i background_position_;

 private:
  Background();
  Background(const Background& o){};

};

#endif