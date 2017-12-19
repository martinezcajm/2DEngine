// pool.h
// Jose Maria Martinez
// Header of the functions of the pooling engine.
#ifndef __POOL_H__
#define __POOL_H__ 1

#include <vector>

#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "background.h"
#include "wall.h"
#include "brick.h"
#include "ball.h"
#include "player.h"

/** @brief Class in charge of managing the pools
*
* Singleton of pools used to reuse the diverse graphical entities of the
* application avoiding this way the destruction of objects during execution
* as much as possible
*
*/
class Pool{
 public:
  /** @brief Gets the instance of our pool
  *
  * In charge of creating our singleton of pools in case it doesn't exist
  * or return it's instance if it exists.
  *
  * @return Pool& instance of the pool
  */
  static Pool& instance();
  /** @brief Initializes the pool
  *
  * Initializes the pool creating the first instances of the elements.
  *
  * @return void
  */
  void init();
  /** @brief Frees the pull
  *
  * Frees all the elements stored in the pools.
  *
  * @return void
  */
  void free();
  /** @brief Retrieves a Rect
  *
  * Returns a Rect from the pool, if the pool doesn't have more rects it 
  * creates one using the rect factory. If the max of rects has been reached
  * it returns null ptr.
  *
  * @return Rect* pointer to rect if possible, nullptr if the maxim has been
  * reached
  */
  Rect* getRect();
  /** @brief Retrieves a Label
  *
  * Returns a Label from the pool, if the pool doesn't have more labels it 
  * creates one using the label factory. If the max of labels has been reached
  * it returns null ptr.
  *
  * @return Label* pointer to label if possible, nullptr if the maxim has been
  * reached
  */
  Label* getLabel();
  /** @brief Retrieves a Sprite
  *
  * Returns a Sprite from the pool, if the pool doesn't have more sprites it 
  * creates one using the sprite factory. If the max of sprites has been
  * reached it returns null ptr.
  *
  * @return Sprite* pointer to sprite if possible, nullptr if the maxim has 
  * been reached
  */
  Sprite* getSprite();
  /** @brief Retrieves a Background
  *
  * Returns a Background from the pool, if the pool doesn't have more 
  * backgrounds it  creates one using the background factory. If the max of 
  * backgrounds has been reached it returns null ptr.
  *
  * @return Background* pointer to background if possible, nullptr if the 
  * maxim has been reached
  */
  Background* getBackground();
  /** @brief Retrieves a Wall
  *
  * Returns a Wall from the pool, if the pool doesn't have more 
  * walls it  creates one using the wall factory. If the max of 
  * walls has been reached it returns null ptr.
  *
  * @return Wall* pointer to wall if possible, nullptr if the 
  * maxim has been reached
  */
  Wall* getWall();
  /** @brief Retrieves a Brick
  *
  * Returns a Brick from the pool, if the pool doesn't have more 
  * bricks it  creates one using the brick factory. If the max of 
  * bricks has been reached it returns null ptr.
  *
  * @return Brick* pointer to brick if possible, nullptr if the 
  * maxim has been reached
  */
  Brick* getBrick();
  /** @brief Retrieves a Brick
  *
  * Returns a Brick from the pool, if the pool doesn't have more 
  * bricks it  creates one using the brick factory. If the max of 
  * bricks has been reached it returns null ptr.
  *
  * @return Brick* pointer to brick if possible, nullptr if the 
  * maxim has been reached
  */
  Ball* getBall();
  /** @brief Retrieves a Player
  *
  * Returns a Player from the pool, if the pool doesn't have more 
  * players it  creates one using the player factory. If the max of 
  * players has been reached it returns null ptr.
  *
  * @return Player* pointer to player if possible, nullptr if the 
  * maxim has been reached
  */
  Player* getPlayer();
  /** @brief Adds an existing rect to the pool
  *
  * Recieves an existing rect and resets it's value using the unuse function of
  * rect
  *
  * @return void
  */
  void returnRect(Rect &rect);
  /** @brief Adds an existing label to the pool
  *
  * Recieves an existing label and resets it's value using the unuse function 
  * of label
  *
  * @return void
  */
  void returnLabel(Label &label);
  /** @brief Adds an existing sprite to the pool
  *
  * Recieves an existing sprite and resets it's value using the unuse function 
  * of sprite
  *
  * @return void
  */
  void returnSprite(Sprite &sprite);
  /** @brief Adds an existing background to the pool
  *
  * Recieves an existing background and resets it's value using the unuse 
  * function of background
  *
  * @return void
  */
  void returnBackground(Background &background);
  /** @brief Adds an existing wall to the pool
  *
  * Recieves an existing wall and resets it's value using the unuse 
  * function of wall
  *
  * @return void
  */
  void returnWall(Wall &wall);
  /** @brief Adds an existing brick to the pool
  *
  * Recieves an existing brick and resets it's value using the unuse 
  * function of brick
  *
  * @return void
  */
  void returnBrick(Brick &brick);
  /** @brief Adds an existing ball to the pool
  *
  * Recieves an existing ball and resets it's value using the unuse 
  * function of ball
  *
  * @return void
  */
  void returnBall(Ball &ball);
  /** @brief Adds an existing Player to the pool
  *
  * Recieves an existing player and resets it's value using the unuse 
  * function of player
  *
  * @return void
  */
  void returnPlayer(Player &player);


  std::vector<Rect*> rect_pool_;
  std::vector<Label*> label_pool_;
  std::vector<Sprite*> sprite_pool_;
  std::vector<Background*> bg_pool_;
  std::vector<Wall*> wall_pool_;
  std::vector<Brick*> brick_pool_;
  std::vector<Ball*> ball_pool_;
  std::vector<Player*> player_pool_;

 private:
  /** @brief Pool constructor
  *
  * In charge of creating the first instance that will use the singleton
  *
  * @return *Pool
  */
  Pool();
  /** @brief Pool copy constructor
  *
  * Pool copy constructor without anything to disable it.
  *
  * @return *Pool
  */
  Pool(const Pool& o){};
  /** @brief Pool destructor
  *
  * Destructor of class pool private so the pool can't be destroyed
  */
  ~Pool();

  //Number of entities that will create the pool at start of each type
  static const uint32_t start_rects_ = 20;
  static const uint32_t start_labels_ = 10;
  static const uint32_t start_sprites_ = 30;
  static const uint32_t start_backgrounds_ = 5;
  static const uint32_t start_walls_ = 5;
  static const uint32_t start_bricks_ = 20;
  static const uint32_t start_balls_ = 1;
  static const uint32_t start_players_ = 1;
};

#endif