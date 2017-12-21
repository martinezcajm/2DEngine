// Author: Sebastián Adrover Pedrosa
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
  GM.close_game_ = 0;
  GM.is_editor_ = 1;
  //ImGui::SFML::Init(*GM.window_->sfml_window_);
  POOL.init();
  ui_ = new UserInterface();
  ui_->init(*GM.window_->sfml_window_);

  scene_ = new Scene();
  scene_->is_game_over_ = 0;
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

  while(!GM.close_game_){
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
      GM.close_game_ = 1;
    }
    if(GM.window_->event_.type == sf::Event::KeyPressed){  
      // Exit if press ESC    
      if (GM.window_->event_.key.code == sf::Keyboard::Escape){
        GM.window_->sfml_window_->close();
        GM.close_game_ = 1;
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

        if(GM.window_->event_.key.code == sf::Keyboard::Return && 
          GM.game_over_ == 1){
          GM.new_game_ = 1;
        }
        
        if(GM.window_->event_.key.code == sf::Keyboard::Space){
          GM.is_ball_in_movement_ = 1;
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
    GM.close_game_ = 1;
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
    
  // TODO: Check game input value
  if(GM.new_game_){
    scene_->loadScene(scene_->scene_path_, GM.arial_);
    GM.game_over_= 0;
    GM.new_game_= 0;
    GM.score_ = 0;
    GM.lives_ = 3;
    GM.is_ball_in_movement_ = 0;
    scene_->is_game_over_ = 0;
  }
  if(!GM.game_over_ && GM.is_ball_in_movement_){
    scene_->update();  
  }
  if(scene_->is_game_over_){
    GM.game_over_= 1;
    scene_->is_game_over_ = 0;
  }
}

void Game::renderGame(){  
  //Only part of the UI that needs to be displayed while we are at game mode
  ui_->UiStartGameMenu();
  GM.window_->clear();
  scene_->drawScene(); 

  ImGui::SFML::Render(*GM.window_->sfml_window_);
  GM.window_->display();
}
