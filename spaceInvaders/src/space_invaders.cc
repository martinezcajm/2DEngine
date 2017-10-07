#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <stdlib.h>

#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h>
#include <ESAT/time.h>

const float kDistanceEnemies = 50;
const float kEnemiesSpeed = 5;
const float kShieldDistance = 200;
const float kShootSpeed = 10;
const float kSpaceShipSpeed = 5;
const float kShieldsYPosition = 350;
const uint8_t kRowEnemies = 3;
const uint8_t kColEnemies = 3;
const uint8_t kNumShields = 3;
const uint16_t kEnemyLifes = 1;
const uint16_t kShieldLifes = 3;
const uint16_t kSpaceShipLifes = 1;
const uint16_t kOriginPointFirstShield = 100;

class Shoot {
  public:
    ESAT::SpriteHandle sprite_;
    ESAT::Vec2 position_;
    float speed_;
    uint8_t is_alive_;
    Shoot(void);
    Shoot(ESAT::SpriteHandle sprite, ESAT::Vec2 position);
    ESAT::Vec2 getPosition(void);
    float getSpeed(void);
    void setPosition(ESAT::Vec2 p);
    void addPosition(ESAT::Vec2 p);
    bool checkCollision(ESAT::Vec2 spritePosition, ESAT::SpriteHandle element);
    ESAT::SpriteHandle getSprite(void);
    uint8_t is_alive(void);
};

Shoot::Shoot(ESAT::SpriteHandle sprite, ESAT::Vec2 position)
    : sprite_(sprite), position_(position){
  speed_ = kShootSpeed;
  is_alive_ = 0;
}

/*Checks if the shoot has colided with an element in a position using the 
dimensions of it's sprite. If the shoot colided we kill it*/
bool Shoot::checkCollision(ESAT::Vec2 spritePosition,
    ESAT::SpriteHandle element){
  if(((position_.x > spritePosition.x && 
    position_.x < spritePosition.x + ESAT::SpriteWidth(element)) || 
    (position_.x + ESAT::SpriteWidth(sprite_) > spritePosition.x &&
    position_.x < spritePosition.x + ESAT::SpriteWidth(element))) &&
    ((position_.y > spritePosition.y &&
    position_.y < spritePosition.y + ESAT::SpriteHeight(element)) || 
    (position_.y + ESAT::SpriteHeight(sprite_) > spritePosition.y &&
    position_.y < spritePosition.y + ESAT::SpriteHeight(element))) ){
    is_alive_ = 0;
    return true;
  }
  return false;
}

ESAT::Vec2 Shoot::getPosition(void){
  return position_;
}

float Shoot::getSpeed(void){
  return speed_;
}

uint8_t Shoot::is_alive(void){
  return is_alive_;
}

void Shoot::setPosition(ESAT::Vec2 p){
  position_.x = p.x;
  position_.y = p.y;
}

void Shoot::addPosition(ESAT::Vec2 p){
  position_.x = position_.x + p.x;
  position_.y = position_.y + p.y;
}

ESAT::SpriteHandle Shoot::getSprite(void){
  return sprite_;
}

class Enemy {
  public:
    ESAT::SpriteHandle sprite_;
    ESAT::Vec2 position_;
    uint8_t isAlive_;
    uint16_t lifes_;   
    Enemy(void);
    Enemy(uint16_t lifes, ESAT::SpriteHandle sprite, ESAT::Vec2 position);
    ESAT::Vec2 getPosition(void);
    ESAT::SpriteHandle getSprite(void);
};

Enemy::Enemy(void){}

Enemy::Enemy(uint16_t lifes, ESAT::SpriteHandle sprite, ESAT::Vec2 position)
    : lifes_(lifes), sprite_(sprite), position_(position){
  isAlive_ = 1;
}

ESAT::Vec2 Enemy::getPosition(void){
  return position_;
}

ESAT::SpriteHandle Enemy::getSprite(void){
  return sprite_;
}

class Shield {
  public:
    ESAT::SpriteHandle sprite_;
    ESAT::Vec2 position_;
    uint8_t is_alive_;
    uint16_t lifes_;          
    Shield(void);
    Shield(uint16_t lifes, ESAT::SpriteHandle sprite, ESAT::Vec2 position);
    ESAT::Vec2 getPosition(void);
    ESAT::SpriteHandle getSprite(void);
};

Shield::Shield(void){}

Shield::Shield(uint16_t lifes, ESAT::SpriteHandle sprite, ESAT::Vec2 position)
    : lifes_(lifes), sprite_(sprite), position_(position){
  is_alive_ = 1;
}

ESAT::Vec2 Shield::getPosition(void){
  return position_;
}

ESAT::SpriteHandle Shield::getSprite(void){
  return sprite_;
}

