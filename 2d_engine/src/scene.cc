#include "scene.h"
#include "game_manager.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

// for convenience
using json = nlohmann::json;

Scene::Scene(){}
Scene::~Scene(){
  cleanScene();
}

void Scene::cleanScene(){
  // TODO: Return objects to the Pool

  map_texture_.clear();
  map_rect_.clear();
  z_order_map_rect_.clear();
  map_label_.clear();
  z_order_map_label_.clear();
  map_sprite_.clear();
  z_order_map_sprite_.clear();
  map_background_.clear();
  z_order_map_background_.clear();
  z_order_levels.clear();
}

void Scene::loadScene(std::string scene_path){
  //TODO  
  std::ifstream i(scene_path);
  json j_scene;
  i >> j_scene;

  cleanScene();

  for (json::iterator it = j_scene["Rects"].begin(); it 
       != j_scene["Rects"].end(); ++it) {
    //std::cout << *it << '\n';
    
    json j_rect = (json)*it;

    // Create Rect    
    Rect *rect = Rect::CreateRect();
    rect->init(j_rect["is_solid_"], j_rect["dimensions_"]["x"], 
               j_rect["dimensions_"]["y"], j_rect["color_"]["r"],
               j_rect["color_"]["g"], j_rect["color_"]["b"],
               j_rect["color_"]["a"], j_rect["rgba_fill_"]["r"],
               j_rect["rgba_fill_"]["g"], j_rect["rgba_fill_"]["b"],
               j_rect["rgba_fill_"]["a"], j_rect["position_"]["x"],
               j_rect["position_"]["y"], j_rect["rotation_"], 
               j_rect["scale_"]["x"], j_rect["scale_"]["y"]);
    rect->tag_ = j_rect["tag_"];
    rect->active_ = j_rect["active_"];
    rect->z_order_ = j_rect["z_order_"];

    this->addRect(*rect);
  }
}

