#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__ 1

#include "window.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "scene.h"
#include "native_dialogs.h"

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
  Native_dialogs *native_dialog_;
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
  sf::Vector2f draw_origin_point_; //position for drawing rects 
  sf::Clock deltaClock_; //delta clock used for the UI updates
  Rect* drawing_rect_; //pointer to a rect that is being drawn at screen
  UiStatus status_ui_; //active mode of UI
  UiEditType edit_type_ui_; //edition type of UI
  MouseStatus mouse_status_; //mouse status for the UI
  //Selection items for UI
  uint8_t selected_type_;
  uint32_t selected_id_;
  Rect *rect_selection_;
  Label *label_selection_;
  Sprite *sprite_selection_;
  Background *background_selection_;
  //Fonts supported by the app 
  //TODO charge them through an ini file
  sf::Font arial_;
  sf::Font verdana_;
};

#endif