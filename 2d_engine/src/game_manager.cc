#include "game_manager.h"

GameManager::GameManager(){
  window_size_ = new sf::Vector2u();
  window_size_->x = 800;
  window_size_->y = 800;
  window_ = Window::CreateWindow(*window_size_, "My Window");
  status_ui_ = UiStatus::kIdle;
  edit_type_ui_ = UiEditType::kNull;
  game_over_ = false;
  draw_status_ui_ = UiDrawStatus::kNotDrawing;
  click_ = 0;
  mouse_position_.x = 0;
  mouse_position_.y = 0;
}

GameManager& GameManager::instance(){
  static GameManager* pinstance = new GameManager();
  return *pinstance;
}