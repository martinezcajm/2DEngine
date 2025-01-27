// label.cc
// Jose Maria Martinez
// Implementation of the label entity. Representation of a text in the engine.
// that will have the engine
//Comments for the functions can be found at the header

#include <string.h>
#include "label.h"

uint32_t Label::total_labels_ = 1;

Label::Label() : DrawableEntity() {
  text_[0] = ' ';
  font_size_ = 30;
  style_ = sf::Text::Regular;
  font_ = nullptr;
  total_labels_ ++;
  type_ = kLabel;
}

Label::~Label(){ }

void Label::init(const uint8_t r, const uint8_t g, const uint8_t b, 
                 const uint8_t a, 
                 const float px, const float py,
                 const float rotation, const float scalex, const float scaley,
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
  DrawableEntity::drawWithTransform(window, text, rotation_origin);
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


void Label::unuse(){
  font_size_ = 0;
  memset(&text_, '\0', kTextMaxSize);
  style_ = sf::Text::Regular;
  font_ = nullptr;
  DrawableEntity::unuse();
}

void Label::update(){
  if(tag_ == 14){
    sprintf_s(text_, sizeof(text_), "%d", GM.score_);
  }else if(tag_ == 15){
    sprintf_s(text_, sizeof(text_), "%d", GM.highest_score_);
  }else if(tag_ == 16){
    sprintf_s(text_, sizeof(text_), "%d", GM.lives_);
  }

}

sf::FloatRect Label::getBoundaries(){
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
  return t.transformRect(boundaries);
}