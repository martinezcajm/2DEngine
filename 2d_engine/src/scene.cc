// Comments can be found at the header
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

  for (std::unordered_map<std::string, sf::Texture*>::iterator it =
    map_texture_.begin(); it != map_texture_.end(); ++it) {

    //free texture memory
    delete it->second;
  }

  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
    map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {
    
    switch(it->second->type())
    {
      case Entity::kRect:
        
        POOL.returnRect(*static_cast<Rect*>(it->second));
        break;
      case Entity::kBackground:
        POOL.returnBackground(*static_cast<Background*>(it->second));
        break;
      case Entity::kLabel:
        POOL.returnLabel(*static_cast<Label*>(it->second));
        break;
      case Entity::kSprite:
        POOL.returnSprite(*static_cast<Sprite*>(it->second));
        break;
    }
  }

  map_texture_.clear();
  map_drawable_entity_.clear();
  z_order_map_drawable_entity_.clear();
  z_order_levels.clear();
}

void Scene::loadScene(const std::string scene_path, const sf::Font& font){
  //TODO  
  std::ifstream i(scene_path);
  json j_scene;
  i >> j_scene;

  cleanScene();

  for (json::iterator it = j_scene["Textures"].begin(); it 
       != j_scene["Textures"].end(); ++it) {

    json j_texture = (json)*it;

    std::string texture_path = j_texture["texture_dir_"];
    sf::Texture *texture = this->getTexture(texture_path);
    
    if(texture == nullptr){
      texture = new sf::Texture();
      if(texture != nullptr){
        texture->loadFromFile(texture_path);  
        this->addTexture(*texture, texture_path);
      }
    }
  }

  for (json::iterator it = j_scene["Rects"].begin(); it 
       != j_scene["Rects"].end(); ++it) {
    
    json j_rect = (json)*it;
    // Create Rect    
    Rect *rect = POOL.getRect();
    if(rect!= nullptr){
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

      this->addDrawableEntity(*rect);
    }
  }

  for (json::iterator it = j_scene["Labels"].begin(); it 
       != j_scene["Labels"].end(); ++it) {

    json j_label = (json)*it;    
    // Create Label    
    Label *label = POOL.getLabel();
    if(label!= nullptr){
      std::string text = j_label["text_"];
      label->init(j_label["color_"]["r"], j_label["color_"]["g"], 
                  j_label["color_"]["b"], j_label["color_"]["a"],
                  j_label["position_"]["x"], j_label["position_"]["y"],
                  j_label["rotation_"], j_label["scale_"]["x"],
                  j_label["scale_"]["y"], text.c_str(), font);

      label->tag_ = j_label["tag_"];
      label->active_ = j_label["active_"];
      label->z_order_ = j_label["z_order_"];
      label->font_size_ = j_label["font_size_"];
      label->style_ = j_label["style_"];    
    
      this->addDrawableEntity(*label);
    }
  }
  
  for (json::iterator it = j_scene["Sprites"].begin(); it 
       != j_scene["Sprites"].end(); ++it) {

    json j_sprite = (json)*it;    
    // Create Sprite    
    Sprite *sprite = POOL.getSprite();
    
    if(sprite!= nullptr){
      uint8_t error_code = 0;  

      std::string texture_path = j_sprite["texture_dir_"];

      if(error_code == 0){
        // init using an image file
        if(j_sprite["origin_"] == SpriteOrigin::kSpriteOrigin_Image){
          sprite->init(j_sprite["position_"]["x"], j_sprite["position_"]["y"],
            j_sprite["rotation_"], j_sprite["scale_"]["x"],
            j_sprite["scale_"]["y"], texture_path);
        }else{
          // We need a texture in the mapping
          sf::Texture *texture = this->getTexture(texture_path);
    
          if(texture == nullptr){
            texture = new sf::Texture();
            if(texture != nullptr){
              texture->loadFromFile(texture_path);  
              this->addTexture(*texture, texture_path);
            }else{
              error_code = 1;
            }
          }
          // init by handle
          if(j_sprite["origin_"] == SpriteOrigin::kSpriteOrigin_Handler){ 
            sprite->init(j_sprite["position_"]["x"], j_sprite["position_"]["y"],
              j_sprite["rotation_"], j_sprite["scale_"]["x"],
              j_sprite["scale_"]["y"], *texture, texture_path);
          // init by memory
          }else if(j_sprite["origin_"] == SpriteOrigin::kSpriteOrigin_Memory){ 
            sprite->init(j_sprite["position_"]["x"], j_sprite["position_"]["y"],
              j_sprite["rotation_"], j_sprite["scale_"]["x"],
              j_sprite["scale_"]["y"], *texture, error_code, texture_path);      
          }else{
            error_code = 1; //No es un sprite valido
          }
        }
      }

      if(error_code == 0){
        sprite->tag_ = j_sprite["tag_"];
        sprite->active_ = j_sprite["active_"];
        sprite->z_order_ = j_sprite["z_order_"];
        sprite->color_.r = j_sprite["color_"]["r"];
        sprite->color_.g = j_sprite["color_"]["g"];
        sprite->color_.b = j_sprite["color_"]["b"];
        sprite->color_.a = j_sprite["color_"]["a"];

        this->addDrawableEntity(*sprite);
      }else{
        // if has error building the sprite, return it to the pool
        POOL.returnSprite(*sprite);
      }
    }
  }
  
  for (json::iterator it = j_scene["Backgrounds"].begin(); it 
       != j_scene["Backgrounds"].end(); ++it) {

    json j_background = (json)*it;    
    // Create Background    
    Background *background = POOL.getBackground();

    if(background!= nullptr){
      uint8_t error_code = 0;
      std::string texture_path = j_background["texture_dir_"];

      if(j_background["origin_"] == SpriteOrigin::kSpriteOrigin_Image){
        error_code = background->init(texture_path,
                                      j_background["dimensions_"]["x"],
                                      j_background["dimensions_"]["y"]);
      }
      
      if(error_code == 0){
        background->rotation_ = j_background["rotation_"];
        background->position_.x = j_background["position_"]["x"];
        background->position_.y = j_background["position_"]["y"];
        background->scale_.x = j_background["scale_"]["x"];
        background->scale_.y = j_background["scale_"]["y"];    
        background->color_.r = j_background["color_"]["r"];
        background->color_.g = j_background["color_"]["g"];
        background->color_.b = j_background["color_"]["b"];
        background->color_.a = j_background["color_"]["a"];    
        background->tag_ = j_background["tag_"];
        background->active_ = j_background["active_"];
        background->z_order_ = j_background["z_order_"];

        background->scrolls_horizontally_ = j_background["scrolls_horizontally_"];
        background->scrolls_vertically_ = j_background["scrolls_vertically_"];
        background->speed_.x = j_background["speed_"]["x"];
        background->speed_.y = j_background["speed_"]["y"];
        background->background_position_.x = 
          j_background["background_position_"]["x"];
        background->background_position_.y = 
          j_background["background_position_"]["y"];    

        this->addDrawableEntity(*background);
      }else{
        POOL.returnBackground(*background);
      }
    }
  }
}

