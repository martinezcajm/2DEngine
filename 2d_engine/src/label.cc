#include "label.h"

uint32_t Label::total_labels_ = 1;

Label::Label() : DrawableEntity() {
  text_ = "";
  font_size_ = 30;
  style_ = sf::Text::Regular;
  total_labels_ ++;
}

void Label::init(uint8_t r, uint8_t g, uint8_t b, uint8_t a, 
                float px, float py,
                float rotation, float scalex, float scaley,
                sf::String text){
  DrawableEntity::init(r,g,b,a, px,py, rotation, scalex,scaley);
  text_ = text;
}

//TODO create the Text and font out of draw
void Label::draw(sf::RenderWindow &window){
  sf::Font font;
  font.loadFromFile("../data/fonts/arial.ttf");
  sf::Text text(text_, font);
  text.setCharacterSize(font_size_);
  text.setStyle(style_);
  text.setFillColor(color_);
  text.setPosition(position_);
  window.draw(text);
}

Label* Label::CreateLabel(){
  if(Label::total_labels_ < kMaxLabels){
    Label* p_label = new Label();
    return p_label;
  }else{
    return nullptr;
  }
}

//TODO implement destructor that will free the Text