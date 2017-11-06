#include "scene.h"
#include "game_manager.h"

Scene::Scene(){

}

void Scene::loadScene(){
  //TODO
}
void Scene::saveScene(){
  //TODO
}

void Scene::drawScene(){
  GameManager& GM = GameManager::instance();

  // Foreach Z-order we print the elements of that level
  for (std::set<uint32_t>::iterator it=z_order_levels.begin(); 
       it!=z_order_levels.end(); it--){
        
    // Print Backgrouds
    if (z_order_map_background_.find(*it) != z_order_map_background_.end()) {
      for (std::unordered_map<uint32_t, Background*>::iterator it2 =
          z_order_map_background_.at(*it).begin(); it2 
          != z_order_map_background_.at(*it).end();
          it2++) {

        it2->second->draw(*GM.window_->sfml_window_);
      }
    }

    // Print Rects
    if (z_order_map_rect_.find(*it) != z_order_map_rect_.end()) {
      for(std::unordered_map<uint32_t, Rect*>::iterator it2 = 
          z_order_map_rect_.at(*it).begin(); it2 != 
          z_order_map_rect_.at(*it).end(); it2++){
        
        it2->second->draw(*GM.window_->sfml_window_);
      }
    }

    // Print Labels
    if (z_order_map_label_.find(*it) != z_order_map_label_.end()) {
      for(std::unordered_map<uint32_t, Label*>::iterator it2 = 
          z_order_map_label_.at(*it).begin(); it2 
          != z_order_map_label_.at(*it).end(); 
          it2++){
        
        it2->second->draw(*GM.window_->sfml_window_);
      }
    }

    // Print Sprites
    if (z_order_map_sprite_.find(*it) != z_order_map_sprite_.end()) {
      for(std::unordered_map<uint32_t, Sprite*>::iterator it2 = 
          z_order_map_sprite_.at(*it).begin(); it2 != 
          z_order_map_sprite_.at(*it).end(); 
          it2++){
        
        it2->second->draw(*GM.window_->sfml_window_);
      }
    }
  }
}

DrawableEntity *Scene::checkColision(sf::Vector2f& position, uint8_t *type){
  
  // Foreach Z-order we print the elements of that level
  for (std::set<uint32_t>::iterator it=z_order_levels.end(); 
       it!=z_order_levels.begin(); it--){
    
    // Check Backgrouds
    if (z_order_map_background_.find(*it) != z_order_map_background_.end()) {
      for (std::unordered_map<uint32_t, Background*>::iterator it2 =
          z_order_map_background_.at(*it).begin(); it2 
          != z_order_map_background_.at(*it).end();
          it2++) {

        if(it2->second->checkCollision(position)){
          *type = 1;
          return it2->second;
        }
      }
    }

    // Check Rects
    if (z_order_map_rect_.find(*it) != z_order_map_rect_.end()) {
      for(std::unordered_map<uint32_t, Rect*>::iterator it2 = 
          z_order_map_rect_.at(*it).begin(); it2 != 
          z_order_map_rect_.at(*it).end(); it2++){
        
        if(it2->second->checkCollision(position)){
          *type = 2;
          return it2->second;
        }
      }
    }

    // Check Labels
    if (z_order_map_label_.find(*it) != z_order_map_label_.end()) {
      for(std::unordered_map<uint32_t, Label*>::iterator it2 = 
          z_order_map_label_.at(*it).begin(); it2 
          != z_order_map_label_.at(*it).end(); 
          it2++){
        
        if(it2->second->checkCollision(position)){
          *type = 3;
          return it2->second;
        }
      }
    }

    // Check Sprites
    if (z_order_map_sprite_.find(*it) != z_order_map_sprite_.end()) {
      for(std::unordered_map<uint32_t, Sprite*>::iterator it2 = 
          z_order_map_sprite_.at(*it).begin(); it2 != 
          z_order_map_sprite_.at(*it).end(); 
          it2++){
        
        if(it2->second->checkCollision(position)){
          *type = 4;
          return it2->second;
        }
      }
    }
  }

  *type = 0;
  return NULL;
}


///// Texture /////
void Scene::addTexture(sf::Texture& texture, uint32_t texture_id){  
  std::pair<uint32_t, sf::Texture*> insert_pair(texture_id, &texture);
  map_texture_.insert(insert_pair); 
}

sf::Texture* Scene::getTexture(uint32_t texture_id){
  std::unordered_map<uint32_t, sf::Texture*>::const_iterator iterator = 
  map_texture_.find(texture_id);
  
  if(iterator == map_texture_.end()){
    return NULL; // Texture not found
  }else{
    return iterator->second;
  }
}
void Scene::removeTexture(uint32_t texture_id){
  sf::Texture *texture_tmp = map_texture_.at(texture_id);
  map_texture_.erase(texture_id);
}

///// Rect /////
void Scene::addRect(Rect& rect){
  z_order_levels.insert(rect.z_order_);
  std::pair<uint32_t, Rect*> insert_pair(rect.id(), &rect);
  map_rect_.insert(insert_pair);
 
  std::map<uint32_t, std::unordered_map<uint32_t, Rect*>>::const_iterator 
    iterator = z_order_map_rect_.find(rect.z_order_);

  if (iterator == z_order_map_rect_.end()) {
    std::unordered_map<uint32_t, Rect*> map_tmp;
    map_tmp.insert(insert_pair);

    std::pair<uint32_t, std::unordered_map<uint32_t, Rect*>> 
      insert_z_order_pair(rect.z_order_, map_tmp);
    z_order_map_rect_.insert(insert_z_order_pair);
  } else {
    //std::unordered_map<uint32_t, Rect*> map_tmp = iterator->second;
    //map_tmp.insert(insert_pair);

	  z_order_map_rect_.at(rect.z_order_).insert(insert_pair);
  }
}

