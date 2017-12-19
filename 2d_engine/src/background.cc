// background.cc
// Jose Maria Martinez
// Implementation of the background graphical entity. Has auto scroll 
//functionalities and is a child of sprite.
//Comments for the functions can be found at the header
#include "background.h"

Background::Background() : Sprite(){
  speed_.x = 0;
  speed_.y = 0;
  type_ = kBackground;
}

Background::~Background(){ }

uint8_t Background::init(const std::string &file_path,
                         const uint32_t width, const uint32_t height){
  uint8_t error = 0;
  error = Sprite::init(0,0,   //position
                       0,1,1, //transforms r, sx, sy
                       file_path);
  if(error) return error;
  background_position_.x = 0;
  background_position_.y = 0;
  dimensions_.x = width;
  dimensions_.y = height;
  scrolls_vertically_ = 0;
  scrolls_horizontally_ = 0;
  own_texture_->setSmooth(false);
  own_texture_->setRepeated(true);
  sprite_.setTexture(*own_texture_);
  sprite_.setPosition(position_.x, position_.y);
  sprite_.setTextureRect(sf::IntRect(background_position_,dimensions_));
  return 0;
}

void Background::draw(sf::RenderWindow &window){
  if(active_){
    window.draw(sprite_);
  }
}

Background* Background::CreateBackground(){
  if(Sprite::total_sprites_ < kMaxSprites){
    Background* p_background = new Background();
    return p_background;
  }else{
    return nullptr;
  }
}

void Background::update(){
  if(scrolls_vertically_){
    if (background_position_.y < dimensions_.y){
      background_position_.y += speed_.y;
    }else{
      background_position_.y = 0;
    }
  }
  if(scrolls_horizontally_){
    if (background_position_.x < dimensions_.x){
      background_position_.x += speed_.x;
    }else{
      background_position_.x = 0;
    }
  }
  sprite_.setTextureRect(sf::IntRect(background_position_,dimensions_));
}

void Background::unuse(){
  scrolls_horizontally_ = 0;
  scrolls_vertically_ = 0;
  speed_.x = 0;
  speed_.y = 0;
  background_position_.x = 0;
  background_position_.y = 0;
  dimensions_.x = 0;
  dimensions_.y = 0;
  Sprite::unuse();
}