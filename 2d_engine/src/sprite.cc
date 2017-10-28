#include "sprite.h"

uint32_t Sprite::total_sprites_ = 1;

Sprite::Sprite() : DrawableEntity() {

  total_sprites_ ++;
}

void Sprite::init(float px, float py,
                float rotation, float scalex, float scaley){
  DrawableEntity::init(255,255,255,255, px,py, rotation, scalex,scaley);
  texture_.loadFromFile("../data/enemy.png");
}

//TODO create the Sprite out of draw
void Sprite::draw(sf::RenderWindow &window){
  sf::Sprite sprite;
  sprite.setTexture(texture_);
  sprite.setColor(color_);
  sprite.setPosition(position_);
  window.draw(sprite);
}

Sprite* Sprite::CreateSprite(){
  if(Sprite::total_sprites_ < kMaxSprites){
    Sprite* p_sprite = new Sprite();
    return p_sprite;
  }else{
    return nullptr;
  }
}

//TODO implement destructor that will free the Text