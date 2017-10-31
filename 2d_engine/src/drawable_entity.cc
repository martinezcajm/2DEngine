#include "drawable_entity.h"

DrawableEntity::DrawableEntity() : Entity() {
  position_.x = 0;
  position_.y = 0;
  color_.r = 0;
  color_.g = 0;
  color_.b = 0;
  color_.a = 0;
  rotation_ = 0.0f;
  scale_.x = 1;
  scale_.y = 1;
}

void DrawableEntity::init(uint8_t r,uint8_t g,uint8_t b,uint8_t a, 
                          float px, float py,
                          float rotation, float scalex, float scaley){
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

void DrawableEntity::move(float px, float py){
  position_.x += px;
  position_.y += py;
}

void DrawableEntity::draw(sf::RenderWindow &window, const sf::Drawable &entity,                        const sf::Vector2f &rotation_origin){
  sf::Transform t;
  t.translate(position_);
  //We indicate the rotation with the origin point from which it will rotate.
  t.rotate(rotation_, rotation_origin);
  t.scale(scale_);
  window.draw(entity, t);
}