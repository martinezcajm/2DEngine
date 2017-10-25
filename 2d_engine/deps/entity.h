#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <cstdint>

class Entity{
 public:
  //Methods
  Entity();
  void init(uint32_t tag);
  void init();
  uint32_t id();
  //Data members
  uint32_t tag_;
  uint8_t active_;
  
//TODO Copy constructor reimplement

 private:
  static uint32_t total_ids_;
  uint32_t id_;
};

#endif