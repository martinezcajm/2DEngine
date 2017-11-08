//Comments can be found at the header
#include "pool.h"

Pool::Pool(){
}

Pool& Pool::instance(){
  static Pool* pinstance = new Pool();
  return *pinstance;
}

void Pool::init(){
  Rect* aux_rect = nullptr;
  Label* aux_label = nullptr;
  Sprite* aux_sprite = nullptr;
  Background* aux_background = nullptr;

  for(int i = 0; i<start_rects_; i++){
    aux_rect = Rect::CreateRect();
    if(aux_rect!=nullptr) rect_pool_.push_back(aux_rect);
  }
  for(int i = 0; i<start_labels_; i++){
    aux_label = Label::CreateLabel();
    if(aux_label!=nullptr) label_pool_.push_back(aux_label);
  }
  for(int i = 0; i<start_sprites_; i++){
    aux_sprite = Sprite::CreateSprite();
    if(aux_sprite!=nullptr) sprite_pool_.push_back(aux_sprite);
  }
  for(int i = 0; i<start_backgrounds_; i++){
    aux_background = Background::CreateBackground();
    if(aux_background!=nullptr) bg_pool_.push_back(aux_background);
  }
}

void Pool::free(){
  Rect *rect_aux_delete = nullptr;
  Label *label_aux_delete = nullptr;
  Sprite *sprite_aux_delete = nullptr;
  Background *background_aux_delete = nullptr;

  while(rect_pool_.size() > 0){
    rect_aux_delete = rect_pool_.back();
    rect_pool_.pop_back();
    delete rect_aux_delete;
  }

  while(label_pool_.size() > 0){
    label_aux_delete = label_pool_.back();
    label_pool_.pop_back();
    delete label_aux_delete;
  }

  while(sprite_pool_.size() > 0){
    sprite_aux_delete = sprite_pool_.back();
    sprite_pool_.pop_back();
    delete sprite_aux_delete;
  }

  while(bg_pool_.size() > 0){
    background_aux_delete = bg_pool_.back();
    bg_pool_.pop_back();
    delete background_aux_delete;
  }
}

Rect* Pool::getRect(){
  Rect* aux_rect = nullptr;
  if(rect_pool_.size() > 0){
    aux_rect = rect_pool_.back();
    rect_pool_.pop_back();
    return aux_rect;
  }else{
    return Rect::CreateRect();
  }
}

Label* Pool::getLabel(){
  Label* aux_label = nullptr;
  if(label_pool_.size() > 0){
    aux_label = label_pool_.back();
    label_pool_.pop_back();
    return aux_label;
  }else{
    return Label::Label::CreateLabel();
  }
}

Sprite* Pool::getSprite(){
  Sprite* aux_sprite;
  if(sprite_pool_.size() > 0){
    aux_sprite = sprite_pool_.back();
    sprite_pool_.pop_back();
    return aux_sprite;
  }else{
    return Sprite::CreateSprite();
  }
}

Background* Pool::getBackground(){
  Background* aux_background;
  if(bg_pool_.size() > 0){
    aux_background = bg_pool_.back();
    bg_pool_.pop_back();
    return aux_background;
  }else{
    return Background::CreateBackground();
  }
}

void Pool::returnRect(Rect &rect){
  rect.unuse();
  rect_pool_.push_back(&rect);
}

void Pool::returnLabel(Label &label){
  label.unuse();
  label_pool_.push_back(&label);
}

void Pool::returnSprite(Sprite &sprite){
  sprite.unuse();
  sprite_pool_.push_back(&sprite);
}

void Pool::returnBackground(Background &background){
  background.unuse();
  bg_pool_.push_back(&background);
}

