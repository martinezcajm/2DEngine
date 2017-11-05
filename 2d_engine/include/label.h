#ifndef __LABEL_H__
#define __LABEL_H__ 1

#include "drawable_entity.h"

class Label : public DrawableEntity{
 public:
  void init(uint8_t r, uint8_t g, uint8_t b, uint8_t a, 
            float px, float py,
            float rotation, float scalex, float scaley,
            sf::String text, const sf::Font &font);
  /** @Draws the graphic entity Label
  *
  * Draws the label using SFML to the window passed by reference 
  *
  * @return void
  * @param window SFML RenderWindow passed by reference
  */
  void draw(sf::RenderWindow &window);
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
  static Label* Label::CreateLabel();
  
  static const uint8_t kMaxLabels = 50;
  uint8_t font_size_;
  sf::String text_;
  //Used to indicate if is normal, bold, italic or underlined
  sf::Text::Style style_;
  //Font of the text
  const sf::Font *font_;
 private:
  Label();
  Label(const Label& o){};
  static uint32_t total_labels_;
};

#endif