// Author: Sebastián Adrover Pedrosa
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
  const int32_t speed_x, const int32_t speed_y,
  const sf::Texture &texture, const std::string &texture_path){
  
  speed_.x = speed_x;
  speed_.y = speed_y;  
  Sprite::init(px, py, 0.0f, scalex, scaley, texture, texture_path);
}
  
void Ball::init(const float px, const float py, 
  const float scalex, const float scaley, 
  const int32_t speed_x, const int32_t speed_y,
  const sf::Texture &texture, uint8_t &error_ocurred, 
  const std::string &texture_path){

  speed_.x = speed_x;
  speed_.y = speed_y;
  Sprite::init(px, py, 0.0f, scalex, scaley, texture, 
               error_ocurred, texture_path);
}
  
uint8_t Ball::init(const float px, const float py, 
     const float scalex, const float scaley, 
     const int32_t speed_x, const int32_t speed_y,
     const std::string &file_path){

  speed_.x = speed_x;
  speed_.y = speed_y;
  return Sprite::init(px, py, 0.0f, scalex, scaley, file_path);  
}

void Ball::update(){  
  if(position_.y > 750){
    GM.lives_ -= 1;
    GM.is_ball_in_movement_ = 0;
    position_.x = 312;
    position_.y = 705;
    speed_.x = 1;
    speed_.y = 3;

    if(GM.lives_ == 0){
      GM.game_over_ = 1;
    }
  }

  if(GM.score_ > GM.highest_score_){
    GM.highest_score_ = GM.score_;
  }
  if(active_){
    position_.x += speed_.x;
    position_.y += speed_.y;
  }
}