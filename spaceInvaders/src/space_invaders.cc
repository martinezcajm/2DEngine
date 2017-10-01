#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdint>

#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h>
#include <ESAT/time.h>

const int kRowEnemies = 3;
const int kColEnemies = 3;
const float kDistanceEnemies = 50;
const float kShootSpeed = 10;
const float kSpaceShipSpeed = 5;
const uint16_t kEnemyLifes = 1;
const uint16_t kSpaceShipLifes = 1;
const uint16_t kShieldLifes = 3;

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
    uint8_t isAlive_;
    uint16_t lifes_;          
    Shield(void);
    Shield(uint16_t lifes, ESAT::SpriteHandle sprite, ESAT::Vec2 position);
    ESAT::Vec2 getPosition(void);
    ESAT::SpriteHandle getSprite(void);
};

Shield::Shield(void){}

Shield::Shield(uint16_t lifes, ESAT::SpriteHandle sprite, ESAT::Vec2 position)
    : lifes_(lifes), sprite_(sprite), position_(position){
  isAlive_ = 1;
}

ESAT::Vec2 Shield::getPosition(void){
  return position_;
}

ESAT::SpriteHandle Shield::getSprite(void){
  return sprite_;
}

class EnemySet {
  public:
    float speed_;
    Enemy *enemies_[kRowEnemies][kColEnemies];
    ESAT::Vec2 position_;
    EnemySet(float speed, ESAT::Vec2 position);
    ESAT::Vec2 getPosition(void);
    float getSpeed(void);
    void addPosition(ESAT::Vec2 p);
};

