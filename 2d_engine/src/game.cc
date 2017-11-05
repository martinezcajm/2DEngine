#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "game.h"
#include "scene.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

Game::Game(){ }
void Game::init(){
  GM.scene_ = new Scene();
  GM.texture_ = new sf::Texture();
  GM.texture_->loadFromFile("../data/enemy.png");

  GM.rect_test_ = Rect::CreateRect();
  GM.rect_test_->init(1,
                  50,100, 
                  255,0,0,255,
                  0,255,0,255,
                  200, 300,
                  0,1,1);
  Rect *rect = Rect::CreateRect();
  rect->init(1,
    50,100, 
    255,0,0,255,
    0,255,0,255,
    300, 400,
    0,1,1);
  rect->z_order_ = 3;

  Rect *rect2 = Rect::CreateRect();
  rect2->init(1,
    50,100, 
    255,0,0,255,
    0,255,0,255,
    400, 500,
    0,1,1);
  rect2->z_order_ = 2;
      
  Rect *rect3 = Rect::CreateRect();
  rect3->init(1,
    50,100, 
    255,0,0,255,
    0,255,0,255,
    20, 20,
    0,1,1);
  rect3->z_order_ = 1;
      
  Rect *rect4 = Rect::CreateRect();
  rect4->init(1,
    50,100, 
    255,0,0,255,
    0,255,0,255,
    20, 75,
    0,1,1);
  rect4->z_order_ = 2;

  GM.scene_->addRect(*GM.rect_test_);
  GM.scene_->addRect(*rect);
  GM.scene_->addRect(*rect2);
  GM.scene_->addRect(*rect3);
  GM.scene_->addRect(*rect4);

  GM.scene_->removeRect(4);

  GM.sprite_test_ = Sprite::CreateSprite();
  GM.sprite_test_->init(0,0,
    0,1,1,
    *GM.texture_);
                   
}

void Game::gameLoop(){
  while(!GM.game_over_){
    processInput();
    update();
    render();
  }
}

void Game::processInput(){
  // Eventos de input


  if(!GM.window_->isOpen()){
    GM.game_over_ = true;
  }
}

void Game::update(){
  // Actualizar estados

}

void Game::render(){
  // render
  GM.window_->clear();
  GM.scene_->drawScene();
  //GM.scene_->getRect(1)->draw(*GM.window_->sfml_window_);
  //GM.scene_->getRect(2)->draw(*GM.window_->sfml_window_);
  //GM.rect_test->draw(*GM.window->sfml_window_);
  //GM.label_test_->draw(*GM.window_->sfml_window_);
  GM.sprite_test_->draw(*GM.window_->sfml_window_);
  

  //GM.scene.zOrderMapRect_

  //ImGui::SFML::Render(window);
  GM.window_->display();


  //GameManager::instance().window->Display();
}