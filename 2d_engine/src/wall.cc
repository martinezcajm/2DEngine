//Comments can be found at the header
#include "wall.h"

Wall::Wall(){}
Wall* Wall::CreateWall(){
  if(Rect::total_rects_ < kMaxRects){
    Wall* p_wall = new Wall();
    return p_wall;
  }else{
    return nullptr;
  }
}

void Wall::init(float width, float height, uint8_t sc_r,
                uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
                uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py,
                float scalex, float scaley){
  
  Rect::init(1, width, height, sc_r, sc_g, sc_b, sc_a, fc_r, fc_g, fc_b, fc_a, 
    px, py, 0.0f, scalex, scaley);
}
