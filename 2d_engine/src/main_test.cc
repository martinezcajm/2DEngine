#include "game.h"

int main()
{
  Game* game = new Game();
  game->Init();
  game->GameLoop();

  delete game;
}