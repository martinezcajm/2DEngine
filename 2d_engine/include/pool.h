#ifndef __POOL_H__
#define __POOL_H__ 1

#include <vector>

#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "background.h"

/** @Class in charge of managing the pools
*
* Singleton of pools used to reuse the diverse graphical entities of the
* application avoiding this way the destruction of objects during execution
* as much as possible
*
*/
class Pool{
 public:
  /** @Gets the instance of our pool
  *
  * In charge of creating our singleton of pools in case it doesn't exist
  * or return it's instance if it exists.
  *
  * @return Pool& instance of the pool
  */
  static Pool& instance();
  /** @Initializes the pool
  *
  * Initializes the pool creating the first instances of the elements.
  *
  * @return void
  */
  void init();
  /** @Frees the pull
  *
  * Frees all the elements stored in the pools.
  *
  * @return void
  */
  void free();
  /** @Retrieves a Rect
  *
  * Returns a Rect from the pool, if the pool doesn't have more rects it 
  * creates one using the rect factory. If the max of rects has been reached
  * it returns null ptr.
  *
  * @return Rect* pointer to rect if possible, nullptr if the maxim has been
  * reached
  */
  Rect* getRect();
  /** @Retrieves a Label
  *
  * Returns a Label from the pool, if the pool doesn't have more labels it 
  * creates one using the label factory. If the max of labels has been reached
  * it returns null ptr.
  *
  * @return Label* pointer to label if possible, nullptr if the maxim has been
  * reached
  */
  Label* getLabel();
  /** @Retrieves a Sprite
  *
  * Returns a Sprite from the pool, if the pool doesn't have more sprites it 
  * creates one using the sprite factory. If the max of sprites has been
  * reached it returns null ptr.
  *
  * @return Sprite* pointer to sprite if possible, nullptr if the maxim has 
  * been reached
  */
  Sprite* getSprite();
  /** @Retrieves a Background
  *
  * Returns a Background from the pool, if the pool doesn't have more 
  * backgrounds it  creates one using the background factory. If the max of 
  * backgrounds has been reached it returns null ptr.
  *
  * @return Background* pointer to background if possible, nullptr if the 
  * maxim has been reached
  */
  Background* getBackground();
  /** @Adds an existing rect to the pool
  *
  * Recieves an existing rect and resets it's value using the unuse function of
  * rect
  *
  * @return void
  */
  void returnRect(Rect &rect);
  /** @Adds an existing label to the pool
  *
  * Recieves an existing label and resets it's value using the unuse function 
  * of label
  *
  * @return void
  */
  void returnLabel(Label &label);
  /** @Adds an existing sprite to the pool
  *
  * Recieves an existing sprite and resets it's value using the unuse function 
  * of sprite
  *
  * @return void
  */
  void returnSprite(Sprite &sprite);
  /** @Adds an existing background to the pool
  *
  * Recieves an existing background and resets it's value using the unuse 
  * function of background
  *
  * @return void
  */
  void returnBackground(Background &background);


  std::vector<Rect*> rect_pool_;
  std::vector<Label*> label_pool_;
  std::vector<Sprite*> sprite_pool_;
  std::vector<Background*> bg_pool_;

 private:
  /** @Pool constructor
  *
  * In charge of creating the first instance that will use the singleton
  *
  * @return *Pool
  */
  Pool();
  /** @Pool copy constructor
  *
  * Pool copy constructor without anything to disable it.
  *
  * @return *Pool
  */
  Pool(const Pool& o){};
  /** @Pool destructor
  *
  * Destructor of class pool private so the pool can't be destroyed
  */
  ~Pool();

  //Number of entities that will create the pool at start of each type
  static const uint32_t start_rects_ = 20;
  static const uint32_t start_labels_ = 10;
  static const uint32_t start_sprites_ = 30;
  static const uint32_t start_backgrounds_ = 5;
};

#endif