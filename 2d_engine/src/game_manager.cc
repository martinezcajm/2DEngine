// Author: Sebastián Adrover Pedrosa
// Comments can be found at the header
#include "game_manager.h"

GameManager::GameManager(){
  // ByDefault parameters
  window_size_ = new sf::Vector2u();
  window_size_->x = 800;
  window_size_->y = 800;
  window_ = Window::CreateWindow(*window_size_, "My Window");
  
  close_game_ = false;
  mouse_status_ = MouseStatus::kNothing;
  
  deltaClock_.restart();
  
  arial_.loadFromFile("../data/fonts/arial.ttf");
  verdana_.loadFromFile("../data/fonts/verdana.ttf");
  native_dialog_ = new Native_dialogs();

  // Default GameParams
  lives_ = 3;
  score_ = 0;
  highest_score_ = 0;

  is_ball_in_movement_ = 0;
  game_over_ = 0;
  new_game_ = 0;
  player_speed_ = 5;
  player1Left_ = 0;
  player1Right_ = 0;
}

GameManager& GameManager::instance(){
  static GameManager* pinstance = new GameManager();
  return *pinstance;
}