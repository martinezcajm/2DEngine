//Comments can be found at the header
#include "player.h"

Player::Player() : Sprite(){
  type_ = kPlayer;
}
Player* Player::CreatePlayer(){  
  if(Sprite::total_sprites_ < kMaxSprites){
    Player* p_player = new Player();
    return p_player;
  }else{
    return nullptr;
  }
}

void Player::init(const float px, const float py, 
  const float scalex, const float scaley,
  const int32_t speed_x, const int32_t speed_y,
  const sf::Texture &texture, const std::string &texture_path){
  
  speed_.x = speed_x;
  speed_.y = speed_y;

  Sprite::init(px, py, 0.0f, scalex, scaley, texture, texture_path);
}

void Player::init(const float px, const float py, 
  const float scalex, const float scaley,
  const int32_t speed_x, const int32_t speed_y,
  const sf::Texture &texture, uint8_t &error_ocurred,
  const std::string &texture_path){

  speed_.x = speed_x;
  speed_.y = speed_y;

  Sprite::init(px, py, 0.0f, scalex, scaley, texture, 
               error_ocurred, texture_path);
}

uint8_t Player::init(const float px, const float py, 
  const float scalex, const float scaley,
  const int32_t speed_x, const int32_t speed_y,
  const std::string &file_path){

  speed_.x = speed_x;
  speed_.y = speed_y;

  return Sprite::init(px, py, 0.0f, scalex, scaley, file_path);
}

void Player::update(){

}