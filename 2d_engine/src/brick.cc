//Comments can be found at the header
#include "brick.h"

Brick::Brick(){}
Brick* Brick::CreateBrick(){
  if(Rect::total_rects_ < kMaxRects){
    Brick* p_brick = new Brick();
    return p_brick;
  }else{
    return nullptr;
  }
}

void Brick::init(float width, float height, uint8_t sc_r,
                uint8_t sc_g, uint8_t sc_b, uint8_t sc_a, uint8_t fc_r,
                uint8_t fc_g, uint8_t fc_b, uint8_t fc_a, float px, float py,
                float scalex, float scaley, uint8_t lives){
  
  Rect::init(1, width, height, sc_r, sc_g, sc_b, sc_a, fc_r, fc_g, fc_b, fc_a, 
    px, py, 0.0f, scalex, scaley);
  lives_ = lives;  
}

void Brick::update(){


}