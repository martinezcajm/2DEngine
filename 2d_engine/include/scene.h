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


  //// DrawableEntity ////
  /** @Add a DrawableEntity to the scene
  *
  *  Add a DrawableEntity in the mappings that form the scene
  *
  * @return void
  * @param drawable_entity Reference of the DrawableEntity to add
  */
  void addDrawableEntity(DrawableEntity& drawable_entity);
  /** @Get a DrawableEntity from the scene
  *
  *  Returns the DrawableEntity with the specified id from the scene
  *
  * @return DrawableEntity Return the DrawableEntity with the id specified
  * @param drawable_entity_id Id of the DrawableEntity to return
  */
  DrawableEntity* getDrawableEntity(const uint32_t drawable_entity_id);
  /** @Remove a DrawableEntity of the scene
  *
  *  Remove the DrawableEntity with the specified id of the scene
  *
  * @return void
  * @param drawable_entity_id Id of the DrawableEntity to remove
  */
  void removeDrawableEntity(const uint32_t drawable_entity_id);
  /** @Change the z-order of a DrawableEntity of the scene
  *
  *  Change the z-order of a DrawableEntity of the scene.
  *
  * @return void
  * @param drawable_entity_id Id of the DrawableEntity to change the z-order
  * @param newZOrder New z-order of the DrawableEntity
  */
  void changeZOrderDrawableEntity(const uint32_t drawable_entity_id, 
    const int32_t newZOrder);


  
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
  */
  uint32_t checkCollision(sf::Vector2f& position);
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

  std::unordered_map<uint32_t, DrawableEntity*> map_drawable_entity_;
  std::map<int32_t, std::unordered_map<uint32_t,DrawableEntity*>> 
    z_order_map_drawable_entity_;

  std::set<int32_t> z_order_levels;

  Pool& POOL = Pool::instance();
  Scene(const Scene& other){};
};

#endif