void Scene::saveScene(const std::string scene_path){  
  json j_scene;
  json j_backgrounds;
  json j_rects;
  json j_labels;
  json j_sprites;
  json j_textures;

  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
    map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {
    
    json j_label;
    json j_rect;
    json j_sprite;
    json j_background;
    Label* label_tmp = nullptr;
    Rect* rect_tmp = nullptr;
    Sprite* sprite_tmp = nullptr;
    Background* background_tmp = nullptr;

    switch(it->second->type())
    {
      case Entity::kLabel:
        label_tmp = static_cast<Label*>(it->second);

        j_label["tag_"] =label_tmp->tag_;    
        j_label["active_"] = label_tmp->tag_;
        j_label["z_order_"] = label_tmp->z_order_;
        j_label["rotation_"] = label_tmp->rotation_;
        j_label["position_"]["x"] = label_tmp->position_.x;
        j_label["position_"]["y"] = label_tmp->position_.y;
        j_label["scale_"]["x"] = label_tmp->scale_.x;
        j_label["scale_"]["y"] = label_tmp->scale_.y;
        j_label["color_"]["r"] = label_tmp->color_.r;
        j_label["color_"]["g"] = label_tmp->color_.g;
        j_label["color_"]["b"] = label_tmp->color_.b;
        j_label["color_"]["a"] = label_tmp->color_.a;
        j_label["font_size_"] = label_tmp->font_size_;
        j_label["text_"] = label_tmp->text_;
        j_label["style_"] = label_tmp->style_;
    
        j_labels.push_back(j_label);

        break;
      case Entity::kRect:
        rect_tmp = static_cast<Rect*>(it->second);

        j_rect["tag_"] = rect_tmp->tag_;
        j_rect["active_"] = rect_tmp->active_;
        j_rect["z_order_"] = rect_tmp->z_order_;
        j_rect["rotation_"] = rect_tmp->rotation_;
        j_rect["position_"]["x"] = rect_tmp->position_.x;
        j_rect["position_"]["y"] = rect_tmp->position_.y;
        j_rect["scale_"]["x"] =rect_tmp->scale_.x;
        j_rect["scale_"]["y"] = rect_tmp->scale_.y;
        j_rect["color_"]["r"] = rect_tmp->color_.r;
        j_rect["color_"]["g"] = rect_tmp->color_.g;
        j_rect["color_"]["b"] = rect_tmp->color_.b;
        j_rect["color_"]["a"] = rect_tmp->color_.a;
        j_rect["is_solid_"] = rect_tmp->is_solid_;
        j_rect["dimensions_"]["x"] = rect_tmp->dimensions_.x;
        j_rect["dimensions_"]["y"] = rect_tmp->dimensions_.y;
        j_rect["rgba_fill_"]["r"] = rect_tmp->rgba_fill_.r;
        j_rect["rgba_fill_"]["g"] = rect_tmp->rgba_fill_.g;
        j_rect["rgba_fill_"]["b"] = rect_tmp->rgba_fill_.b;
        j_rect["rgba_fill_"]["a"] = rect_tmp->rgba_fill_.a;

        j_rects.push_back(j_rect);
        break;
      case Entity::kSprite:
        sprite_tmp = static_cast<Sprite*>(it->second);

        j_sprite["tag_"] = sprite_tmp->tag_;    
        j_sprite["active_"] = sprite_tmp->active_;
        j_sprite["z_order_"] = sprite_tmp->z_order_;
        j_sprite["rotation_"] = sprite_tmp->rotation_;
        j_sprite["position_"]["x"] = sprite_tmp->position_.x;
        j_sprite["position_"]["y"] = sprite_tmp->position_.y;
        j_sprite["scale_"]["x"] = sprite_tmp->scale_.x;
        j_sprite["scale_"]["y"] = sprite_tmp->scale_.y;
        j_sprite["color_"]["r"] = sprite_tmp->color_.r;
        j_sprite["color_"]["g"] = sprite_tmp->color_.g;
        j_sprite["color_"]["b"] = sprite_tmp->color_.b;
        j_sprite["color_"]["a"] = sprite_tmp->color_.a;
        j_sprite["texture_dir_"] = sprite_tmp->texture_dir_;
        j_sprite["origin_"] = sprite_tmp->origin();
    
        j_sprites.push_back(j_sprite);
        break;
      case Entity::kBackground:
        background_tmp = static_cast<Background*>(it->second);
        
        j_background["tag_"] = background_tmp->tag_;    
        j_background["active_"] = background_tmp->active_;
        j_background["z_order_"] = background_tmp->z_order_;
        j_background["rotation_"] = background_tmp->rotation_;
        j_background["position_"]["x"] = background_tmp->position_.x;
        j_background["position_"]["y"] = background_tmp->position_.y;
        j_background["scale_"]["x"] = background_tmp->scale_.x;
        j_background["scale_"]["y"] = background_tmp->scale_.y;
        j_background["color_"]["r"] = background_tmp->color_.r;
        j_background["color_"]["g"] = background_tmp->color_.g;
        j_background["color_"]["b"] = background_tmp->color_.b;
        j_background["color_"]["a"] = background_tmp->color_.a;
        j_background["texture_dir_"] = background_tmp->texture_dir_;
        j_background["origin_"] = background_tmp->origin();
        j_background["scrolls_horizontally_"] = background_tmp->scrolls_horizontally_;
        j_background["scrolls_vertically_"] = background_tmp->scrolls_vertically_;
        j_background["speed_"]["x"] = background_tmp->speed_.x;
        j_background["speed_"]["y"] = background_tmp->speed_.y;
        j_background["dimensions_"]["x"] = background_tmp->dimensions_.x;
        j_background["dimensions_"]["y"] = background_tmp->dimensions_.y;
        j_background["background_position_"]["x"] = 
          background_tmp->background_position_.x;
        j_background["background_position_"]["y"] = 
          background_tmp->background_position_.y;

        j_backgrounds.push_back(j_background);  
        
        break;
    }
  }
  
  for (std::unordered_map<std::string, sf::Texture*>::iterator it =
    map_texture_.begin(); it != map_texture_.end(); ++it) {

    //it->second;
    json j_texture;
    j_texture["texture_dir_"] = it->first;

    j_textures.push_back(j_texture);
  }

  j_scene["Rects"] = { j_rects };
  j_scene["Labels"] = { j_labels };
  j_scene["Sprites"] = { j_sprites };
  j_scene["Backgrounds"] = { j_backgrounds };
  j_scene["Textures"] = { j_textures };

  std::ofstream o(scene_path);
  o << std::setw(2) << j_scene << std::endl;  
}

