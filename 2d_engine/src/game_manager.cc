// Comments can be found at the header
#include "game_manager.h"

GameManager::GameManager(){
  window_size_ = new sf::Vector2u();
  window_size_->x = 800;
  window_size_->y = 800;
  window_ = Window::CreateWindow(*window_size_, "My Window");
  status_ui_ = UiStatus::kIdle;
  edit_type_ui_ = UiEditType::kNull;
  game_over_ = false;
  mouse_status_ = MouseStatus::kNothing;
  mouse_position_.x = 0;
  mouse_position_.y = 0;
  draw_origin_point_.x = 0;
  draw_origin_point_.y = 0;
  deltaClock_.restart();
  drawing_rect_ = nullptr;
  ui_is_drawing_ = 0;
  rect_selection_ = nullptr;
  label_selection_ = nullptr;
  sprite_selection_ = nullptr;
  background_selection_ = nullptr;
  wall_selection_ = nullptr;
  brick_selection_ = nullptr;
  ball_selection_ = nullptr;
  player_selection_ = nullptr;
  arial_.loadFromFile("../data/fonts/arial.ttf");
  verdana_.loadFromFile("../data/fonts/verdana.ttf");
  native_dialog_ = new Native_dialogs();

}

GameManager& GameManager::instance(){
  static GameManager* pinstance = new GameManager();
  return *pinstance;
}