#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/input.h>
#include <ESAT/time.h>

#include "rect.h"

void PaintRectangles() {
  const unsigned int kScreenWidth = 640;
  const unsigned int kScreenHeight = 480;  
  const float kFps = 60;
  uint8_t error = 0;
  double current_time, last_time;
  ESAT::WindowInit(kScreenWidth, kScreenHeight);
  last_time = ESAT::Time();
  Rect* rect_test = nullptr;
  rect_test = new Rect();
  rect_test->init(1, 20, 20, 255,0,0,255, 0,255,0,255, 10, 20);
  if(error == 0){
    while (ESAT::WindowIsOpened() &&
           !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
      ESAT::DrawBegin();
      ESAT::DrawClear(0,0,0);
    rect_test->draw();
    do{
      current_time = ESAT::Time();
    }while((current_time-last_time)<=1000.0/kFps);
    last_time = current_time; 
    ESAT::DrawEnd();
    // End of current frame
    ESAT::WindowFrame();
    }
  }
  delete rect_test;
  rect_test = nullptr;
  ESAT::WindowDestroy();
}

int ESAT::main(int argc, char **argv) {
  PaintRectangles();
  return 0;
}