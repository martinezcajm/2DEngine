#ifndef __LABEL_H__
#define __LABEL_H__ 1

#include "drawable_entity.h"

/** @Graphic entity Label
*
* Class used to represent text.
*
*/
class Label : public DrawableEntity{
 public:
  /** @Destroys the label
  *
  * Destructor of the label
  *
  * @return void
  */
  ~Label();
  /** @Initializes the Label
  *
  * Initializes a label
  *
  * @return void
  * @param r color red component of the label we want to create
  * @param g color blue component of the label we want to create 
  * @param b color green component of the label we want to create
  * @param a alpha channel of the color of the label we want to create
  * @param px x position in the window
  * @param py y position in the window
  * @param rotation rotation in degrees
  * @param scalex scale quantity at x axis
  * @param scaley scale quantity at y axis
  * @param text text that will contain the label
  * @param font font of the text
  */
  void init(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a,
            const float px, const float py,
            const float rotation, const float scalex, const float scaley,
            const char* text, const sf::Font &font);
  /** @Draws the graphic entity Label
  *
  * Draws the label using SFML to the window passed by reference 
  *
  * @return void
  * @param window SFML RenderWindow passed by reference
  */
  void draw(sf::RenderWindow &window);
  /** @Setter for text value
  *
  * Changes  the text value of the label
  *
  * @return void
  * @param &text reference to the new string we wish to show within the label
  */
  void set_font(const sf::Font  &font);
  /** @Setter for font_size value
  *
  * Changes the font size of the label
  *
  * @return void
  * @param &font_size reference to the new font size of our label
  */
  void set_font_size(const int32_t &font_size);
  /** @Factory that creates labels
  *
  * Checks that the number of labels didn't pass the maxim amount established
  * If you wish to create a Label you must use this method. In case the maximum
  * amount of labels has been reached it will return nullptr. Otherwise it will
  *return a pointer to a label.
  *
  * @return Label* returns the label created or nullptr if the maximum of
  * labels has been reached
  */
  //static Label* Label::CreateLabel();
  static Label* CreateLabel();
  /** @Checks if a point collides with the label
  *
  * Checks if the point passed by reference collides with the label.
  *
  * @return bool returns true if the point collides and false if not.
  */
  bool checkCollision(const sf::Vector2f& position);
  /** @Resets the values of the label
  *
  * Sets the attributes of the label to a default value
  * to return it to a pool and being able to reuse it later.
  *
  * @return void
  */
  void unuse();
  
  static const uint8_t kMaxLabels = 50;
  static const uint8_t kTextMaxSize = 50;
  int32_t font_size_;
  char text_[kTextMaxSize];
  //Used to indicate if is normal, bold, italic or underlined
  sf::Text::Style style_;
  //Font of the text
  const sf::Font *font_;
 private:
  /** @Label constructor
  *
  * Label constructor used by the factory to create labels
  *
  * @return *Label
  */
  Label();
  /** @Label copy constructor
  *
  * Label copy constructor without anything to disable it.
  *
  * @return *Label
  */
  Label(const Label& o){};
  static uint32_t total_labels_;
};

#endif
