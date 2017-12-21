// Author: Sebastián Adrover Pedrosa
#ifndef __GAME_H__
#define __GAME_H__ 1

#include "game_manager.h"
#include "pool.h"
#include "user_interface.h"

  /** @Brief Main class of the editor
  *
  * This class contains the main bucle of the game and editor
  *
  */
class  Game{
 public:
  /** @brief Contruct the game
  *
  * Constructor of the game
  *
  * @return void
  */
  Game();
  /** @brief Destruct the game
  *
  * Destructor of the game
  *
  * @return void
  */
  ~Game();

  /** @brief Initializes the game
  *
  * Initializes the necesary objects for the game.
  *
  * @return void
  */
  void init();
  /** @brief Check the inputs
  *
  * Check the inputs and change the game stats for do the uptade.
  *
  * @return void
  */
  void processInput();
  /** @brief Update the game
  *
  * Update entitites and the game state.
  *
  * @return void
  */
  void updateGame();
  /** @brief Render the game entities
  *
  * Draw all the entities of the game
  *
  * @return void
  */
  void renderGame();
  /** @brief Update the game
  *
  * Update entitites and the game state.
  *
  * @return void
  */
  void updateEditor();
  /** @brief Render the game entities
  *
  * Draw all the entities of the game and the UI of the editor
  *
  * @return void
  */
  void renderEditor();
  /** @brief Process the game loop
  *
  * Process the game loop.
  *
  * @return void
  */
  void mainLoop();
  /** @brief Finish the game
  *
  * Free the memoryof the elements of the game
  *
  * @return void
  */
  void finish();
  
  GameManager& GM = GameManager::instance();
  Pool& POOL = Pool::instance();
  UserInterface *ui_;
  Scene *scene_;
  char const *kFilterPatternsJson[1] = { "*.json" };
  char const *kFilterPatternsImage[3] = { "*.png","*.jpeg", "*.jpg" };
 private:
  Game(const Game& other){};
};

#endif