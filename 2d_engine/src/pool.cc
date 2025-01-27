// pool.cc
// Jose Maria Martinez
// Implementation of entity. Pooling used for reusing the entities used while
// iterating with the engine. 
//Comments for the functions can be found at the header
#include "pool.h"

Pool::Pool(){
}

Pool::~Pool(){}

Pool& Pool::instance(){
  static Pool* pinstance = new Pool();
  return *pinstance;
}

void Pool::init(){
  Rect* aux_rect = nullptr;
  Label* aux_label = nullptr;
  Sprite* aux_sprite = nullptr;
  Background* aux_background = nullptr;
  Wall *aux_wall = nullptr;
  Brick *aux_brick = nullptr;
  Ball *aux_ball = nullptr;
  Player *aux_player = nullptr;

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
  for(int i = 0; i<start_walls_; i++){
    aux_wall = Wall::CreateWall();
    if(aux_wall!=nullptr) wall_pool_.push_back(aux_wall);
  }
  for(int i = 0; i<start_bricks_; i++){
    aux_brick = Brick::CreateBrick();
    if(aux_brick!=nullptr) brick_pool_.push_back(aux_brick);
  }
  for(int i = 0; i<start_balls_; i++){
    aux_ball = Ball::CreateBall();
    if(aux_ball!=nullptr) ball_pool_.push_back(aux_ball);
  }
  for(int i = 0; i<start_players_; i++){
    aux_player = Player::CreatePlayer();
    if(aux_player!=nullptr) player_pool_.push_back(aux_player);
  }
}

void Pool::free(){
  Rect *rect_aux_delete = nullptr;
  Label *label_aux_delete = nullptr;
  Sprite *sprite_aux_delete = nullptr;
  Background *background_aux_delete = nullptr;
  Wall *wall_aux_delete = nullptr;
  Brick *brick_aux_delete = nullptr;
  Ball *ball_aux_delete = nullptr;
  Player *player_aux_delete = nullptr;

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

  while(wall_pool_.size() > 0){
    wall_aux_delete = wall_pool_.back();
    wall_pool_.pop_back();
    delete wall_aux_delete;
  }

  while(brick_pool_.size() > 0){
    brick_aux_delete = brick_pool_.back();
    brick_pool_.pop_back();
    delete brick_aux_delete;
  }

  while(ball_pool_.size() > 0){
    ball_aux_delete = ball_pool_.back();
    ball_pool_.pop_back();
    delete ball_aux_delete;
  }

  while(player_pool_.size() > 0){
    player_aux_delete = player_pool_.back();
    player_pool_.pop_back();
    delete player_aux_delete;
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

Wall* Pool::getWall(){
  Wall* aux_wall;
  if(wall_pool_.size() > 0){
    aux_wall = wall_pool_.back();
    wall_pool_.pop_back();
    return aux_wall;
  }else{
    return Wall::CreateWall();
  }
}

Brick* Pool::getBrick(){
  Brick* aux_brick;
  if(brick_pool_.size() > 0){
    aux_brick = brick_pool_.back();
    brick_pool_.pop_back();
    return aux_brick;
  }else{
    return Brick::CreateBrick();
  }
}

Ball* Pool::getBall(){
  Ball* aux_ball;
  if(ball_pool_.size() > 0){
    aux_ball = ball_pool_.back();
    ball_pool_.pop_back();
    return aux_ball;
  }else{
    return Ball::CreateBall();
  }
}

Player* Pool::getPlayer(){
  Player* aux_player;
  if(player_pool_.size() > 0){
    aux_player = player_pool_.back();
    player_pool_.pop_back();
    return aux_player;
  }else{
    return Player::CreatePlayer();
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

void Pool::returnWall(Wall &wall){
  wall.unuse();
  wall_pool_.push_back(&wall);
}

void Pool::returnBrick(Brick &brick){
  brick.unuse();
  brick_pool_.push_back(&brick);
}

void Pool::returnBall(Ball &ball){
  ball.unuse();
  ball_pool_.push_back(&ball);
}

void Pool::returnPlayer(Player &player){
  player.unuse();
  player_pool_.push_back(&player);
}