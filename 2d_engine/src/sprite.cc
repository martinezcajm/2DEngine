//Comments can be found at the header
#include "sprite.h"

uint32_t Sprite::total_sprites_ = 1;

Sprite::Sprite() : DrawableEntity() {
  own_texture_ = nullptr;
  origin_ = SpriteOrigin::kSpriteOrigin_Unknown;
  total_sprites_ ++;
  texture_dir_ = "../data/fonts/arial.ttf";
}

Sprite::~Sprite(){
  if(origin_ != kSpriteOrigin_Handler && own_texture_ != nullptr){
    delete own_texture_;
  }
}

void Sprite::init(const float px, const float py,
                  const float rotation, const float scalex, const float scaley,
                  const sf::Texture &texture){
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  sprite_.setTexture(texture);
  origin_ = SpriteOrigin::kSpriteOrigin_Handler;
}

void Sprite::init(const float px, const float py,
                  const float rotation, const float scalex, const float scaley,
                  const sf::Texture& texture, uint8_t &error_ocurred){
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  error_ocurred = 0;
  //We invoke the SFML copy constructor of texture
  own_texture_ = new sf::Texture(texture);
  if(own_texture_ == nullptr){
    error_ocurred = 1;
    return;
  } 
  sprite_.setTexture(*own_texture_);
  origin_ = SpriteOrigin::kSpriteOrigin_Memory;
}

uint8_t Sprite::init(const float px, const float py,
                     const float rotation, const float scalex, 
                     const float scaley,
                     const std::string &file_path){
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  own_texture_ = new sf::Texture();
  if(own_texture_ == nullptr) return 1;
  own_texture_->loadFromFile(file_path);
  sprite_.setTexture(*own_texture_);
  origin_ = SpriteOrigin::kSpriteOrigin_Image;
  texture_dir_ = file_path;
  return 0;
}

void Sprite::draw(sf::RenderWindow &window){
  sprite_.setColor(color_);
  sf::FloatRect boundaries = sprite_.getLocalBounds();
  sf::Vector2f rotation_origin = {(boundaries.width/2)*scale_.x,
                                  (boundaries.height/2)*scale_.y};
  DrawableEntity::drawWithTransform(window, sprite_, rotation_origin);
}

Sprite* Sprite::CreateSprite(){
  if(Sprite::total_sprites_ < kMaxSprites){
    Sprite* p_sprite = new Sprite();
    return p_sprite;
  }else{
    return nullptr;
  }
}

//TODO externalizar accion release y usarlo en los init
void Sprite::unuse(){
  if(origin_ != kSpriteOrigin_Handler && own_texture_ != nullptr){
    delete own_texture_;
    own_texture_ = nullptr;
  }
  origin_ = SpriteOrigin::kSpriteOrigin_Unknown;
  DrawableEntity::unuse();
}

SpriteOrigin Sprite::origin(){
  return origin_;
}

void Sprite::update(){}

sf::FloatRect Sprite::getBoundaries(){
  sf::FloatRect boundaries = sprite_.getLocalBounds();
  sf::Vector2f rotation_origin = {(boundaries.width/2)*scale_.x,
                                  (boundaries.height/2)*scale_.y};
  sf::Transform t;
  t.translate(position_);
  t.rotate(rotation_, rotation_origin);
  t.scale(scale_);
  
  //We apply the transformations we have done to our boundaries
  return t.transformRect(boundaries);
}