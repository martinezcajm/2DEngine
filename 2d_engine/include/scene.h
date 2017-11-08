#ifndef __SCENE_H__
#define __SCENE_H__ 1

#include "string.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "background.h"
#include "pool.h"
#include <set>
#include <list>
#include <unordered_map>
#include <map>

/** @Brief Class that create and manage a scene
*
* This class create and manage the scene and all the elements that form it.
*
*/
class Scene{
 public:
  Scene();
  ~Scene();

  /** @Clean the scene
  *
  *  Clean all maps of the scene and return the elements to the Pool
  *
  * @return void
  */
  void cleanScene();
  
  /** @Load a scene
  *
  *  Load a scene from a file with format json. Put to the labels the font of 
  *  the parameter.
  *
  * @return void
  * @param scene_path Path of the scene to load
  * @param font Font to put in the labels
  */
  void loadScene(const std::string scene_path, const sf::Font& font);
  
  /** @Save a scene
  *
  *  Save a scene in a file with format json.
  *
  * @return void
  * @param scene_path Path of the scene to load
  * @param font Font to put in the labels
  */
  void saveScene(const std::string scene_path);

  //// BACKGROUND ////
  /** @Add a Background to the scene
  *
  *  Add a Background in the mappings that form the scene
  *
  * @return void
  * @param background Reference of the Background to add
  */
  void addBackground(Background& background);
  /** @Get a Background from the scene
  *
  *  Returns the Background with the specified id from the scene
  *
  * @return Background Return the Background with the id specified
  * @param background_id Id of the Background to return
  */
  Background* getBackground(const uint32_t background_id);
  /** @Remove a Background of the scene
  *
  *  Remove the Background with the specified id of the scene
  *
  * @return void
  * @param background_id Id of the Background to remove
  */
  void removeBackground(const uint32_t background_id);
  /** @Change the z-order of a Background of the scene
  *
  *  Change the z-order of a Background of the scene.
  *
  * @return void
  * @param background_id Id of the Background to change the z-order
  * @param newZOrder New z-order of the Background
  */
  void changeZOrderBackground(const uint32_t background_id, 
    const int32_t newZOrder);

  //// RECT ////
  /** @Add a Rect to the scene
  *
  *  Add a Rect in the mappings that form the scene
  *
  * @return void
  * @param rect Reference of the Rect to add
  */
  void addRect(Rect& rect);
  /** @Get a Rect from the scene
  *
  *  Returns the Rect with the specified id from the scene
  *
  * @return Rect Return the Rect with the id specified
  * @param rect_id Id of the Rect to return
  */
  Rect* getRect(const uint32_t rect_id);
  /** @Remove a Rect of the scene
  *
  *  Remove the Rect with the specified id of the scene
  *
  * @return void
  * @param rect_id Id of the Rect to remove
  */
  void removeRect(const uint32_t rect_id);
  /** @Change the z-order of a Rect of the scene
  *
  *  Change the z-order of a Rect of the scene.
  *
  * @return void
  * @param rect_id Id of the Rect to change the z-order
  * @param newZOrder New z-order of the Rect
  */
  void changeZOrderRect(const uint32_t rect_id, const int32_t newZOrder);
  
  //// LABEL ////
  /** @Add a Label to the scene
  *
  *  Add a Label in the mappings that form the scene
  *
  * @return void
  * @param label Reference of the Label to add
  */
  void addLabel(Label& label);
  /** @Get a Label from the scene
  *
  *  Returns the Label with the specified id from the scene
  *
  * @return Label Return the Label with the id specified
  * @param label_id Id of the Label to return
  */
  Label* getLabel(const uint32_t label_id);
  /** @Remove a Label of the scene
  *
  *  Remove the Label with the specified id of the scene
  *
  * @return void
  * @param label_id Id of the Label to remove
  */
  void removeLabel(const uint32_t label_id);
  /** @Change the z-order of a Label of the scene
  *
  *  Change the z-order of a Label of the scene.
  *
  * @return void
  * @param label_id Id of the Label to change the z-order
  * @param newZOrder New z-order of the Label
  */
  void changeZOrderLabel(const uint32_t label_id, const int32_t newZOrder);

