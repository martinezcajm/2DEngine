#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__ 1

#include "window.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "scene.h"

typedef enum UiStatus
{
  kIdle,
  kDraw,
  kSelection,
  kWrite
} UiStatus;

typedef enum UiEditType
{
  kNull,
  kRect,
  kLabel,
  kSprite,
  kBackground
} UiEditType;

typedef enum UiDrawStatus
{
  kNotDrawing,
  kStartDrawing,
  kDrawing,
  kStopDrawing
} UiDrawStatus;

class GameManager {
private:
  GameManager();
  GameManager(const GameManager& other){};
  ~GameManager(){};

public:
  static GameManager& instance();

  uint8_t click_; // indicates if there has been a click
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
  sf::Vector2f mouse_position_;
  UiStatus status_ui_;
  UiEditType edit_type_ui_;
  UiDrawStatus draw_status_ui_;
};

#endif