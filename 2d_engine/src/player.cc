//Comments can be found at the header
#include "player.h"

Player::Player(){}
Player* Player::CreatePlayer(){  
  if(Sprite::total_sprites_ < kMaxSprites){
    Player* p_player = new Player();
    return p_player;
  }else{
    return nullptr;
  }
}

uint8_t Player::init(const float px, const float py, 
  const float scalex, const float scaley, const sf::Texture &texture,
  const uint8_t speed_x, const uint8_t speed_y){
  
  uint8_t error = 0;
  speed_x_ = speed_x;
  speed_y_ = speed_y;

  Sprite::init(px, py, 0.0f, scalex, scaley, texture, error);
  return error; 
}

void Player::update(){


}