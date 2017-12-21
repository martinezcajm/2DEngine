// Author: Sebastián Adrover Pedrosa
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
      case Entity::kWall:
        POOL.returnWall(*static_cast<Wall*>(it->second));
        break;
      case Entity::kBrick:
        POOL.returnBrick(*static_cast<Brick*>(it->second));
        break;
      case Entity::kBall:
        POOL.returnBall(*static_cast<Ball*>(it->second));
        break;
      case Entity::kPlayer:
        POOL.returnPlayer(*static_cast<Player*>(it->second));
        break;
    }
  }

  map_texture_.clear();
  map_drawable_entity_.clear();
  z_order_map_drawable_entity_.clear();
  z_order_levels.clear();
}

void Scene::loadScene(const std::string scene_path, const sf::Font& font){
  scene_path_ = scene_path;
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

  
  for (json::iterator it = j_scene["Walls"].begin(); it 
  != j_scene["Walls"].end(); ++it) {

    json j_wall = (json)*it;
    // Create Wall    
    Wall *wall = POOL.getWall();
    if(wall!= nullptr){
      wall->init(j_wall["dimensions_"]["x"], j_wall["dimensions_"]["y"], 
                 j_wall["color_"]["r"], j_wall["color_"]["g"], 
                 j_wall["color_"]["b"], j_wall["color_"]["a"], 
                 j_wall["rgba_fill_"]["r"], j_wall["rgba_fill_"]["g"], 
                 j_wall["rgba_fill_"]["b"], j_wall["rgba_fill_"]["a"], 
                 j_wall["position_"]["x"], j_wall["position_"]["y"], 
                 j_wall["rotation_"], j_wall["scale_"]["x"], 
                 j_wall["scale_"]["y"]);

      wall->tag_ = j_wall["tag_"];
      wall->active_ = j_wall["active_"];
      wall->z_order_ = j_wall["z_order_"];

      this->addDrawableEntity(*wall);
    }
  }
  
  for (json::iterator it = j_scene["Bricks"].begin(); it 
  != j_scene["Bricks"].end(); ++it) {

    json j_brick = (json)*it;
    // Create Wall    
    Brick *brick = POOL.getBrick();
    if(brick!= nullptr){
      brick->init(j_brick["dimensions_"]["x"], j_brick["dimensions_"]["y"], 
                 j_brick["color_"]["r"], j_brick["color_"]["g"], 
                 j_brick["color_"]["b"], j_brick["color_"]["a"], 
                 j_brick["rgba_fill_"]["r"], j_brick["rgba_fill_"]["g"], 
                 j_brick["rgba_fill_"]["b"], j_brick["rgba_fill_"]["a"], 
                 j_brick["position_"]["x"], j_brick["position_"]["y"], 
                 j_brick["rotation_"], j_brick["scale_"]["x"], 
                 j_brick["scale_"]["y"], j_brick["lives_"]);

      brick->tag_ = j_brick["tag_"];
      brick->active_ = j_brick["active_"];
      brick->z_order_ = j_brick["z_order_"];

      this->addDrawableEntity(*brick);
    }
  }

  for (json::iterator it = j_scene["Balls"].begin(); it 
  != j_scene["Balls"].end(); ++it) {

    json j_ball = (json)*it;    
    // Create Ball    
    Ball *ball = POOL.getBall();

    if(ball!= nullptr){
      uint8_t error_code = 0;  

      std::string texture_path = j_ball["texture_dir_"];

      if(error_code == 0){
        // init using an image file
        if(j_ball["origin_"] == SpriteOrigin::kSpriteOrigin_Image){
          ball->init(j_ball["position_"]["x"], j_ball["position_"]["y"],
            j_ball["scale_"]["x"], j_ball["scale_"]["y"], 
            j_ball["speed_"]["x"], j_ball["speed_"]["y"], 
            texture_path);
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
          if(j_ball["origin_"] == SpriteOrigin::kSpriteOrigin_Handler){ 
            ball->init(j_ball["position_"]["x"], j_ball["position_"]["y"],
              j_ball["scale_"]["x"], j_ball["scale_"]["y"], 
              j_ball["speed_"]["x"], j_ball["speed_"]["y"], 
              *texture, texture_path);
          // init by memory
          }else if(j_ball["origin_"] == SpriteOrigin::kSpriteOrigin_Memory){ 
            ball->init(j_ball["position_"]["x"], j_ball["position_"]["y"],
              j_ball["scale_"]["x"], j_ball["scale_"]["y"], 
              j_ball["speed_"]["x"], j_ball["speed_"]["y"], 
              *texture, error_code, texture_path);      
          }else{
            error_code = 1; //No es un ball valido
          }
        }
      }

      if(error_code == 0){
        ball->tag_ = j_ball["tag_"];
        ball->active_ = j_ball["active_"];
        ball->z_order_ = j_ball["z_order_"];
        ball->color_.r = j_ball["color_"]["r"];
        ball->color_.g = j_ball["color_"]["g"];
        ball->color_.b = j_ball["color_"]["b"];
        ball->color_.a = j_ball["color_"]["a"];

        this->addDrawableEntity(*ball);
      }else{
        // if has error building the ball, return it to the pool
        POOL.returnBall(*ball);
      }
    }
  }
  

  for (json::iterator it = j_scene["Players"].begin(); it 
  != j_scene["Players"].end(); ++it) {

    json j_player = (json)*it;    
    // Create Player    
    Player *player = POOL.getPlayer();

    if(player!= nullptr){
      uint8_t error_code = 0;  

      std::string texture_path = j_player["texture_dir_"];

      if(error_code == 0){
        // init using an image file
        if(j_player["origin_"] == SpriteOrigin::kSpriteOrigin_Image){
          player->init(j_player["position_"]["x"], j_player["position_"]["y"],
            j_player["scale_"]["x"], j_player["scale_"]["y"], 
            j_player["speed_"]["x"], j_player["speed_"]["y"], 
            texture_path);
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
          if(j_player["origin_"] == SpriteOrigin::kSpriteOrigin_Handler){ 
            player->init(j_player["position_"]["x"], j_player["position_"]["y"],
              j_player["scale_"]["x"], j_player["scale_"]["y"], 
              j_player["speed_"]["x"], j_player["speed_"]["y"], 
              *texture, texture_path);
          // init by memory
          }else if(j_player["origin_"] == SpriteOrigin::kSpriteOrigin_Memory){ 
            player->init(j_player["position_"]["x"], j_player["position_"]["y"],
              j_player["scale_"]["x"], j_player["scale_"]["y"], 
              j_player["speed_"]["x"], j_player["speed_"]["y"], 
              *texture, error_code, texture_path);      
          }else{
            error_code = 1; //No es un player valido
          }
        }
      }

      if(error_code == 0){
        player->tag_ = j_player["tag_"];
        player->active_ = j_player["active_"];
        player->z_order_ = j_player["z_order_"];
        player->color_.r = j_player["color_"]["r"];
        player->color_.g = j_player["color_"]["g"];
        player->color_.b = j_player["color_"]["b"];
        player->color_.a = j_player["color_"]["a"];

        this->addDrawableEntity(*player);
      }else{
        // if has error building the player, return it to the pool
        POOL.returnPlayer(*player);
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
  json j_walls;
  json j_bricks;
  json j_balls;
  json j_players;

  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
    map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {
    
    json j_label;
    json j_rect;
    json j_sprite;
    json j_background;    
    json j_wall;
    json j_brick;
    json j_ball;
    json j_player;

    Label* label_tmp = nullptr;
    Rect* rect_tmp = nullptr;
    Sprite* sprite_tmp = nullptr;
    Background* background_tmp = nullptr;
    
    wall_tmp_ = nullptr;
    brick_tmp_ = nullptr;
    ball_tmp_ = nullptr;
    player_tmp_ = nullptr;

    switch(it->second->type())
    {
      case Entity::kLabel:
        label_tmp = static_cast<Label*>(it->second);

        j_label["tag_"] =label_tmp->tag_;    
        j_label["active_"] = label_tmp->active_;
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
        
      case Entity::kWall:
        wall_tmp_ = static_cast<Wall*>(it->second);

        j_wall["tag_"] = wall_tmp_->tag_;
        j_wall["active_"] = wall_tmp_->active_;
        j_wall["z_order_"] = wall_tmp_->z_order_;
        j_wall["rotation_"] = wall_tmp_->rotation_;
        j_wall["position_"]["x"] = wall_tmp_->position_.x;
        j_wall["position_"]["y"] = wall_tmp_->position_.y;
        j_wall["scale_"]["x"] =wall_tmp_->scale_.x;
        j_wall["scale_"]["y"] = wall_tmp_->scale_.y;
        j_wall["color_"]["r"] = wall_tmp_->color_.r;
        j_wall["color_"]["g"] = wall_tmp_->color_.g;
        j_wall["color_"]["b"] = wall_tmp_->color_.b;
        j_wall["color_"]["a"] = wall_tmp_->color_.a;
        j_wall["is_solid_"] = wall_tmp_->is_solid_;
        j_wall["dimensions_"]["x"] = wall_tmp_->dimensions_.x;
        j_wall["dimensions_"]["y"] = wall_tmp_->dimensions_.y;
        j_wall["rgba_fill_"]["r"] = wall_tmp_->rgba_fill_.r;
        j_wall["rgba_fill_"]["g"] = wall_tmp_->rgba_fill_.g;
        j_wall["rgba_fill_"]["b"] = wall_tmp_->rgba_fill_.b;
        j_wall["rgba_fill_"]["a"] = wall_tmp_->rgba_fill_.a;

        j_walls.push_back(j_wall);
        break;
      case Entity::kBrick:
        brick_tmp_ = static_cast<Brick*>(it->second);

        j_brick["tag_"] = brick_tmp_->tag_;
        j_brick["active_"] = brick_tmp_->active_;
        j_brick["z_order_"] = brick_tmp_->z_order_;
        j_brick["rotation_"] = brick_tmp_->rotation_;
        j_brick["position_"]["x"] = brick_tmp_->position_.x;
        j_brick["position_"]["y"] = brick_tmp_->position_.y;
        j_brick["scale_"]["x"] =brick_tmp_->scale_.x;
        j_brick["scale_"]["y"] = brick_tmp_->scale_.y;
        j_brick["color_"]["r"] = brick_tmp_->color_.r;
        j_brick["color_"]["g"] = brick_tmp_->color_.g;
        j_brick["color_"]["b"] = brick_tmp_->color_.b;
        j_brick["color_"]["a"] = brick_tmp_->color_.a;
        j_brick["is_solid_"] = brick_tmp_->is_solid_;
        j_brick["dimensions_"]["x"] = brick_tmp_->dimensions_.x;
        j_brick["dimensions_"]["y"] = brick_tmp_->dimensions_.y;
        j_brick["rgba_fill_"]["r"] = brick_tmp_->rgba_fill_.r;
        j_brick["rgba_fill_"]["g"] = brick_tmp_->rgba_fill_.g;
        j_brick["rgba_fill_"]["b"] = brick_tmp_->rgba_fill_.b;
        j_brick["rgba_fill_"]["a"] = brick_tmp_->rgba_fill_.a;
        j_brick["lives_"] = brick_tmp_->lives_;

        j_bricks.push_back(j_brick);
        break;
      case Entity::kBall:
        ball_tmp_ = static_cast<Ball*>(it->second);

        j_ball["tag_"] = ball_tmp_->tag_;    
        j_ball["active_"] = ball_tmp_->active_;
        j_ball["z_order_"] = ball_tmp_->z_order_;
        j_ball["rotation_"] = ball_tmp_->rotation_;
        j_ball["position_"]["x"] = ball_tmp_->position_.x;
        j_ball["position_"]["y"] = ball_tmp_->position_.y;
        j_ball["scale_"]["x"] = ball_tmp_->scale_.x;
        j_ball["scale_"]["y"] = ball_tmp_->scale_.y;
        j_ball["color_"]["r"] = ball_tmp_->color_.r;
        j_ball["color_"]["g"] = ball_tmp_->color_.g;
        j_ball["color_"]["b"] = ball_tmp_->color_.b;
        j_ball["color_"]["a"] = ball_tmp_->color_.a;
        j_ball["texture_dir_"] = ball_tmp_->texture_dir_;
        j_ball["origin_"] = ball_tmp_->origin();
        j_ball["speed_"]["x"] = ball_tmp_->speed_.x;
        j_ball["speed_"]["y"] = ball_tmp_->speed_.y;
    
        j_balls.push_back(j_ball);
        break;
      case Entity::kPlayer:
        player_tmp_ = static_cast<Player*>(it->second);

        j_player["tag_"] = player_tmp_->tag_;    
        j_player["active_"] = player_tmp_->active_;
        j_player["z_order_"] = player_tmp_->z_order_;
        j_player["rotation_"] = player_tmp_->rotation_;
        j_player["position_"]["x"] = player_tmp_->position_.x;
        j_player["position_"]["y"] = player_tmp_->position_.y;
        j_player["scale_"]["x"] = player_tmp_->scale_.x;
        j_player["scale_"]["y"] = player_tmp_->scale_.y;
        j_player["color_"]["r"] = player_tmp_->color_.r;
        j_player["color_"]["g"] = player_tmp_->color_.g;
        j_player["color_"]["b"] = player_tmp_->color_.b;
        j_player["color_"]["a"] = player_tmp_->color_.a;
        j_player["texture_dir_"] = player_tmp_->texture_dir_;
        j_player["origin_"] = player_tmp_->origin();
        j_player["speed_"]["x"] = player_tmp_->speed_.x;
        j_player["speed_"]["y"] = player_tmp_->speed_.y;
    
        j_players.push_back(j_player);
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
  j_scene["Walls"] = { j_walls };
  j_scene["Bricks"] = { j_bricks };
  j_scene["Balls"] = { j_balls };
  j_scene["Players"] = { j_players };

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

std::list<DrawableEntity*> Scene::getDrawableEntitiesByTag(int tag){
  std::list<DrawableEntity*> return_list;
  
  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
       map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {

    if(it->second->tag_ == tag){
      return_list.push_back(it->second);
    }
  }

  return return_list;
}

std::list<DrawableEntity*> Scene::getDrawableEntitiesBySelectionTag(
  uint8_t selection_tag){
  std::list<DrawableEntity*> return_list;
  
  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
       map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {

    if(it->second->selection_tag_ == selection_tag){
      return_list.push_back(it->second);
    }
  }

  return return_list;
}

void Scene::update(){
  for (std::unordered_map<uint32_t, DrawableEntity*>::iterator it =
       map_drawable_entity_.begin(); it != map_drawable_entity_.end(); ++it) {
          
    switch(it->second->type())
    {
      case Entity::kWall:
        break;
      case Entity::kBrick:
        break;
      case Entity::kBall:
        ball_tmp_ = static_cast<Ball*>(it->second);


        if(ball_tmp_->position_.y > 750){
          list_tmp_ = getDrawableEntitiesByTag(12);
          for (std::list<DrawableEntity*>::const_iterator it2 =
            list_tmp_.begin(); it2 != list_tmp_.end(); ++it2) {

            // Reset Player position
            player_tmp_ = static_cast<Player*>(*it2);
            player_tmp_->position_.x = 275;
            player_tmp_->position_.y = 725;
          }
        }
        else{
          // Check Collision with Walls
          list_tmp_ = getDrawableEntitiesByTag(10);
          for (std::list<DrawableEntity*>::const_iterator it2 =
            list_tmp_.begin(); it2 != list_tmp_.end(); ++it2) {

            if((*it2)->active_){
              f_rect =  it->second->getBoundaries();
              pos_top_.x = f_rect.left + (f_rect.width / 2);
              pos_top_.y = f_rect.top;

              pos_down_.x = f_rect.left + (f_rect.width / 2);
              pos_down_.y = f_rect.top + f_rect.height;

              pos_left_.x = f_rect.left;
              pos_left_.y = f_rect.top + (f_rect.height / 2);

              pos_right_.x = f_rect.left + f_rect.width;
              pos_right_.y = f_rect.top + (f_rect.height / 2);

              if((*it2)->checkCollision(pos_top_)){
                ball_tmp_->speed_.y *= -1;
              }else if((*it2)->checkCollision(pos_down_)){
                ball_tmp_->speed_.y *= -1;
              }else if((*it2)->checkCollision(pos_left_)){
                ball_tmp_->speed_.x *= -1;
              }else if((*it2)->checkCollision(pos_right_)){
                ball_tmp_->speed_.x *= -1;
              }
            }
          }

          // Check Collision with Bricks
          list_tmp_ = getDrawableEntitiesByTag(11);
          count_bricks_ = 0;
          for (std::list<DrawableEntity*>::const_iterator it2 =
            list_tmp_.begin(); it2 != list_tmp_.end(); ++it2) {

            if((*it2)->active_){
              count_bricks_ += 1;
              f_rect =  it->second->getBoundaries();
              pos_top_.x = f_rect.left + (f_rect.width / 2);
              pos_top_.y = f_rect.top;

              pos_down_.x = f_rect.left + (f_rect.width / 2);
              pos_down_.y = f_rect.top + f_rect.height;

              pos_left_.x = f_rect.left;
              pos_left_.y = f_rect.top + (f_rect.height / 2);

              pos_right_.x = f_rect.left + f_rect.width;
              pos_right_.y = f_rect.top + (f_rect.height / 2);

              if((*it2)->checkCollision(pos_top_)){
                brick_tmp_ = static_cast<Brick*>(*it2);
                brick_tmp_->lives_ -= 1;
                ball_tmp_->speed_.y *= -1;
              }else if((*it2)->checkCollision(pos_down_)){
                brick_tmp_ = static_cast<Brick*>(*it2);
                brick_tmp_->lives_ -= 1;
                ball_tmp_->speed_.y *= -1;
              }else if((*it2)->checkCollision(pos_left_)){
                brick_tmp_ = static_cast<Brick*>(*it2);
                brick_tmp_->lives_ -= 1;
                ball_tmp_->speed_.x *= -1;
              }else if((*it2)->checkCollision(pos_right_)){
                brick_tmp_ = static_cast<Brick*>(*it2);
                brick_tmp_->lives_ -= 1;
                ball_tmp_->speed_.x *= -1;
              }
            }
          }
          if(count_bricks_ == 0){
            is_game_over_ = 1;
          }

          // Check Collision with Player
          list_tmp_ = getDrawableEntitiesByTag(12);
          for (std::list<DrawableEntity*>::const_iterator it2 =
            list_tmp_.begin(); it2 != list_tmp_.end(); ++it2) {

            if((*it2)->active_){
              f_rect =  it->second->getBoundaries();
              pos_top_.x = f_rect.left + (f_rect.width / 2);
              pos_top_.y = f_rect.top;

              pos_down_.x = f_rect.left + (f_rect.width / 2);
              pos_down_.y = f_rect.top + f_rect.height;

              pos_left_.x = f_rect.left;
              pos_left_.y = f_rect.top + (f_rect.height / 2);

              pos_right_.x = f_rect.left + f_rect.width;
              pos_right_.y = f_rect.top + (f_rect.height / 2);

              if((*it2)->checkCollision(pos_top_)){
                ball_tmp_->speed_.y *= -1;
              }else if((*it2)->checkCollision(pos_down_)){
                f_rect =  (*it2)->getBoundaries();              
                ball_tmp_->speed_.y *= -1;
                
                if(pos_down_.x < f_rect.left + (f_rect.width / 6)){
                  ball_tmp_->speed_.x = -6;
                }else if(pos_down_.x < f_rect.left + ((f_rect.width / 6) * 2)){
                  ball_tmp_->speed_.x = -4;
                }else if(pos_down_.x < f_rect.left + ((f_rect.width / 6) * 3)){
                  ball_tmp_->speed_.x = -2;
                }else if(pos_down_.x < f_rect.left + ((f_rect.width / 6) * 4)){
                  ball_tmp_->speed_.x = 2;
                }else if(pos_down_.x < f_rect.left + ((f_rect.width / 6) * 5)){
                  ball_tmp_->speed_.x = 4;
                }else{
                  ball_tmp_->speed_.x = 6;                
                }              

              }else if((*it2)->checkCollision(pos_left_)){
                player_tmp_ = static_cast<Player*>(*it2);
                ball_tmp_->speed_.x = -8;
                ball_tmp_->speed_.y *= -1;
              }else if((*it2)->checkCollision(pos_right_)){
                player_tmp_ = static_cast<Player*>(*it2);
                ball_tmp_->speed_.x = 8;
                ball_tmp_->speed_.y *= -1;
              }
            }
          }
        }
        break;
      case Entity::kPlayer:
        break;
    }    
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
