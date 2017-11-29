// user_interface.h
// Jose Maria Martinez
// Header of the functions to control the user interface of the app
#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__ 1

#include "game_manager.h"
#include "pool.h"

class UserInterface{
 public:
  /** @brief Contructor of the UI
  *
  * Contructor of the UI
  *
  * @return *UserInterface
  */
  UserInterface();
  /** @brief Destroys the UI
  *
  * Destructor of the UI
  *
  * @return void
  */
  ~UserInterface();
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
 private:
  char const *kFilterPatternsJson[1] = { "*.json" };
  char const *kFilterPatternsImage[3] = { "*.png","*.jpeg", "*.jpg" };
};

#endif