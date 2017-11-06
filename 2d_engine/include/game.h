#ifndef __GAME_H__
#define __GAME_H__ 1

#include "game_manager.h"

class  Game{
 public:
  Game();
  ~Game();

  void init();
  void processInput();
  void updateGame();
  void renderGame();
  void updateEditor();
  void renderEditor();
  void mainLoop();
  void finish();
  
  GameManager& GM = GameManager::instance();
  bool game_over; 
 private:
  Game(const Game& other){};
};

#endif