void Scene::drawScene(){
  GameManager& GM = GameManager::instance();

  // Foreach Z-order we print the elements of that level
  for (std::set<int32_t>::iterator it=z_order_levels.begin(); 
       it!=z_order_levels.end(); ++it){
        
    // Print Entities
    if (z_order_map_drawable_entity_.find(*it) 
        != z_order_map_drawable_entity_.end()) {
      for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it2 =
        z_order_map_drawable_entity_.at(*it).begin(); it2 
          != z_order_map_drawable_entity_.at(*it).end();
          ++it2) {

        it2->second->draw(*GM.window_->sfml_window_);
      }
    }
  }
}

uint32_t Scene::checkCollision(sf::Vector2f& position){
  std::set<int32_t>::iterator it = z_order_levels.end();
  do {
    --it;
    
    // Check Entities
    if (z_order_map_drawable_entity_.find(*it) != z_order_map_drawable_entity_.end()) {
      for(std::unordered_map<uint32_t, DrawableEntity*>::iterator it2 = 
          z_order_map_drawable_entity_.at(*it).begin(); it2 != 
          z_order_map_drawable_entity_.at(*it).end(); ++it2){
        
        if(it2->second->checkCollision(position)){
          return it2->first;
        }
      }
    }
  } while (it != z_order_levels.begin());

  return 0;
}

