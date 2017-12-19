// sprite.cc
// Jose Maria Martinez
// Implementation of sprite. Representation of a Rectangle in the engine.
//Comments for the functions can be found at the header
#include "sprite.h"

uint32_t Sprite::total_sprites_ = 1;

Sprite::Sprite() : DrawableEntity() {
  own_texture_ = nullptr;
  origin_ = SpriteOrigin::kSpriteOrigin_Unknown;
  total_sprites_ ++;
  texture_dir_ = "";
  type_ = kSprite;
}

Sprite::~Sprite(){
  release();
}

void Sprite::init(const float px, const float py,
                  const float rotation, const float scalex, const float scaley,
                  const sf::Texture &texture, const std::string &file_path){
  release();
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  sprite_.setTexture(texture, true);
  origin_ = SpriteOrigin::kSpriteOrigin_Handler;
  texture_dir_ = file_path;
}

void Sprite::init(const float px, const float py,
                  const float rotation, const float scalex, const float scaley,
                  const sf::Texture& texture, uint8_t &error_ocurred,
                  const std::string &file_path){
  release();
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  error_ocurred = 0;
  //We invoke the SFML copy constructor of texture
  own_texture_ = new sf::Texture(texture);
  if(own_texture_ == nullptr){
    error_ocurred = 1;
    return;
  } 
  sprite_.setTexture(*own_texture_, true);
  origin_ = SpriteOrigin::kSpriteOrigin_Memory;
  texture_dir_ = file_path;
}

uint8_t Sprite::init(const float px, const float py,
                     const float rotation, const float scalex, 
                     const float scaley,
                     const std::string &file_path){
  release();
  DrawableEntity::init(255,255,255,255, px, py, rotation, scalex, scaley);
  own_texture_ = new sf::Texture();
  if(own_texture_ == nullptr) return 1;
  own_texture_->loadFromFile(file_path);
  sprite_.setTexture(*own_texture_, true);
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

void Sprite::unuse(){
  texture_dir_ = "";
  release();
  DrawableEntity::unuse();
}

void Sprite::release(){
  if(origin_ != kSpriteOrigin_Unknown && origin_ != kSpriteOrigin_Handler &&
     own_texture_ != nullptr){
    delete own_texture_;
  }
  own_texture_ = nullptr;
  origin_ = SpriteOrigin::kSpriteOrigin_Unknown;
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