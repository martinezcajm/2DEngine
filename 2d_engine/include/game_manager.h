#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__ 1

#include "window.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "scene.h"

class GameManager {
private:
  GameManager();
  GameManager(const GameManager& other){};
  ~GameManager(){};

public:
  static GameManager& instance();

  uint32_t score_;
  // saveGame
  // loadGame
  
  bool game_over_;
  bool is_editor_;
  Window *window_;
  Scene *scene_;
  sf::Vector2u *window_size_;
  Rect *rect_test_;
  Label *label_test_;
  Sprite *sprite_test_;
  sf::Texture *texture_;
};

#endif