std::list<DrawableEntity*> Scene::getDrawableEntitiesByTag(uint32_t tag){
  std::list<DrawableEntity*> return_list;
  
  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
       map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {

    if(it->second->tag_ == tag){
      return_list.push_back(it->second);
    }
  }

  return return_list;
}

void Scene::update(){
  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
       map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {
      
    it->second->update();    
  }
}

///// Texture /////
void Scene::addTexture(sf::Texture& texture, const std::string texture_path){  
  std::pair<std::string, sf::Texture*> insert_pair(texture_path, &texture);
  map_texture_.insert(insert_pair); 
}

sf::Texture* Scene::getTexture(const std::string texture_path){
  std::unordered_map<std::string, sf::Texture*>::const_iterator iterator = 
  map_texture_.find(texture_path);
  
  if(iterator == map_texture_.end()){
    return nullptr; // Texture not found
  }else{
    return iterator->second;
  }
}
void Scene::removeTexture(const std::string texture_path){
  sf::Texture *texture_tmp = map_texture_.at(texture_path);
  free(texture_tmp);
  map_texture_.erase(texture_path);
}


///// DrawableEntity /////
void Scene::addDrawableEntity(DrawableEntity& drawable_entity){
  z_order_levels.insert(drawable_entity.z_order_);
  std::pair<uint32_t, DrawableEntity*> insert_pair(drawable_entity.id(), &drawable_entity);
  map_drawable_entity_.insert(insert_pair);
 
  std::map<int32_t, std::unordered_map<uint32_t, DrawableEntity*>>::const_iterator 
    iterator = z_order_map_drawable_entity_.find(drawable_entity.z_order_);

  if (iterator == z_order_map_drawable_entity_.end()) {
    std::unordered_map<uint32_t, DrawableEntity*> map_tmp;
    map_tmp.insert(insert_pair);

    std::pair<int32_t, std::unordered_map<uint32_t, DrawableEntity*>> 
      insert_z_order_pair(drawable_entity.z_order_, map_tmp);
    z_order_map_drawable_entity_.insert(insert_z_order_pair);
  } else {
	  z_order_map_drawable_entity_.at(drawable_entity.z_order_).insert(insert_pair);
  }
}