  //// SPRITE ////
  /** @Add a Sprite to the scene
  *
  *  Add a Sprite in the mappings that form the scene
  *
  * @return void
  * @param sprite Reference of the Sprite to add
  */
  void addSprite(Sprite& sprite);
  /** @Get a Sprite from the scene
  *
  *  Returns the Sprite with the specified id from the scene
  *
  * @return Sprite Return the Sprite with the id specified
  * @param sprite_id Id of the Sprite to return
  */
  Sprite* getSprite(const uint32_t sprite_id);
  /** @Remove a Sprite of the scene
  *
  *  Remove the Sprite with the specified id of the scene
  *
  * @return void
  * @param sprite_id Id of the Sprite to remove
  */
  void removeSprite(const uint32_t sprite_id);
  /** @Change the z-order of a Sprite of the scene
  *
  *  Change the z-order of a Sprite of the scene.
  *
  * @return void
  * @param sprite_id Id of the Sprite to change the z-order
  * @param newZOrder New z-order of the Sprite
  */
  void changeZOrderSprite(const uint32_t sprite_id, const int32_t newZOrder);
  
  /// Texture ///
  /** @Add a Texture to the scene
  *
  *  Add a Texture in the mappings that form the scene
  *
  * @return void
  * @param sprite Reference of the Texture to add
  * @param texture_path Path where is the texture file
  */
  void addTexture(sf::Texture& texture, const std::string texture_path);
  /** @Get a Texture from the scene
  *
  *  Returns the Texture with the specified path from the scene
  *
  * @return sf::Texture Return the texture with the path specified
  * @param texture_path Path of the Texture to return
  */
  sf::Texture* getTexture(const std::string texture_path);
  /** @Remove a Texture of the scene
  *
  *  Remove the Texture with the specified path of the scene
  *
  * @return void
  * @param texture_path Path of the Texture to remove
  */
  void removeTexture(const std::string texture_path);

  /** @Check if some element collision with a point
  *
  *  Check if some element of the scene have a colision with a point specified
  *  in the parameters
  *
  * @return uint32_t Return the id of the first element that have a collision.
  *  Return 0 if any element have collision.
  * @param position The point to check the collision
  * @param type The typeof element that colision. 0 - No colision, 
  *  1 - Background, 2 - Rect, 3 - Label, 4 - Sprite
  */
  uint32_t checkCollision(sf::Vector2f& position, uint8_t *type);
  /** @Get a list of entities with a specific tag
  *
  *  Return the entities with the tag specified in params
  *
  * @return list<DrawableEntity*> Return the list of DrawableEntity
  * @param tag Tag to seach
  */
  std::list<DrawableEntity*> getDrawableEntitiesByTag(const uint32_t tag);
  /** @Draw all elemnts of the scene
  *
  *  Draw all elemnts of the scene
  *
  * @return void
  */
  void drawScene();
  /** @Update the elements of the scene
  *
  *  Call to Update of the all elements of the scene
  *
  * @return void
  * @param texture_path Path of the Texture to remove
  */
  void update();

 private:
  std::unordered_map<std::string, sf::Texture*> map_texture_;
  
  std::unordered_map<uint32_t, Rect*> map_rect_;
  std::map<int32_t, std::unordered_map<uint32_t, Rect*>> z_order_map_rect_;

  std::unordered_map<uint32_t, Label*> map_label_;
  std::map<int32_t, std::unordered_map<uint32_t, Label*>> z_order_map_label_;
  
  std::unordered_map<uint32_t, Sprite*> map_sprite_;
  std::map<int32_t, std::unordered_map<uint32_t, Sprite*>> 
    z_order_map_sprite_;
  
  std::unordered_map<uint32_t, Background*> map_background_;
  std::map<int32_t, std::unordered_map<uint32_t, Background*>> 
    z_order_map_background_;

  std::set<int32_t> z_order_levels;

  Pool& POOL = Pool::instance();
  Scene(const Scene& other){};
};

#endif