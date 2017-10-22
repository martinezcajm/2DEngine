#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/input.h>
#include <ESAT/time.h>

#include "rect.h"

void PaintRectangles() {
  const unsigned int kScreenWidth = 640;
  const unsigned int kScreenHeight = 480;  
  const float kFps = 60;
  //const uint8_t kMaxRectangles = 50;
  const uint8_t kNumBigRect = 3;
  const uint8_t kNumMedRect = 4;
  const uint8_t kNumLitRect = 6;
  const ESAT::Vec2 kSpawnPoinBigRect = {550, 50};
  const ESAT::Vec2 kSpawnPoinMedRect = {550, 200};
  const ESAT::Vec2 kSpawnPoinLitRect = {550, 350};
  const uint8_t kBigRectColor[4] = {0,0,102,255};
  const uint8_t kMedRectColor[4] = {51,51,255,255 };
  const uint8_t kLitRectColor[4] = {102,153,255,255 };
  const uint8_t kFillColor[4] = {102,0,102,255};
  const ESAT::Vec2 kBigRectDimension = {150,100};
  const ESAT::Vec2 kMedRectDimension = {100,75};
  const ESAT::Vec2 kLitRectDimension = {50,50};


  double current_time = ESAT::Time();
  double last_time = ESAT::Time();
  Rect *big_rect_container[kNumBigRect];
  Rect *medium_rect_container[kNumMedRect];
  Rect *small_rect_container[kNumLitRect];
  for(int i = 0; i < kNumBigRect; i++){
    big_rect_container[i] = new Rect();
    big_rect_container[i]->init(1,
                                kBigRectDimension.x, kBigRectDimension.y,
                                kFillColor[0],kFillColor[1],
                                kFillColor[2],kFillColor[3],
                                kBigRectColor[0], kBigRectColor[1],
                                kBigRectColor[2], kBigRectColor[3],
                                kSpawnPoinBigRect.x + (kBigRectDimension.x*i) +
                                (50*i), kSpawnPoinBigRect.y);
  }
  for(int i = 0; i < kNumMedRect; i++){
    medium_rect_container[i] = new Rect();
    medium_rect_container[i]->init(1,
                                kMedRectDimension.x, kMedRectDimension.y,
                                kFillColor[0],kFillColor[1],
                                kFillColor[2],kFillColor[3],
                                kMedRectColor[0], kMedRectColor[1],
                                kMedRectColor[2], kMedRectColor[3],
                                kSpawnPoinMedRect.x + (kMedRectDimension.x*i) +
                                (50*i), kSpawnPoinMedRect.y);
  }
  for(int i = 0; i < kNumLitRect; i++){
    small_rect_container[i] = new Rect();
    small_rect_container[i]->init(1,
                                kLitRectDimension.x, kLitRectDimension.y,
                                kFillColor[0],kFillColor[1],
                                kFillColor[2],kFillColor[3],
                                kLitRectColor[0], kLitRectColor[1],
                                kLitRectColor[2], kLitRectColor[3],
                                kSpawnPoinLitRect.x + (kLitRectDimension.x*i) +
                                (50*i), kSpawnPoinLitRect.y);
  }

  ESAT::WindowInit(kScreenWidth, kScreenHeight);
  last_time = ESAT::Time();
  while (ESAT::WindowIsOpened() &&
         !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    ESAT::DrawBegin();
    ESAT::DrawClear(0,0,0);

    for (auto const rectangle : big_rect_container){
      rectangle->draw();
      rectangle->move(-5,0);
      if(rectangle->position_.x < -kBigRectDimension.x){
        rectangle->position_.x = kSpawnPoinBigRect.x;
      }
    }

    for (auto const rectangle : medium_rect_container){
      rectangle->draw();
      rectangle->move(-10,0);
      if(rectangle->position_.x < -kMedRectDimension.x){
        rectangle->position_.x = kSpawnPoinMedRect.x;
      }
    }

    for (auto const rectangle : small_rect_container){
      rectangle->draw();
      rectangle->move(-15,0);
      if(rectangle->position_.x < -kLitRectDimension.x){
        rectangle->position_.x = kSpawnPoinLitRect.x;
      }
    }

    do{
      current_time = ESAT::Time();
    }while((current_time-last_time)<=1000.0/kFps);
    last_time = current_time; 
    ESAT::DrawEnd();
  // End of current frame
    ESAT::WindowFrame();
  }
  for(int i = 0; i < kNumBigRect; i++){
    delete big_rect_container[i];
  }
  for(int i = 0; i < kNumMedRect; i++){
    delete medium_rect_container[i];
  }
  for(int i = 0; i < kNumLitRect; i++){
    delete small_rect_container[i];
  }
  ESAT::WindowDestroy();
}

int ESAT::main(int argc, char **argv) {
  PaintRectangles();
  return 0;
}