class ShieldSet{
  public:
    Shield *shields_ = nullptr;
    uint8_t num_shields_;
    uint8_t num_shields_alive_;
    uint16_t origin_first_shield_;
    ShieldSet(uint8_t num_shields, uint16_t origin_first_shield);
    uint8_t Init(void);
    void Dispose(void);
    void Draw(Shoot *shoot);
};

ShieldSet::ShieldSet(uint8_t num_shields, uint16_t origin_first_shield)
    : num_shields_(num_shields), origin_first_shield_(origin_first_shield){}

/*This function initializes the class first storing dynamic memory, in case
the booking of memory fails it returns a -1. If you call this method you need to call dipsose once you are done with it*/
uint8_t ShieldSet::Init(void){
  num_shields_alive_ = num_shields_;
  ESAT::SpriteHandle sprite = ESAT::SpriteFromFile("../data/shield.png");
  shields_ = (Shield*)malloc(sizeof(Shield)*num_shields_);
  if(!shields_) return 1;
  for(int i = 0; i < num_shields_; i++){
    shields_[i] = Shield(kShieldLifes, sprite, 
      {origin_first_shield_ + (i*kShieldDistance), kShieldsYPosition});
  }
  return 0;
} 

/*Frees all the memory reserved by the structure in the Init. Must be summoned
once you are done wit the structure*/
void ShieldSet::Dispose(void){
  ESAT::SpriteRelease(shields_[0].getSprite());
  free(shields_);
}

/*Draws the shields from the set checking before if they have died in this
frame*/
void ShieldSet::Draw(Shoot *shoot){
  if(num_shields_alive_ > 0){
    for(int i = 0; i < num_shields_; ++i){
      if(shoot->is_alive() == 1 && shields_[i].is_alive_ == 1 &&
         shoot->checkCollision(shields_[i].getPosition(),
                               shields_[i].getSprite()) ){
        shields_[i].lifes_ -= 1;
        if(shields_[i].lifes_ == 0){
          shields_[i].is_alive_ = 0;
          num_shields_alive_ -=1;
        }
      }
      if(shields_[i].is_alive_ == 1){
        ESAT::DrawSprite(shields_[i].getSprite(),shields_[i].getPosition().x,
                         shields_[i].getPosition().y);
      }
    }
  }
}

class EnemySet {
  public:
    float speed_;
    Enemy *enemies_ = nullptr;
    ESAT::Vec2 position_;
    uint16_t num_enemies_;
    uint8_t enemies_by_col_;
    EnemySet(float speed, ESAT::Vec2 position, uint16_t num_enemies,
             uint8_t enemies_by_col);
    ESAT::Vec2 getPosition(void);
    float getSpeed(void);
    void addPosition(ESAT::Vec2 p);
    uint8_t Init();
    void Dispose();
    void Draw(Shoot *shoot);
};

EnemySet::EnemySet(float speed, ESAT::Vec2 position, uint16_t num_enemies,
                    uint8_t enemies_by_col) 
    : speed_(speed), position_(position), num_enemies_(num_enemies),
      enemies_by_col_(enemies_by_col){}

/*This function initializes the class first storing dynamic memory, in case
the booking of memory fails it returns a -1. If you call this method you need to call dipsose once you are done with it*/
uint8_t EnemySet::Init(){
  ESAT::SpriteHandle sprite = ESAT::SpriteFromFile("../data/enemy.png");
  enemies_ = (Enemy*) malloc(sizeof(Enemy)*num_enemies_);
  if(!enemies_) return 1;
  for(int i = 0; i < num_enemies_; i++){  
    enemies_[i] = Enemy(kEnemyLifes, sprite,
                        {(i%enemies_by_col_) * kDistanceEnemies,
                         (i/enemies_by_col_) * kDistanceEnemies});
  }
  return 0;
}

/*Frees all the memory reserved by the structure in the Init. Must be summoned
once you are done wit the structure*/
void EnemySet::Dispose(){
  ESAT::SpriteRelease(enemies_[0].getSprite());
  free(enemies_);
}

/*Draws the enemies form the set checking before if they have died in this
 frame*/
void EnemySet::Draw(Shoot *shoot){
  ESAT::Vec2 relativePositionEnemy;
  for(int i = 0; i < num_enemies_; ++i){
    relativePositionEnemy.x = enemies_[i].getPosition().x + position_.x;
    relativePositionEnemy.y = enemies_[i].getPosition().y + position_.y;
      if(enemies_[i].isAlive_ == 1 && shoot->is_alive() == 1 &&
        shoot->checkCollision(relativePositionEnemy,
                              enemies_[i].getSprite())){
          enemies_[i].lifes_ -= 1;
          if(enemies_[i].lifes_ == 0) enemies_[i].isAlive_ = 0;
        }
        if(enemies_[i].isAlive_ == 1){
          ESAT::DrawSprite(enemies_[i].getSprite(),
                           enemies_[i].getPosition().x + position_.x, 
                           enemies_[i].getPosition().y + position_.y);
        }
    }
}

