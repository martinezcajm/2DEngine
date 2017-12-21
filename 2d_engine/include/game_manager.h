// Author: Sebastián Adrover Pedrosa
#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__ 1

#include "window.h"
#include "native_dialogs.h"


typedef enum MouseStatus
{
  kNothing,
  kPressed,
  kReleased
} MouseStatus;

class GameManager {
private:
  /** @brief Contruct the GameManager
  *
  * Constructor of the GameManager
  *
  * @return void
  */
  GameManager();
  GameManager(const GameManager& other){};
  /** @brief Destruct the GameManager
  *
  * Destructor of the GameManager
  *
  * @return void
  */
  ~GameManager(){};

public:
  /** @brief Gets the instance of our GameManager
  *
  * In charge of creating our GameManager singleton in case it doesn't exist
  * or return it's instance if it exists.
  *
  * @return GameManager& instance
  */
  static GameManager& instance();

  // Elements of the game
  uint8_t close_game_;
  uint8_t is_editor_;
  Window *window_;
  sf::Vector2u *window_size_;
  //Scene *scene_;
  Native_dialogs *native_dialog_;
  
  // Status update for UI
  //uint8_t ui_is_drawing_;
  //sf::Vector2f mouse_position_;
  //sf::Vector2f draw_origin_point_; //position for drawing rects 
  sf::Clock deltaClock_; //delta clock used for the UI updates
  //Rect* drawing_rect_; //pointer to a rect that is being drawn at screen
  //UiStatus status_ui_; //active mode of UI
  //UiEditType edit_type_ui_; //edition type of UI
  MouseStatus mouse_status_; //mouse status for the UI
  
  //Selection items for UI
  uint8_t selected_type_;
  uint32_t selected_id_;
  
  //Fonts supported by the app 
  //TODO charge them through an ini file
  sf::Font arial_;
  sf::Font verdana_;
  //tag that is related to a selected item
  static const uint32_t selected_item_tag_ = 1;
  
  // Arcanoid Status
  uint8_t player1Left_;
  uint8_t player1Right_;
  uint8_t new_game_;
  uint8_t game_over_;

  uint8_t is_ball_in_movement_;
  int player_speed_;
  int lives_;
  int score_;
  int highest_score_;
};

#endif