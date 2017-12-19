// entity.h
// Jose Maria Martinez
// Header of the functions of the entity interface.
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
  enum Type {
    kRect = 0,
    kBackground = 1,
    kLabel = 2,
    kSprite = 3
  };
  /** @Entity constructor
  *
  * Base constructor of entity
  *
  * @return *Entity
  */
  Entity();
  /** @Destroys the Entity
  *
  * Destructor of the entity
  *
  * @return void
  */
  virtual ~Entity() = 0 {};
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
  /** @brief Getter of the id
  *
  * Returns the value of the id
  *
  * @return uint32_t id of the entity
  */
  uint32_t id();
  /** @Resets the values of the entity
  *
  * Sets the attributes of the object to return it to a pool and being able
  * to reuse it later. 
  *
  * @return void
  */
  virtual void unuse();
  /** @brief Getter of the type
  *
  * Returns the type of the entity
  *
  * @return Type type of the entity
  */
  Type type();

  //Data members
  uint32_t tag_;
  uint8_t active_;
 protected:
  Type type_;
 private:
  static uint32_t total_ids_;
  uint32_t id_;
};

#endif