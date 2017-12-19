//Comments can be found at the header
#include "ball.h"

Ball::Ball(){}
Ball* Ball::CreateBall(){  
  if(Sprite::total_sprites_ < kMaxSprites){
    Ball* p_ball = new Ball();
    return p_ball;
  }else{
    return nullptr;
  }
}

uint8_t Ball::init(const float px, const float py, 
  const float scalex, const float scaley, const sf::Texture &texture,
  const uint8_t speed_x, const uint8_t speed_y){
  
  uint8_t error = 0;

  Sprite::init( px, py, 0.0f, scalex, scaley, texture);
  if(error) return error;

  speed_x_ = speed_x;
  speed_y_ = speed_y;   
  
  return error;
}

void Ball::update(){

}