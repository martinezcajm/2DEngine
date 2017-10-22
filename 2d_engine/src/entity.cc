#include "entity.h"

Entity::Entity() {
  tag_ = 0;
  active_ = 0;
}

void Entity::init(uint32_t tag){
  tag_ = tag;
  active_ = 1;
}

void Entity::init(){
  tag_ = 0;
  active_ = 1;
}