#include <string.h>
#include "label.h"

uint32_t Label::total_labels_ = 1;

Label::Label() : DrawableEntity() {
  text_[0] = ' ';
  font_size_ = 30;
  style_ = sf::Text::Regular;
  font_ = nullptr;
  total_labels_ ++;
}

void Label::init(uint8_t r, uint8_t g, uint8_t b, uint8_t a, 
                float px, float py,
                float rotation, float scalex, float scaley,
                const char* text, const sf::Font &font){
  DrawableEntity::init(r,g,b,a, px,py, rotation, scalex,scaley);
  if(text != nullptr){
    memcpy(&text_, text, kTextMaxSize);
  }
  font_ = &font;
}

void Label::draw(sf::RenderWindow &window){
  sf::Text text(text_, *font_);
  text.setCharacterSize(font_size_);
  text.setStyle(style_);
  text.setFillColor(color_);
  sf::FloatRect boundaries = text.getLocalBounds();
  sf::Vector2f rotation_origin = {(boundaries.width/2)*scale_.x,
                                  (boundaries.height/2)*scale_.y};
  DrawableEntity::draw(window, text, rotation_origin);
}

void Label::set_font(const sf::Font  &font){
  font_ = &font;
}

void Label::set_font_size(const int32_t &font_size){
  font_size_ = font_size;
}

Label* Label::CreateLabel(){
  if(Label::total_labels_ < kMaxLabels){
    Label* p_label = new Label();
    return p_label;
  }else{
    return nullptr;
  }
}

bool Label::checkCollision(sf::Vector2f& position){
  sf::Text text(text_, *font_);
  text.setCharacterSize(font_size_);
  text.setStyle(style_);
  
  sf::FloatRect boundaries = text.getLocalBounds();
  sf::Vector2f rotation_origin = {(boundaries.width/2)*scale_.x
                                  ,(boundaries.height/2)*scale_.y};
  sf::Transform t;
  t.translate(position_);
  t.rotate(rotation_, rotation_origin);
  t.scale(scale_);
  
  //We apply the transformations we have done to our boundaries
  boundaries = t.transformRect(boundaries);

  return DrawableEntity::checkCollision(position, boundaries);
}