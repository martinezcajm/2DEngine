#ifndef __GAME_H__
#define __GAME_H__ 1

#include "game_manager.h"
#include "pool.h"

  /** @Brief Main class of the editor
  *
  * This class contains the main bucle of the game and editor
  *
  */
class  Game{
 public:
  /** @Contruct the game
  *
  * Constructor of the game
  *
  * @return void
  */
  Game();
  /** @Destruct the game
  *
  * Destructor of the game
  *
  * @return void
  */
  ~Game();

  /** @Initializes the game
  *
  * Initializes the necesary objects for the game.
  *
  * @return void
  */
  void init();
  /** @Check the inputs
  *
  * Check the inputs and change the game stats for do the uptade.
  *
  * @return void
  */
  void processInput();
  /** @Update the game
  *
  * Update entitites and the game state.
  *
  * @return void
  */
  void updateGame();
  /** @Render the game entities
  *
  * Draw all the entities of the game
  *
  * @return void
  */
  void renderGame();
  /** @Update the game
  *
  * Update entitites and the game state.
  *
  * @return void
  */
  void updateEditor();
  /** @Render the game entities
  *
  * Draw all the entities of the game and the UI of the editor
  *
  * @return void
  */
  void renderEditor();
  /** @Process the game loop
  *
  * Process the game loop.
  *
  * @return void
  */
  void mainLoop();
  /** @Finis the game
  *
  * Free the memoryof the elements of the game
  *
  * @return void
  */
  void finish();

  /////// UI Functions ///////

  /** @Renders the UI
  *
  * Function in charge of rendering the UI
  *
  * @return void
  */
  void renderUI();
  /** @Loads the edit values of Drawable entity
  *
  * Loads the edit values of Drawable entity: transformations, color, 
  * position...
  *
  * @return void
  * @param reference to the drawable entity whose values will be loaded at the 
  * UI
  */
  void UiLoadCommonValuesEdit(DrawableEntity &d_entity);
  /** @Loads the edit values of Rect entity
  *
  * Loads the edit values of Rect entity: fill color, is_solid, size...
  *
  * @return void
  * @param reference to the rect whose values will be loaded at the UI
  * 
  */
  void UiLoadRectValuesEdit(Rect &rect);
  /** @Loads the edit values of Label entity
  *
  * Loads the edit values of Label entity: text, font_size...
  *
  * @return void
  * @param reference to the label whose values will be loaded at the UI
  * 
  */
  void UiLoadLabelValuesEdit(Label &label);
  /** @Loads the edit values of Background entity
  *
  * Loads the edit values of Background entity: speed, vertical movememnt, 
  * horizaontal_movement...
  *
  * @return void
  * @param reference to the background whose values will be loaded at the UI
  * 
  */
  void UiLoadBackgroundValuesEdit(Background &bg);
  /** @Loads the mode menu of the UI
  *
  * Loads the mode menu with the different buttons to chose in which mode is
  * working the UI
  *
  * @return void
  * 
  */
  void UiLoadMenu();
  /** @Loads the game mode menu
  *
  * Only part of the UI that will be shown in game mode, this allows us to
  * change between game mode and edit mode
  *
  * @return void
  * 
  */
  void UiStartGameMenu();
  
  GameManager& GM = GameManager::instance();
  Pool& POOL = Pool::instance();
  bool game_over_;
  char const *kFilterPatternsJson[1] = { "*.json" };
  char const *kFilterPatternsImage[3] = { "*.png","*.jpeg", "*.jpg" };
 private:
  Game(const Game& other){};
};

#endif