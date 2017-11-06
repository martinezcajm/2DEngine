#ifndef __SCENE_H__
#define __SCENE_H__ 1

#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "background.h"
#include<set>
#include <unordered_map>
#include <map>

class Scene{
 public:
  Scene();
  ~Scene();

  void loadScene();
  void saveScene();

  //// BACKGROUND ////
  void addBackground(Background& background);
  Background* getBackground(uint32_t background_id);
  void removeBackground(uint32_t background_id);

  //// RECT ////
  void addRect(Rect& rect);
  Rect* getRect(uint32_t rect_id);
  void removeRect(uint32_t rect_id);
  
  //// LABEL ////
  void addLabel(Label& label);
  Label* getLabel(uint32_t label_id);
  void removeLabel(uint32_t label_id);

  //// SPRITE ////
  void addSprite(Sprite& sprite);
  Sprite* getSprite(uint32_t sprite_id);
  void removeSprite(uint32_t sprite_id);
  
  /// Texture ///
  void addTexture(sf::Texture& texture, uint32_t texture_id);
  sf::Texture* getTexture(uint32_t texture_id);
  void removeTexture(uint32_t texture_id);

  // 0 - No colision
  // 1 - Background
  // 2 - Rect
  // 3 - Label
  // 4 - Sprite
  DrawableEntity *checkColision(sf::Vector2f& position, uint8_t *type);

  void drawScene();

  std::unordered_map<uint32_t, sf::Texture*> map_texture_;
  
  std::unordered_map<uint32_t, Rect*> map_rect_;
  std::map<uint32_t, std::unordered_map<uint32_t, Rect*>> z_order_map_rect_;

  std::unordered_map<uint32_t, Label*> map_label_;
  std::map<uint32_t, std::unordered_map<uint32_t, Label*>> z_order_map_label_;
  
  std::unordered_map<uint32_t, Sprite*> map_sprite_;
  std::map<uint32_t, std::unordered_map<uint32_t, Sprite*>> 
    z_order_map_sprite_;
  
  std::unordered_map<uint32_t, Background*> map_background_;
  std::map<uint32_t, std::unordered_map<uint32_t, Background*>> 
    z_order_map_background_;

  std::set<uint32_t> z_order_levels;
 private:
  Scene(const Scene& other){};
  
};

#endif