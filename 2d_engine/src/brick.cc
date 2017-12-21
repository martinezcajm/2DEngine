// Author: Sebastián Adrover Pedrosa
//Comments can be found at the header
#include "brick.h"

Brick::Brick() : Rect(){
  type_ = kBrick;
}

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
                float rotation, float scalex, float scaley, uint8_t lives){
  
  Rect::init(1, width, height, sc_r, sc_g, sc_b, sc_a, fc_r, fc_g, fc_b, fc_a, 
    px, py, rotation, scalex, scaley);
  lives_ = lives; 
  score_ = 100 * lives_; 
}

void Brick::update(){
  if (lives_ <= 0){
    if(active_)
      GM.score_ += score_;
    active_ = 0;
  }else{
    active_ = 1;
  }
}