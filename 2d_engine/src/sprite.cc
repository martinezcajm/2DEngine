#include "sprite.h"

uint32_t Sprite::total_sprites_ = 1;

Sprite::Sprite() : DrawableEntity() {

  total_sprites_ ++;
}

void Sprite::init(float px, float py,
                float rotation, float scalex, float scaley,
                const sf::Texture &texture){
  DrawableEntity::init(255,255,255,255, px,py, rotation, scalex,scaley);
  sprite_.setTexture(texture);
}

void Sprite::draw(sf::RenderWindow &window){
  sprite_.setColor(color_);
  sprite_.setPosition(position_);
  sprite_.scale(scale_.x, scale_.y);
  sprite_.rotate(rotation_);
  window.draw(sprite_);
}

Sprite* Sprite::CreateSprite(){
  if(Sprite::total_sprites_ < kMaxSprites){
    Sprite* p_sprite = new Sprite();
    return p_sprite;
  }else{
    return nullptr;
  }
}