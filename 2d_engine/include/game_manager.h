#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__ 1

#include "window.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"

class GameManager {
private:
  GameManager();
  GameManager(const GameManager& other){};
  ~GameManager();

public:
  static GameManager& instance();

  bool game_over;
  Window *window;
  sf::Vector2u *window_size;
  Rect *rect_test;
  Label *label_test;
  Sprite *sprite_test;
  sf::Texture *texture;
};

#endif