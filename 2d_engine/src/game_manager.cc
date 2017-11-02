#include "game_manager.h"

GameManager::GameManager(){
  window = new Window();
  window_size = new sf::Vector2u();
  window_size->x = 800;
  window_size->y = 800;
  window->CreateWindow(*window_size, "My Window");
  game_over = false;


  
}

GameManager::~GameManager(){
  //delete objects
}

GameManager& GameManager::instance(){
  static GameManager* pinstance = new GameManager();
  return *pinstance;
}