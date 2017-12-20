// entity.cc
// Jose Maria Martinez
// Implementation of entity. Abstract interface for the different entities
// that will have the engine
//Comments for the functions can be found at the header
#include "entity.h"

uint32_t Entity::total_ids_ = 1;

Entity::Entity() {
  tag_ = 0;
  selection_tag_ = 0;
  active_ = 0;
  id_ = total_ids_;
  total_ids_ ++;
}

/*Entity::~Entity(){ }*/

Entity::Entity(const Entity& o) {
  tag_ = o.tag_;
  active_ = o.active_;
  id_ = total_ids_;
  total_ids_ ++;
};

void Entity::init(const uint32_t tag){
  tag_ = tag;
  active_ = 1;
}

void Entity::init(){
  tag_ = 0;
  active_ = 1;
}

uint32_t Entity::id(){
  return id_;
}

Entity::Type Entity::type(){
  return type_;
}

void Entity::unuse(){
  selection_tag_ = 0;
  tag_ = 0;
  active_ = 0;
}