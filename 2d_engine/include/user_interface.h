// user_interface.h
// Jose Maria Martinez
// Header of the functions to control the user interface of the app
#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__ 1

#include "game_manager.h"
#include "pool.h"



class UserInterface{
 public:
  enum UiStatus
  {
    kIdle,
    kDraw,
    kSelection,
    kWrite,
    kMultiselect
  };

  enum UiEditType
  {
    kNull,
    kRect,
    kLabel,
    kSprite,
    kBackground,
    kMulti,
    kWall,
    kBrick,
    kBall,
    kPlayer
  };

  /*enum MouseStatus
  {
    kNothing,
    kPressed,
    kReleased
  };*/
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
  /** @brief Inits the user interface
  *
  * Function in charge of initializing all the necesary to use the user
  * interface
  *
  * @return void
  * @param window window to which the UI will be binded.
  */
  void init(sf::RenderWindow &window);
  /** @brief Renders the UI
  *
  * Function in charge of rendering the UI
  *
  * @return void
  * @param window window to which the UI will be drawn.
  */
  void renderUI(sf::RenderWindow &window);
  /** @brief Checks the inputs
  *
  * Checks the inputs and updates the UI accordly.
  *
  * @return void
  * @param window sfml from which we will process the events
  * @param event 
  */
  void processInput(sf::RenderWindow &window, sf::Event &event);
  
  /** @brief Checks the inputs
  *
  * Checks the inputs and updates the UI accordly.
  *
  * @return void
  * @param window sfml from which we will process the events
  * @param event 
  */
  void update(sf::RenderWindow &window);

  /** @brief Loads the edit values of Drawable entity
  *
  * Loads the edit values of Drawable entity: transformations, color, 
  * position...
  *
  * @return void
  * @param d_entity reference to the drawable entity whose values will be
  * loaded at the UI
  */
  void UiLoadCommonValuesEdit(DrawableEntity &d_entity);
  /** @brief Loads the edit values of Rect entity
  *
  * Loads the edit values of Rect entity: fill color, is_solid, size...
  *
  * @return void
  * @param rect reference to the rect whose values will be loaded at the UI
  * 
  */
  void UiLoadRectValuesEdit(Rect &rect);
  /** @brief Loads the edit values of Label entity
  *
  * Loads the edit values of Label entity: text, font_size...
  *
  * @return void
  * @param label reference to the label whose values will be loaded at the UI
  * 
  */
  void UiLoadLabelValuesEdit(Label &label);
  /** @brief Loads the edit values of Background entity
  *
  * Loads the edit values of Background entity: speed, vertical movememnt, 
  * horizaontal_movement...
  *
  * @return void
  * @param bg reference to the background whose values will be loaded at the UI
  * 
  */
  void UiLoadBackgroundValuesEdit(Background &bg);
  /** @brief Loads the edit values of Player entity
  *
  * Loads the edit values of Player entity: speedx, speedy
  *
  * @return void
  * @param player reference to the player whose values will be loaded at the UI
  * 
  */
  void UiLoadPlayerValuesEdit(Player &player);
  /** @brief Loads the edit values of Ball entity
  *
  * Loads the edit values of Ball entity: speedx, speedy
  *
  * @return void
  * @param ball reference to the ball whose values will be loaded at the UI
  * 
  */
  void UiLoadBallValuesEdit(Ball &ball);
  /** @brief Loads the edit values of Brick entity
  *
  * Loads the edit values of Brick entity: lives
  *
  * @return void
  * @param brick reference to the brick whose values will be loaded at the UI
  * 
  */
  void UiLoadBrickValuesEdit(Brick &brick);
  /** @brief Loads the mode menu of the UI
  *
  * Loads the mode menu with the different buttons to chose in which mode is
  * working the UI
  *
  * @return void
  * 
  */
  void UiLoadMenu();
  /** @brief Loads the game mode menu
  *
  * Only part of the UI that will be shown in game mode, this allows us to
  * change between game mode and edit mode
  *
  * @return void
  * 
  */
  void UiStartGameMenu();
  /** @brief Loads texture manager menu
  *
  * Shows the textures that were created for the scene
  *
  * @return void
  * 
  */
  void UiTextureManager();

  GameManager& GM = GameManager::instance();
  Pool& POOL = Pool::instance();
  // Status update for UI
  uint8_t ui_is_drawing_;
  sf::Vector2f mouse_position_;
  sf::Vector2f draw_origin_point_; //position for drawing rects 
  sf::Clock deltaClock_; //delta clock used for the UI updates
  Rect* drawing_rect_; //pointer to a rect that is being drawn at screen
  UiStatus status_ui_; //active mode of UI
  UiEditType edit_type_ui_; //edition type of UI
  //MouseStatus mouse_status_; //mouse status for the UI
  uint8_t selected_texture_ = 1;
 private:
  char const *kFilterPatternsJson[1] = { "*.json" };
  char const *kFilterPatternsImage[3] = { "*.png","*.jpeg", "*.jpg" };
};

#endif