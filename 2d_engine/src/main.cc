#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/input.h>
#include <ESAT/time.h>

#include "rect.h"

void PaintRectangles() {
  const unsigned int kScreenWidth = 640;
  const unsigned int kScreenHeight = 480;  
  const float kFps = 60;
  const uint8_t kMaxRectangles = 50;

  uint8_t is_drawing = 0;
  uint8_t num_rectangles = 0;
  double current_time = ESAT::Time();
  double last_time = ESAT::Time();
  ESAT::Vec2 draw_origin_point = {0,0};
  ESAT::Vec2 draw_end_point = {0,0};
  Rect *rect_container[kMaxRectangles];
  for(int i = 0; i < kMaxRectangles; i++){
    rect_container[i] = Rect::CreateRect();
  }
  ESAT::WindowInit(kScreenWidth, kScreenHeight);
  while (ESAT::WindowIsOpened() &&
         !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    ESAT::DrawBegin();
    ESAT::DrawClear(0,0,0);
    //We check for building rect while there's space for more
    if(num_rectangles < kMaxRectangles){
      //We register the position where starts the button click
      if(ESAT::MouseButtonDown(0)){
        is_drawing = 1;
        draw_origin_point.x = ESAT::MousePositionX();
        draw_origin_point.y = ESAT::MousePositionY();
        rect_container[num_rectangles]->init(1,
           0,0, 
           255,0,0,255,
           0,255,0,255,
           draw_origin_point.x, draw_origin_point.y);
      }
      //Once the mouse button is released we do the final init to the rectangle
      if (ESAT::MouseButtonUp(0)) {
        is_drawing = 0;
        draw_end_point.x = ESAT::MousePositionX();
        draw_end_point.y = ESAT::MousePositionY();
        //We check that the user is not drawing a line (origin.x or y equals to
        //endpoint.x or y)
        if((draw_origin_point.x!=draw_end_point.x) &&
           (draw_origin_point.y!=draw_end_point.y)){
          rect_container[num_rectangles]->resize(
             draw_end_point.x - draw_origin_point.x,
             draw_end_point.y - draw_origin_point.y);
          num_rectangles++;
        }
      }
      //We draw the selected area while the mouse button is not released
      if(is_drawing){
        draw_end_point.x = ESAT::MousePositionX();
        draw_end_point.y = ESAT::MousePositionY();
        rect_container[num_rectangles]->resize(
           draw_end_point.x - draw_origin_point.x,
           draw_end_point.y - draw_origin_point.y);
      }
    }
    for (auto const rectangle : rect_container){  
      if (rectangle->active_){
        rectangle->draw();
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
  for(int i = 0; i < kMaxRectangles; i++){
    delete rect_container[i];
  }
  ESAT::WindowDestroy();
}

int ESAT::main(int argc, char **argv) {
  PaintRectangles();
  return 0;
}