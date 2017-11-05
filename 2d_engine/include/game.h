#ifndef __GAME_H__
#define __GAME_H__ 1

#include "game_manager.h"

class  Game{
 public:
  Game();
  void init();
  void gameLoop();
  
  GameManager& GM = GameManager::instance();
  bool game_over; 
 private:
  Game(const Game& other){};
  void processInput();
  void update();
  void render();
};

#endif