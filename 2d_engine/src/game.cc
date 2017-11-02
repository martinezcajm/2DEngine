#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "game.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

Game::Game(){ }
void Game::Init(){
  GM.rect_test = Rect::CreateRect();
  GM.label_test = Label::CreateLabel();
  GM.sprite_test = Sprite::CreateSprite();
  GM.texture = new sf::Texture();
  GM.texture->loadFromFile("../data/enemy.png");
  GM.rect_test->init(1,
                  50,100, 
                  255,0,0,255,
                  0,255,0,255,
                  200, 300,
                  0,1,1);
                  GM.label_test->init(255,0,0,255,
                   500,400,
                   0,1,1,
                   "Hello world");
                   GM.sprite_test->init(0,0,
                   0,1,1,
                   *GM.texture);
                   
}

void Game::GameLoop(){
  while(!GM.game_over){
    ProcessInput();
    Update();
    Render();
  }
}

void Game::ProcessInput(){
  // Eventos de input


  if(!GM.window->IsOpen()){
    GM.game_over = true;
  }
}

void Game::Update(){
  // Actualizar estados

}

void Game::Render(){
  // render
  GM.window->Clear();
  GM.rect_test->draw(*GM.window->sfml_window_);
  GM.label_test->draw(*GM.window->sfml_window_);
  GM.sprite_test->draw(*GM.window->sfml_window_);
    //ImGui::SFML::Render(window);
  GM.window->Display();


  //GameManager::instance().window->Display();
}