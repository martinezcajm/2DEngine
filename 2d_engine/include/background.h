// background.h
// Jose Maria Martinez
// Header of the functions of the 2d entity background.
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__ 1

#include "sprite.h"

/** @brief Graphic entity Background.
*
* Class used to represent backgrounds. Used to stablish continuous movement 
* to a sprite.
*
*/
class Background : public Sprite{
 public:
  /** @brief Destroys the Background
  *
  * Destructor of the background
  *
  * @return void
  */
  virtual ~Background();
  /** @brief Initializes the backgorund using a texture
  *
  * Initializes the width height and path of a background
  *
  * @return uint8_t indicates if there was an error in the execution error->1
  *  ok->0
  * @param width width the background will be initialized to
  * @param height height the background will be initialized to
  * @param file_path image that will be used for the texture
  */
  uint8_t init(const std::string &file_path, const uint32_t width, 
               const uint32_t height);
  /** @brief Updates the background position
  *
  * Updates the position of the background in the x,y axis if they are 
  * active, implementation of the update interface
  *
  * @return void
  */
  void update() override;
  /** @brief Draws the graphic entity Background
  *
  * Draws the background using SFML to the window passed by reference, note
  * that the background doesn't use the transformationso of it's parent,
  * you can set them bou they won't have any effect over the background. 
  *
  * @return void
  * @param window SFML RenderWindow passed by reference
  */
  void draw(sf::RenderWindow &window) override;
  /** @brief Factory that creates backgrounds
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
  static Background* CreateBackground();
  /** @brief Resets the values of the background
  *
  * Sets the attributes of the background to a default value
  * to return it to a pool and being able to reuse it later.
  *
  * @return void
  */
  void unuse() override;

  uint8_t scrolls_horizontally_;
  uint8_t scrolls_vertically_;
  sf::Vector2i speed_;
  sf::Vector2i dimensions_;
  //used to move the background, it indicate from wich x and y is being
  //showed the texture, it's not the position of the background!
  sf::Vector2i background_position_;

 private:
  /** @brief Background constructor
  *
  * Background constructor used by the factory to create backgrounds
  *
  * @return *Background
  */
  Background();
  /** @brief Background copy constructor
  *
  * Background copy constructor without anything to disable it.
  *
  * @return *Background
  */
  Background(const Background& o){};

};

#endif