float EnemySet::getSpeed(void){
  return speed_;
}

ESAT::Vec2 EnemySet::getPosition(void){
  return position_;
}

void EnemySet::addPosition(ESAT::Vec2 p){
  position_.x = position_.x + p.x;
  position_.y = position_.y + p.y;
}

class SpaceShip {
  public:
    ESAT::SpriteHandle sprite_;
    ESAT::Vec2 position_;
    uint8_t isAlive_;
    uint16_t lifes_;     
    float speed_;
    SpaceShip(void);
    SpaceShip(uint16_t lifes, ESAT::SpriteHandle sprite, ESAT::Vec2 position);
    ESAT::Vec2 getPosition(void);
    float getSpeed(void);
    void addPosition(ESAT::Vec2 p);
    ESAT::SpriteHandle getSprite(void);
};

SpaceShip::SpaceShip(uint16_t lifes, ESAT::SpriteHandle sprite, 
                    ESAT::Vec2 position)
    :lifes_(lifes), sprite_(sprite), position_(position){
  isAlive_ = 1;
  speed_ = kSpaceShipSpeed;
}

ESAT::Vec2 SpaceShip::getPosition(void){
  return position_;
}

float SpaceShip::getSpeed(void){
  return speed_;
}

void SpaceShip::addPosition(ESAT::Vec2 p){
  position_.x = position_.x + p.x;
  position_.y = position_.y + p.y;
}

ESAT::SpriteHandle SpaceShip::getSprite(void){
  return sprite_;
}

void SpaceInvaders() {
  const unsigned int kScreenWidth = 640;
  const unsigned int kScreenHeight = 480;  
  const float kFps = 60;
  uint8_t error;
  ESAT::WindowInit(kScreenWidth, kScreenHeight);
  ESAT::SpriteHandle shoot_spr = ESAT::SpriteFromFile("../data/shoot.png");
  ESAT::SpriteHandle ship_spr = ESAT::SpriteFromFile("../data/spaceShip.png");
  double current_time, last_time;
  last_time = ESAT::Time();
  SpaceShip mainCharacter(kSpaceShipLifes, ship_spr, {300,450});
  Shoot spaceShipShoot(shoot_spr, {0,0});
  EnemySet enemy_set(kEnemiesSpeed, {300,0}, kRowEnemies*kColEnemies,
                     kColEnemies);
  error = enemy_set.Init();
  int direction = 1;
  ShieldSet shield_set(kNumShields, kOriginPointFirstShield);
  error += shield_set.Init();
  if(error == 0){
    while (ESAT::WindowIsOpened() &&
           !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
      ESAT::DrawBegin();
      ESAT::DrawClear(0,0,0);
      if(enemy_set.getPosition().x < 0 || enemy_set.getPosition().x > 480){
        direction = -direction;
        enemy_set.addPosition({0,enemy_set.getSpeed()});
      } 
      enemy_set.addPosition({(float)direction,0});
      enemy_set.Draw(&spaceShipShoot);
      shield_set.Draw(&spaceShipShoot);
      if (ESAT::IsKeyPressed('A') && mainCharacter.getPosition().x > 0){
        mainCharacter.addPosition({- mainCharacter.getSpeed(),0});
      } 
      if (ESAT::IsKeyPressed('D') && mainCharacter.getPosition().x < 600){
        mainCharacter.addPosition({mainCharacter.getSpeed(),0});
      }
      if (ESAT::IsKeyDown('W') && spaceShipShoot.is_alive_ == 0){
        spaceShipShoot.is_alive_ = 1;
        spaceShipShoot.setPosition({mainCharacter.getPosition().x,
                                  mainCharacter.getPosition().y});
      } 
      ESAT::DrawSprite(mainCharacter.getSprite(),mainCharacter.getPosition().x,
                    mainCharacter.getPosition().y);
      if(spaceShipShoot.is_alive_ == 1){
        spaceShipShoot.addPosition({0,-spaceShipShoot.getSpeed()});
        ESAT::DrawSprite(spaceShipShoot.getSprite(),
                         spaceShipShoot.getPosition().x,
                         spaceShipShoot.getPosition().y);
        if(spaceShipShoot.getPosition().y < 0)  spaceShipShoot.is_alive_ = 0;
      }
    do{
          current_time = ESAT::Time();
      }while((current_time-last_time)<=1000.0/kFps);
      last_time = current_time; 
    ESAT::DrawEnd();
    // End of current frame
    ESAT::WindowFrame();
    }
  }
  
  enemy_set.Dispose();
  shield_set.Dispose();
  ESAT::SpriteRelease(spaceShipShoot.getSprite());
  ESAT::SpriteRelease(mainCharacter.getSprite());
  //ESAT::SpriteRelease(leftShield.getSprite());
  ESAT::WindowDestroy();
}

int ESAT::main(int argc, char **argv) {
  SpaceInvaders();
  return 0;
}