void Scene::saveScene(std::string scene_path){
  json j_scene;
  json j_backgrounds;
  json j_rects;
  json j_labels;
  json j_sprites;

  for (std::unordered_map<uint32_t, Rect*>::iterator it =
    map_rect_.begin(); it != map_rect_.end(); it++) {
      
    //it->second;
    json j_rect;
    j_rect["tag_"] = it->second->tag_;
    j_rect["active_"] = it->second->active_;
    j_rect["z_order_"] = it->second->z_order_;
    j_rect["rotation_"] = it->second->rotation_;
    j_rect["position_"]["x"] = it->second->position_.x;
    j_rect["position_"]["y"] = it->second->position_.y;
    j_rect["scale_"]["x"] = it->second->scale_.x;
    j_rect["scale_"]["y"] = it->second->scale_.y;
    j_rect["color_"]["r"] = it->second->color_.r;
    j_rect["color_"]["g"] = it->second->color_.g;
    j_rect["color_"]["b"] = it->second->color_.b;
    j_rect["color_"]["a"] = it->second->color_.a;
    j_rect["is_solid_"] = it->second->is_solid_;
    j_rect["dimensions_"]["x"] = it->second->dimensions_.x;
    j_rect["dimensions_"]["y"] = it->second->dimensions_.y;
    j_rect["rgba_fill_"]["r"] = it->second->rgba_fill_.r;
    j_rect["rgba_fill_"]["g"] = it->second->rgba_fill_.g;
    j_rect["rgba_fill_"]["b"] = it->second->rgba_fill_.b;
    j_rect["rgba_fill_"]["a"] = it->second->rgba_fill_.a;

    j_rects.push_back(j_rect);
  }  

  for (std::unordered_map<uint32_t, Label*>::iterator it =
    map_label_.begin(); it != map_label_.end(); it++) {
      
    //it->second;
    json j_label;
    j_label["tag_"] = it->second->tag_;    
    j_label["active_"] = it->second->tag_;
    j_label["z_order_"] = it->second->z_order_;
    j_label["rotation_"] = it->second->rotation_;
    j_label["position_"]["x"] = it->second->position_.x;
    j_label["position_"]["y"] = it->second->position_.y;
    j_label["scale_"]["x"] = it->second->scale_.x;
    j_label["scale_"]["y"] = it->second->scale_.y;
    j_label["color_"]["r"] = it->second->color_.r;
    j_label["color_"]["g"] = it->second->color_.g;
    j_label["color_"]["b"] = it->second->color_.b;
    j_label["color_"]["a"] = it->second->color_.a;
    j_label["font_size_"] = it->second->font_size_;
    j_label["text_"] = it->second->text_;
    j_label["style_"] = it->second->style_;

    j_labels.push_back(j_label);
  }

  for (std::unordered_map<uint32_t, Sprite*>::iterator it =
    map_sprite_.begin(); it != map_sprite_.end(); it++) {

    //it->second;
    json j_sprite;
    j_sprite["tag_"] = it->second->tag_;    
    j_sprite["active_"] = it->second->tag_;
    j_sprite["z_order_"] = it->second->z_order_;
    j_sprite["rotation_"] = it->second->rotation_;
    j_sprite["position_"]["x"] = it->second->position_.x;
    j_sprite["position_"]["y"] = it->second->position_.y;
    j_sprite["scale_"]["x"] = it->second->scale_.x;
    j_sprite["scale_"]["y"] = it->second->scale_.y;
    j_sprite["color_"]["r"] = it->second->color_.r;
    j_sprite["color_"]["g"] = it->second->color_.g;
    j_sprite["color_"]["b"] = it->second->color_.b;
    j_sprite["color_"]["a"] = it->second->color_.a;
    //j_sprite["texture_path"] = it->second->getTexturePath();
    //j_sprite["origin_"] = it->second->origin_;

    j_sprites.push_back(j_sprite);
  }
  
  for (std::unordered_map<uint32_t, Background*>::iterator it =
    map_background_.begin(); it != map_background_.end(); it++) {

    //it->second;
    json j_background;
    j_background["tag_"] = it->second->tag_;    
    j_background["active_"] = it->second->tag_;
    j_background["z_order_"] = it->second->z_order_;
    j_background["rotation_"] = it->second->rotation_;
    j_background["position_"]["x"] = it->second->position_.x;
    j_background["position_"]["y"] = it->second->position_.y;
    j_background["scale_"]["x"] = it->second->scale_.x;
    j_background["scale_"]["y"] = it->second->scale_.y;
    j_background["color_"]["r"] = it->second->color_.r;
    j_background["color_"]["g"] = it->second->color_.g;
    j_background["color_"]["b"] = it->second->color_.b;
    j_background["color_"]["a"] = it->second->color_.a;
    //j_background["texture_path"] = it->second->getTexturePath();
    //j_background["origin_"] = it->second->origin_;
    j_background["scrolls_horizontally_"] = it->second->scrolls_horizontally_;
    j_background["scrolls_horizontally_"] = it->second->scrolls_horizontally_;
    j_background["speed_"]["x"] = it->second->speed_.x;
    j_background["speed_"]["y"] = it->second->speed_.y;
    j_background["dimensions_"]["x"] = it->second->dimensions_.x;
    j_background["dimensions_"]["y"] = it->second->dimensions_.y;
    j_background["background_position_"]["x"] = 
      it->second->background_position_.x;
    j_background["background_position_"]["y"] = 
      it->second->background_position_.y;

    j_backgrounds.push_back(j_background);
  }

  j_scene["Rects"] = { j_rects };
  j_scene["Labels"] = { j_labels };
  j_scene["Sprites"] = { j_sprites };
  j_scene["Backgrounds"] = { j_backgrounds };

  std::ofstream o(scene_path);
  o << std::setw(2) << j_scene << std::endl;
}

void Scene::drawScene(){
  GameManager& GM = GameManager::instance();

  // Foreach Z-order we print the elements of that level
  for (std::set<uint32_t>::iterator it=z_order_levels.begin(); 
       it!=z_order_levels.end(); it++){
        
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

DrawableEntity *Scene::checkCollision(sf::Vector2f& position, uint8_t *type){
  
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