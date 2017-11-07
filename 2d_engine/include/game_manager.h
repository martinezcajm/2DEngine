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

typedef enum MouseStatus
{
  kNothing,
  kPressed,
  kReleased
} MouseStatus;

class GameManager {
private:
  GameManager();
  GameManager(const GameManager& other){};
  ~GameManager(){};

public:
  static GameManager& instance();

  uint8_t ui_is_drawing_;
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
  sf::Vector2f draw_origin_point_;
  sf::Clock deltaClock_;
  Rect* drawing_rect_;
  UiStatus status_ui_;
  UiEditType edit_type_ui_;
  UiDrawStatus draw_status_ui_;
  MouseStatus mouse_status_;
  //Selection items for UI
  uint8_t selected_type_;
  uint32_t selected_id_;
  Rect *rect_selection_;
  Label *label_selection_;
  Sprite *sprite_selection_;
  Background *background_selection_;
};

#endif