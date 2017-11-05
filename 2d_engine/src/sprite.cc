#include "sprite.h"

uint32_t Sprite::total_sprites_ = 1;

Sprite::Sprite() : DrawableEntity() {
  own_texture_ = nullptr;
  total_sprites_ ++;
}

Sprite::~Sprite(){
  if(origin_ != kSpriteHandler && own_texture_ != nullptr){
    delete own_texture_;
  }
}

void Sprite::init(float px, float py,
                float rotation, float scalex, float scaley,
                const sf::Texture &texture){
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  sprite_.setTexture(texture);
  origin_ = SpriteOrigin::kSpriteHandler;
}

void Sprite::init(float px, float py,
                float rotation, float scalex, float scaley,
                const sf::Texture& texture, uint8_t *error_ocurred){
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  /*if(embeddedImageData != nullptr){
         texture.loadFromMemory(embeddedImageData, sizeof(*embeddedImageData));
       }
  
  sprite_.setTexture(texture);*/
  origin_ = SpriteOrigin::kMemory;
}

uint8_t Sprite::init(float px, float py,
                float rotation, float scalex, float scaley,
                const std::string &file_path){
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  own_texture_ = new sf::Texture();
  if(own_texture_ == nullptr) return 1;
  own_texture_->loadFromFile(file_path);
  sprite_.setTexture(*own_texture_);
  origin_ = SpriteOrigin::kImage;
  return 0;
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