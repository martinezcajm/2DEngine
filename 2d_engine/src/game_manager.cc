// Comments can be found at the header
#include "game_manager.h"

GameManager::GameManager(){
  window_size_ = new sf::Vector2u();
  window_size_->x = 800;
  window_size_->y = 800;
  window_ = Window::CreateWindow(*window_size_, "My Window");
  //status_ui_ = UiStatus::kIdle;
  //edit_type_ui_ = UiEditType::kNull;
  game_over_ = false;
  mouse_status_ = MouseStatus::kNothing;
  //mouse_position_.x = 0;
  //mouse_position_.y = 0;
  //draw_origin_point_.x = 0;
  //draw_origin_point_.y = 0;
  deltaClock_.restart();
  //drawing_rect_ = nullptr;
  //ui_is_drawing_ = 0;
  arial_.loadFromFile("../data/fonts/arial.ttf");
  verdana_.loadFromFile("../data/fonts/verdana.ttf");
  native_dialog_ = new Native_dialogs();

  // Default GameParams
  lives_ = 3;
  score_ = 0;
  hight_score_ = 0;

  isBallInMovement_ = 1;
  player_speed_ = 5;
  player1Left_ = 0;
  player1Right_ = 0;
}

GameManager& GameManager::instance(){
  static GameManager* pinstance = new GameManager();
  return *pinstance;
}