Rect* Scene::getRect(uint32_t rect_id){
  std::unordered_map<uint32_t, Rect*>::const_iterator iterator = 
    map_rect_.find(rect_id);
  
  if(iterator == map_rect_.end()){
    return NULL; // Rect not found
  }else{
    return iterator->second;
  }
}
void Scene::removeRect(uint32_t rect_id){
  Rect *rect_tmp = map_rect_.at(rect_id);
  map_rect_.erase(rect_id);
  z_order_map_rect_.at(rect_tmp->z_order_).erase(rect_id);
}

///// Label /////
void Scene::addLabel(Label& label){
  z_order_levels.insert(label.z_order_);
  std::pair<uint32_t, Label*> insert_pair(label.id(), &label);
  map_label_.insert(insert_pair);
 
  std::map<uint32_t, std::unordered_map<uint32_t, Label*>>::const_iterator 
    iterator = z_order_map_label_.find(label.z_order_);

  if (iterator == z_order_map_label_.end()) {
    std::unordered_map<uint32_t, Label*> map_tmp;
    map_tmp.insert(insert_pair);

    std::pair<uint32_t, std::unordered_map<uint32_t, Label*>> 
      insert_z_order_pair(label.z_order_, map_tmp);
    z_order_map_label_.insert(insert_z_order_pair);
  } else {
	  z_order_map_label_.at(label.z_order_).insert(insert_pair);
  }
}

Label* Scene::getLabel(uint32_t label_id){
  std::unordered_map<uint32_t, Label*>::const_iterator iterator = 
    map_label_.find(label_id);
  
  if(iterator == map_label_.end()){
    return NULL; // Label not found
  }else{
    return iterator->second;
  }
}
void Scene::removeLabel(uint32_t label_id){
  Label *label_tmp = map_label_.at(label_id);
  map_label_.erase(label_id);
  z_order_map_label_.at(label_tmp->z_order_).erase(label_id);
}

///// Sprite /////
void Scene::addSprite(Sprite& sprite){
  z_order_levels.insert(sprite.z_order_);
  std::pair<uint32_t, Sprite*> insert_pair(sprite.id(), &sprite);
  map_sprite_.insert(insert_pair);
 
  std::map<uint32_t, std::unordered_map<uint32_t, Sprite*>>::const_iterator 
    iterator = z_order_map_sprite_.find(sprite.z_order_);

  if (iterator == z_order_map_sprite_.end()) {
    std::unordered_map<uint32_t, Sprite*> map_tmp;
    map_tmp.insert(insert_pair);

    std::pair<uint32_t, std::unordered_map<uint32_t, Sprite*>> 
      insert_z_order_pair(sprite.z_order_, map_tmp);
    z_order_map_sprite_.insert(insert_z_order_pair);
  } else {
	  z_order_map_sprite_.at(sprite.z_order_).insert(insert_pair);
  }
}

Sprite* Scene::getSprite(uint32_t sprite_id){
  std::unordered_map<uint32_t, Sprite*>::const_iterator iterator = 
    map_sprite_.find(sprite_id);
  
  if(iterator == map_sprite_.end()){
    return NULL; // Sprite not found
  }else{
    return iterator->second;
  }
}

void Scene::removeSprite(uint32_t sprite_id){
  Sprite *sprite_tmp = map_sprite_.at(sprite_id);
  map_sprite_.erase(sprite_id);
  z_order_map_sprite_.at(sprite_tmp->z_order_).erase(sprite_id);
}

///// Background /////
void Scene::addBackground(Background& background){
  z_order_levels.insert(background.z_order_);
  std::pair<uint32_t, Background*> insert_pair(background.id(), &background);
  map_background_.insert(insert_pair);
 
  std::map<uint32_t, std::unordered_map<uint32_t, Background*>>::const_iterator 
    iterator = z_order_map_background_.find(background.z_order_);

  if (iterator == z_order_map_background_.end()) {
    std::unordered_map<uint32_t, Background*> map_tmp;
    map_tmp.insert(insert_pair);

    std::pair<uint32_t, std::unordered_map<uint32_t, Background*>> 
      insert_z_order_pair(background.z_order_, map_tmp);
    z_order_map_background_.insert(insert_z_order_pair);
  } else {
	  z_order_map_background_.at(background.z_order_).insert(insert_pair);
  }
}

Background* Scene::getBackground(uint32_t background_id){
  std::unordered_map<uint32_t, Background*>::const_iterator iterator = 
    map_background_.find(background_id);
  
  if(iterator == map_background_.end()){
    return NULL; // Background not found
  }else{
    return iterator->second;
  }
}
void Scene::removeBackground(uint32_t background_id){
  Background *background_tmp = map_background_.at(background_id);
  map_background_.erase(background_id);
  z_order_map_background_.at(background_tmp->z_order_).erase(background_id);
}