EnemySet::EnemySet(float speed, ESAT::Vec2 position) 
    : speed_(speed), position_(position){
  for(int i = 0; i < kRowEnemies; ++i){
    for (int j = 0; j< kColEnemies; ++j){
      enemies_[i][j] = new Enemy(kEnemyLifes,ESAT::SpriteFromFile("enemy.png"),
        {i * kDistanceEnemies,j * kDistanceEnemies});
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
    uint8_t isShooting_;
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
  isShooting_ = 0;
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

class Shoot {
  public:
    ESAT::SpriteHandle sprite_;
    ESAT::Vec2 position_;
    float speed_;
    Shoot(void);
    Shoot(ESAT::SpriteHandle sprite, ESAT::Vec2 position);
    ESAT::Vec2 getPosition(void);
    float getSpeed(void);
    void setPosition(ESAT::Vec2 p);
    void addPosition(ESAT::Vec2 p);
    bool checkCollision(ESAT::Vec2 spritePosition, ESAT::SpriteHandle element);
    ESAT::SpriteHandle getSprite(void);
};

Shoot::Shoot(ESAT::SpriteHandle sprite, ESAT::Vec2 position)
    : sprite_(sprite), position_(position){
  speed_ = kShootSpeed;
}

/*Checks if the shoot has colided with an element in a position using the 
dimensions of it's sprite.*/
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

void SpaceInvaders() {
  const unsigned int kScreenWidth = 640;
  const unsigned int kScreenHeight = 480;
  const float kShieldsYPosition = 350;
  const float kFps = 60;
  ESAT::WindowInit(kScreenWidth, kScreenHeight);
  double current_time, last_time;
  last_time = ESAT::Time();
  EnemySet set(5, {300,0});
  int direction = 1;
  SpaceShip mainCharacter(kSpaceShipLifes,
                          ESAT::SpriteFromFile("spaceShip.png"), {300,450});
  Shoot spaceShipShoot(ESAT::SpriteFromFile("shoot.png"), {0,0});
  ESAT::Vec2 relativePositionEnemy;
  Shield leftShield (kShieldLifes, ESAT::SpriteFromFile("shield.png"),
                    {100,kShieldsYPosition});
  Shield middleShield (kShieldLifes, ESAT::SpriteFromFile("shield.png"),
                    {300, kShieldsYPosition});
  Shield rightShield (kShieldLifes, ESAT::SpriteFromFile("shield.png"),
                    {500,kShieldsYPosition});
  while (ESAT::WindowIsOpened() &&
        !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    ESAT::DrawBegin();
    ESAT::DrawClear(0,0,0);
    if(set.getPosition().x < 0 || set.getPosition().x > 480){
      direction = -direction;
      set.addPosition({0,set.getSpeed()});
    } 
    set.addPosition({(float)direction,0});
    for(int i = 0; i < kRowEnemies; ++i){
      for (int j = 0; j < kColEnemies; ++j){
        relativePositionEnemy.x = set.enemies_[i][j]->getPosition().x +
          set.getPosition().x;
        relativePositionEnemy.y = set.enemies_[i][j]->getPosition().y +
          set.getPosition().y;
        if(set.enemies_[i][j]->isAlive_ == 1 &&
          mainCharacter.isShooting_ == 1 &&
          spaceShipShoot.checkCollision(relativePositionEnemy,
          set.enemies_[i][j]->getSprite())){
          mainCharacter.isShooting_ = 0;
          set.enemies_[i][j]->lifes_ -= 1;
          if(set.enemies_[i][j]->lifes_ == 0)set.enemies_[i][j]->isAlive_ = 0;
        }
        if(set.enemies_[i][j]->isAlive_ == 1){
          ESAT::DrawSprite(set.enemies_[i][j]->getSprite(),
          set.enemies_[i][j]->getPosition().x + set.getPosition().x, 
          set.enemies_[i][j]->getPosition().y + set.getPosition().y);
        }
      }
    }
    if((leftShield.isAlive_ == 1 || rightShield.isAlive_ == 1 ||
      middleShield.isAlive_ == 1) && (mainCharacter.isShooting_ == 1)){
      if(spaceShipShoot.checkCollision(leftShield.getPosition(),
        leftShield.getSprite())&& leftShield.isAlive_ == 1){
        leftShield.lifes_ -= 1;
        mainCharacter.isShooting_ = 0;
        if(leftShield.lifes_ == 0) leftShield.isAlive_ = 0;
      }
      if(spaceShipShoot.checkCollision(rightShield.getPosition(),
        rightShield.getSprite()) && rightShield.isAlive_ == 1){
        rightShield.lifes_ -= 1;
        mainCharacter.isShooting_ = 0;
        if(rightShield.lifes_ == 0) rightShield.isAlive_ = 0;
      }
      if(spaceShipShoot.checkCollision(middleShield.getPosition(),
        middleShield.getSprite()) && middleShield.isAlive_ == 1){
        middleShield.lifes_ -= 1;
        mainCharacter.isShooting_ = 0;
        if(middleShield.lifes_ == 0) middleShield.isAlive_ = 0;
      }
    }
    if(leftShield.isAlive_ == 1)ESAT::DrawSprite(leftShield.getSprite(),
      leftShield.getPosition().x, leftShield.getPosition().y);
    if(rightShield.isAlive_ == 1)ESAT::DrawSprite(rightShield.getSprite(),
      rightShield.getPosition().x, rightShield.getPosition().y);
    if(middleShield.isAlive_ == 1)ESAT::DrawSprite(middleShield.getSprite(),
      middleShield.getPosition().x, middleShield.getPosition().y);
    if (ESAT::IsKeyPressed('A') && mainCharacter.getPosition().x > 0){
      mainCharacter.addPosition({- mainCharacter.getSpeed(),0});
    } 
    if (ESAT::IsKeyPressed('D') && mainCharacter.getPosition().x < 600){
      mainCharacter.addPosition({mainCharacter.getSpeed(),0});
    }
    if (ESAT::IsKeyDown('W') && mainCharacter.isShooting_ == 0){
      mainCharacter.isShooting_ = 1;
      spaceShipShoot.setPosition({mainCharacter.getPosition().x,
                                  mainCharacter.getPosition().y});
    } 
    ESAT::DrawSprite(mainCharacter.getSprite(), mainCharacter.getPosition().x,
                    mainCharacter.getPosition().y);
    if(mainCharacter.isShooting_ == 1){
      spaceShipShoot.addPosition({0,-spaceShipShoot.getSpeed()});
      ESAT::DrawSprite(spaceShipShoot.getSprite(),
                      spaceShipShoot.getPosition().x,
                      spaceShipShoot.getPosition().y);
      if(spaceShipShoot.getPosition().y < 0) mainCharacter.isShooting_ = 0;
    }
    do{
          current_time = ESAT::Time();
      }while((current_time-last_time)<=1000.0/kFps);
      last_time = current_time; 
    ESAT::DrawEnd();
    // End of current frame
    ESAT::WindowFrame();
  }
  ESAT::SpriteRelease(spaceShipShoot.getSprite());
  ESAT::SpriteRelease(mainCharacter.getSprite());
  ESAT::WindowDestroy();
}

int ESAT::main(int argc, char **argv) {
  SpaceInvaders();
  return 0;
}