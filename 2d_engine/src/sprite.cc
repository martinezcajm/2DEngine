#include "sprite.h"

uint32_t Sprite::total_sprites_ = 1;

Sprite::Sprite() : DrawableEntity() {
  own_texture_ = nullptr;
  origin_ = SpriteOrigin::kUnknown;
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
  sf::FloatRect boundaries = sprite_.getLocalBounds();
  sf::Vector2f rotation_origin = {(boundaries.width/2)*scale_.x,
                                  (boundaries.height/2)*scale_.y};
  DrawableEntity::draw(window, sprite_, rotation_origin);
}

Sprite* Sprite::CreateSprite(){
  if(Sprite::total_sprites_ < kMaxSprites){
    Sprite* p_sprite = new Sprite();
    return p_sprite;
  }else{
    return nullptr;
  }
}

bool Sprite::checkCollision(sf::Vector2f& position){

  sf::FloatRect boundaries = sprite_.getLocalBounds();
  sf::Vector2f rotation_origin = {(boundaries.width/2)*scale_.x,
                                  (boundaries.height/2)*scale_.y};
  sf::Transform t;
  t.translate(position_);
  t.rotate(rotation_, rotation_origin);
  t.scale(scale_);
  
  //We apply the transformations we have done to our boundaries
  boundaries = t.transformRect(boundaries);

  return DrawableEntity::checkCollision(position, boundaries);
}

void Sprite::unuse(){
  if(origin_ != kSpriteHandler && own_texture_ != nullptr){
    delete own_texture_;
    own_texture_ = nullptr;
  }
  //sprite_ = Sprite();
  origin_ = SpriteOrigin::kUnknown;
  DrawableEntity::unuse();
}