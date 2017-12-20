// Comments can be found at the header
#include "imgui.h"
#include "imgui-SFML.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "game.h"
#include "scene.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

Game::Game(){ }
Game::~Game(){ }

void Game::init(){
  GM.game_over_ = 0;
  GM.is_editor_ = 1;
  //ImGui::SFML::Init(*GM.window_->sfml_window_);
  POOL.init();
  ui_ = new UserInterface();
  ui_->init(*GM.window_->sfml_window_);

  scene_ = new Scene();
  //TODO Right now the UI only allows to create sprite by image, but the 
  //sprite has the capacity to be created through copy of an already existing
  //texture (copying it in memory and having it's own reference) 
  //or by a texture Test case to check it works, the first sprite loses it's
  //texture after the scope and the last one doesn't as it stores a copy of it 
  /*
  sf::Texture texture;
  texture.loadFromFile("../data/enemy.png");
  scene_->addSprite(*sprite_test);
  Sprite *sprite_test2 = POOL.getSprite();
  uint8_t error;
  sprite_test2->init(300,400,0,1,1,texture,error);
  scene_->addSprite(*sprite_test2);*/
}

void Game::finish(){
  // TODO: release all the memory
  delete scene_;
  delete ui_;
  POOL.free();
  //ImGui::SFML::Shutdown();
}

void Game::mainLoop(){
  init();

  while(!GM.game_over_){
    processInput();
    //ui_->processInput(*GM.window_->sfml_window_, GM.window_->event_);
    if(GM.is_editor_){
      updateEditor();
      renderEditor();
    }else{
      updateGame();
      renderGame();
    }
  }

  finish();
}

void Game::processInput(){
  // Eventos de input

  //We check sfml and imgui events
  while (GM.window_->sfml_window_->pollEvent(GM.window_->event_)){
    ImGui::SFML::ProcessEvent(GM.window_->event_);
    if (GM.window_->event_.type == sf::Event::MouseButtonPressed && 
        GM.window_->event_.mouseButton.button == sf::Mouse::Left &&
        !ImGui::IsAnyWindowHovered()) {
      GM.mouse_status_ = MouseStatus::kPressed;
    }
    if (GM.window_->event_.type == sf::Event::MouseButtonReleased && 
        GM.window_->event_.mouseButton.button == sf::Mouse::Left ) {
      GM.mouse_status_ = MouseStatus::kReleased;
    }
    if (GM.window_->event_.type == sf::Event::Closed) {
      GM.window_->sfml_window_->close();
      GM.game_over_ = 1;
    }
    if(GM.window_->event_.type == sf::Event::KeyPressed){  
      // Exit if press ESC    
      if (GM.window_->event_.key.code == sf::Keyboard::Escape){
        GM.window_->sfml_window_->close();
        GM.game_over_ = 1;
      }
      else
      {
        // Player 1
        if(GM.window_->event_.key.code == sf::Keyboard::Left){
          GM.player1Left_ = 1;
        }
        if(GM.window_->event_.key.code == sf::Keyboard::Right){
          GM.player1Right_ = 1;
        }

        if(GM.window_->event_.key.code == sf::Keyboard::Return){
          GM.new_game_ = 0;
        }
      }
    }else if(GM.window_->event_.type == sf::Event::KeyReleased){
      // Player 1
      if(GM.window_->event_.key.code == sf::Keyboard::Left){
        GM.player1Left_ = 0;
      }
      if(GM.window_->event_.key.code == sf::Keyboard::Right){
        GM.player1Right_ = 0;
      }
    }
  }
}

void Game::updateEditor(){
  // If window is close then finish the excution
  if(!GM.window_->isOpen()){
    GM.game_over_ = 1;
  }
  ui_->update(*GM.window_->sfml_window_, *scene_);
}

void Game::renderEditor(){
  
  // render
  GM.window_->clear();
  scene_->drawScene();  
  //We render the UI
  ui_->renderUI(*GM.window_->sfml_window_, *scene_);

  //ImGui::SFML::Render(*GM.window_->sfml_window_);
  GM.window_->display();
}

void Game::updateGame(){
  //We are still rendering a part of the UI, so we need the update to be 
  //effective
  ImGui::SFML::Update(*GM.window_->sfml_window_, GM.deltaClock_.restart());
  
  //scene_->is_game_over_ = 1;
  
  // TODO: Check game input value
  scene_->update();  

/*
  GM.player1Left_ = 1;
  GM.player1Right_ = 1;
  GM.player2Left_ = 1;
  GM.player2Right_ = 1;*/
}

void Game::renderGame(){  
  //Only part of the UI that needs to be displayed while we are at game mode
  ui_->UiStartGameMenu();
  GM.window_->clear();
  scene_->drawScene(); 

  ImGui::SFML::Render(*GM.window_->sfml_window_);
  GM.window_->display();
}
