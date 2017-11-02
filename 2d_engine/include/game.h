#ifndef __GAME_H__
#define __GAME_H__ 1

#include "game_manager.h"

class  Game{
 public:
  Game();
  void Init();
  void GameLoop();
  
  GameManager& GM = GameManager::instance();
  bool game_over; 
 private:
  Game(const Game& other){};
  void ProcessInput();
  void Update();
  void Render();
};

#endif