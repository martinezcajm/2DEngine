#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <cstdint>

class Entity{
 public:
  //Methods
  Entity();
  Entity(const Entity& o);
  void init(const uint32_t tag);
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