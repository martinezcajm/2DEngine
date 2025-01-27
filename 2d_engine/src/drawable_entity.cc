// drawable_entity.cc
// Jose Maria Martinez
// Implementation of the drawable entity. Abstract interface for the graphical
// 2D entities
//Comments for the functions can be found at the header

#include "drawable_entity.h"

DrawableEntity::DrawableEntity() : Entity() {
  position_.x = 0;
  position_.y = 0;
  color_.r = 0;
  color_.g = 0;
  color_.b = 0;
  color_.a = 0;
  rotation_ = 0.0f;
  z_order_ = 0;
  scale_.x = 1;
  scale_.y = 1;
}

DrawableEntity::~DrawableEntity(){ }

void DrawableEntity::init(const uint8_t r, const uint8_t g, 
                          const uint8_t b ,const uint8_t a,
                          const float px, const float py,
                          const float rotation,
                          const float scalex, const float scaley){
  Entity::init();
  color_.r = r;
  color_.g = g;
  color_.b = b;
  color_.a = a;
  position_.x = px;
  position_.y = py;
  rotation_ = rotation;
  scale_.x = scalex;
  scale_.y = scaley;
}

void DrawableEntity::move(const float px, const float py){
   position_.x += px;
   position_.y += py;
}

void DrawableEntity::drawWithTransform(sf::RenderWindow &window,
                                       const sf::Drawable &entity,
                                       const sf::Vector2f &rotation_origin){
  if(active_){
    sf::Transform t;
    t.translate(position_);
    //We indicate the rotation with the origin point from which it will rotate.
    t.rotate(rotation_, rotation_origin);
    t.scale(scale_);
    window.draw(entity, t);
  }
}

bool DrawableEntity::checkCollision(const sf::Vector2f &position){
  return getBoundaries().contains(position);
}

bool DrawableEntity::checkCollision(DrawableEntity &entity){
  return getBoundaries().intersects(entity.getBoundaries());
}

void DrawableEntity::unuse(){
  z_order_ = 1;
  rotation_ = 0;
  position_.x = 0;
  position_.y = 0;
  scale_.x = 0;
  scale_.y = 0;
  color_.r = 0;
  color_.g = 0;
  color_.b = 0;
  color_.a = 0;
  Entity::unuse();
}