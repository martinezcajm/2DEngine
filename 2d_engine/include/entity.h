#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <cstdint>

/** @entity
*
* Atomic class of the elements of our engine.
*
*/
class Entity{
 public:
  /** @Entity constructor
  *
  * Base constructor of entity
  *
  * @return *Entity
  */
  Entity();
  /** @Entity copy constructor
  *
  * Personal Entity copy constructor taking into account the id.
  *
  * @return *Entity
  */
  Entity(const Entity& o);
  /** @Initializes the Entity
  *
  * Initializes an entity with a tag
  *
  * @return void
  * @param tag unsigned int used to group entities
  */
  void init(const uint32_t tag);
  /** @Initializes the Entity
  *
  * Initializes an entity with default values
  *
  * @return void
  * @param tag unsigned int used to group entities
  */
  void init();
  uint32_t id();
  /** @Resets the values of the entity
  *
  * Sets the attributes of the object to return it to a pool and being able
  * to reuse it later.
  *
  * @return void
  */
  void unuse();
  //Data members
  uint32_t tag_;
  uint8_t active_;

 private:
  static uint32_t total_ids_;
  uint32_t id_;
};

#endif