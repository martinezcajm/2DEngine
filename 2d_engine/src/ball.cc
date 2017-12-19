//Comments can be found at the header
#include "ball.h"

Ball::Ball() : Sprite(){
  type_ = kBall;
}

Ball* Ball::CreateBall(){  
  if(Sprite::total_sprites_ < kMaxSprites){
    Ball* p_ball = new Ball();
    return p_ball;
  }else{
    return nullptr;
  }
}

void Ball::init(const float px, const float py, 
  const float scalex, const float scaley, 
  const uint8_t speed_x, const uint8_t speed_y,
  const sf::Texture &texture, const std::string &texture_path){
  
  speed_x_ = speed_x;
  speed_y_ = speed_y;  
  Sprite::init(px, py, 0.0f, scalex, scaley, texture, texture_path);
}
  
void Ball::init(const float px, const float py, 
  const float scalex, const float scaley, 
  const uint8_t speed_x, const uint8_t speed_y,
  const sf::Texture &texture, uint8_t &error_ocurred, 
  const std::string &texture_path){

  speed_x_ = speed_x;
  speed_y_ = speed_y;
  Sprite::init(px, py, 0.0f, scalex, scaley, texture, 
               error_ocurred, texture_path);
}
  
uint8_t Ball::init(const float px, const float py, 
     const float scalex, const float scaley, 
     const uint8_t speed_x, const uint8_t speed_y,
     const std::string &file_path){

  speed_x_ = speed_x;
  speed_y_ = speed_y;
  return Sprite::init(px, py, 0.0f, scalex, scaley, file_path);  
}

void Ball::update(){

}