DrawableEntity* Scene::getDrawableEntity(const uint32_t drawable_entity_id){
  std::unordered_map<uint32_t, DrawableEntity*>::const_iterator iterator = 
    map_drawable_entity_.find(drawable_entity_id);
  
  if(iterator == map_drawable_entity_.end()){
    return nullptr; // DrawableEntity not found
  }else{
    return iterator->second;
  }
}
void Scene::removeDrawableEntity(const uint32_t drawable_entity_id){
  DrawableEntity *drawable_entity_tmp = map_drawable_entity_.at(drawable_entity_id);
  if(drawable_entity_tmp != nullptr){
    map_drawable_entity_.erase(drawable_entity_id);
    z_order_map_drawable_entity_.at(drawable_entity_tmp->z_order_).erase(drawable_entity_id);
  }
}
void Scene::changeZOrderDrawableEntity(const uint32_t drawable_entity_id, const int32_t newZOrder){
  // Obtain the drawable_entity
  DrawableEntity *drawable_entity_tmp = map_drawable_entity_.at(drawable_entity_id);

  if(drawable_entity_tmp != nullptr){
    z_order_map_drawable_entity_.at(drawable_entity_tmp->z_order_).erase(drawable_entity_id);
    z_order_levels.insert(newZOrder);

    // Create pair to insert in z_order_map_drawable_entity_
    std::pair<uint32_t, DrawableEntity*> insert_pair(drawable_entity_id, drawable_entity_tmp);
    // Create iterator for z_order_map_drawable_entity_
    std::map<int32_t, std::unordered_map<uint32_t, DrawableEntity*>>::const_iterator 
      iterator = z_order_map_drawable_entity_.find(newZOrder);

    if (iterator == z_order_map_drawable_entity_.end()) {
      // If z-order is not in z_order_map_drawable_entity_ we add a new map in the z-order
      std::unordered_map<uint32_t, DrawableEntity*> map_tmp;
      map_tmp.insert(insert_pair);

      std::pair<int32_t, std::unordered_map<uint32_t, DrawableEntity*>> 
        insert_z_order_pair(newZOrder, map_tmp);
      z_order_map_drawable_entity_.insert(insert_z_order_pair);
    } else {
      // If z-order is in z_order_map_drawable_entity_ we only add the pair in the z-order
      z_order_map_drawable_entity_.at(newZOrder).insert(insert_pair);
    }

    drawable_entity_tmp->z_order_ = newZOrder;
  }
}
