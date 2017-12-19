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
  ImGui::SFML::Init(*GM.window_->sfml_window_);
  POOL.init();
  ui_ = new UserInterface();

  GM.scene_ = new Scene();
  //TODO Right now the UI only allows to create sprite by image, but the 
  //sprite has the capacity to be created through copy of an already existing
  //texture (copying it in memory and having it's own reference) 
  //or by a texture Test case to check it works, the first sprite loses it's
  //texture after the scope and the last one doesn't as it stores a copy of it 
  /*
  GM.scene_->addSprite(*sprite_test);
  Sprite *sprite_test2 = POOL.getSprite();
  uint8_t error;
  sprite_test2->init(300,400,0,1,1,texture,error);
  GM.scene_->addSprite(*sprite_test2);*/
}

void Game::finish(){
  // TODO: release all the memory
  delete GM.scene_;
  delete ui_;
  POOL.free();
  ImGui::SFML::Shutdown();
}

void Game::mainLoop(){
  init();

  while(!GM.game_over_){
    processInput();

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
      if (GM.window_->event_.key.code == sf::Keyboard::Escape)
      {
        GM.window_->sfml_window_->close();
        GM.game_over_ = 1;
      }
    }
  }
}

void Game::updateEditor(){
  // If window is close then finish the excution
  if(!GM.window_->isOpen()){
    GM.game_over_ = 1;
  }

  // Actualizar estados
  if(GM.status_ui_ == UiStatus::kDraw){
    if(GM.mouse_status_ == MouseStatus::kPressed){
      GM.mouse_status_ = MouseStatus::kNothing;
      GM.drawing_rect_ = POOL.getRect();
      //The limit of rects has been reached
      if(GM.drawing_rect_ == nullptr){
        GM.ui_is_drawing_ = 0;
      }else{
        //We insert the rect to the scene
        GM.scene_->addDrawableEntity(*GM.drawing_rect_);
        GM.ui_is_drawing_ = 1;
        GM.draw_origin_point_ = static_cast<sf::Vector2f>(
                      sf::Mouse::getPosition(*GM.window_->sfml_window_));
        GM.drawing_rect_->init(1,
           0,0, 
           255,0,0,255,
           0,255,0,255,
           GM.draw_origin_point_.x, GM.draw_origin_point_.y,
           0,1,1);
      }
    }else if(GM.mouse_status_ == MouseStatus::kReleased){
      GM.mouse_status_ = MouseStatus::kNothing;
      if(GM.ui_is_drawing_){
        GM.ui_is_drawing_ = 0;
        GM.mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(*GM.window_->sfml_window_));
        GM.drawing_rect_->resize(
                 GM.mouse_position_.x - GM.draw_origin_point_.x,
                 GM.mouse_position_.y - GM.draw_origin_point_.y);
        
      }
    }
    if(GM.ui_is_drawing_){
      GM.mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(*GM.window_->sfml_window_));
      GM.drawing_rect_->resize(GM.mouse_position_.x - GM.draw_origin_point_.x,
                               GM.mouse_position_.y - GM.draw_origin_point_.y);
    }
  }else if((GM.status_ui_ == UiStatus::kSelection|| 
            GM.status_ui_ == UiStatus::kMultiselect) && 
           GM.mouse_status_ == MouseStatus::kPressed){
    GM.mouse_status_ = MouseStatus::kNothing;
    GM.mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(*GM.window_->sfml_window_));
    GM.selected_id_ = GM.scene_-> checkCollision(GM.mouse_position_,
                                                 &GM.selected_type_);
      // 0 - nothing
      // 1 - Background
      // 2 - Rect
      // 3 - Label
      // 4 - Sprite
    if(GM.selected_type_ == 0){
      GM.edit_type_ui_ = UiEditType::kNull;
      GM.background_selection_ = nullptr;
      GM.rect_selection_ = nullptr;
      GM.label_selection_ = nullptr;
      GM.sprite_selection_ = nullptr;
    }else if(GM.selected_type_ == 1){
      GM.background_selection_ = 
        static_cast<Background*>(GM.scene_->getDrawableEntity(GM.selected_id_));
      if(GM.status_ui_ == UiStatus::kSelection){
        GM.edit_type_ui_ = UiEditType::kBackground;
        GM.rect_selection_ = nullptr;
        GM.label_selection_ = nullptr;
        GM.sprite_selection_ = nullptr;
      }
      //We don't want to be able to multi select the background, as there's
      //no sense in moving it
    }else if(GM.selected_type_ == 2){
      GM.rect_selection_ = 
        static_cast<Rect*>(GM.scene_->getDrawableEntity(GM.selected_id_));
      if(GM.status_ui_ == UiStatus::kSelection){
        GM.edit_type_ui_ = UiEditType::kRect;
        GM.background_selection_ = nullptr;
        GM.label_selection_ = nullptr;
        GM.sprite_selection_ = nullptr;
      }else if(GM.status_ui_ == UiStatus::kMultiselect){
        GM.edit_type_ui_ = UiEditType::kMulti;
        GM.rect_selection_->tag_ = (GM.rect_selection_->tag_) ?
                                    0 : GM.selected_item_tag_;
      }
    } else if(GM.selected_type_ == 3){
      GM.label_selection_ =
        static_cast<Label*>(GM.scene_->getDrawableEntity(GM.selected_id_));
      if(GM.status_ui_ == UiStatus::kSelection){
        GM.edit_type_ui_ = UiEditType::kLabel;
        GM.background_selection_ = nullptr;
        GM.rect_selection_ = nullptr;
        GM.sprite_selection_ = nullptr;
      }else if(GM.status_ui_ == UiStatus::kMultiselect){
        GM.edit_type_ui_ = UiEditType::kMulti;
        GM.label_selection_->tag_ = (GM.label_selection_->tag_) ?
                                     0 : GM.selected_item_tag_;
      }
    } else if(GM.selected_type_ == 4){
      GM.sprite_selection_ = 
        static_cast<Sprite*>(GM.scene_->getDrawableEntity(GM.selected_id_));
      if(GM.status_ui_ == UiStatus::kSelection){
        GM.edit_type_ui_ = UiEditType::kSprite;
        GM.background_selection_ = nullptr;
        GM.rect_selection_ = nullptr;
        GM.label_selection_ = nullptr;        
      }else if(GM.status_ui_ == UiStatus::kMultiselect){
        GM.edit_type_ui_ = UiEditType::kMulti;
        GM.sprite_selection_->tag_ = (GM.sprite_selection_->tag_) ?
                                      0 : GM.selected_item_tag_;
      }
      
    }
  }else if(GM.status_ui_ == UiStatus::kWrite && 
           GM.mouse_status_ == MouseStatus::kPressed){
    GM.mouse_status_ = MouseStatus::kNothing;
    Label *tmp_label = POOL.getLabel();
    //If the limit of labels hasn't been reached
    if(tmp_label != nullptr){
      GM.mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(*GM.window_->sfml_window_));
      GM.scene_->addDrawableEntity(*tmp_label);
      tmp_label->init(255,0,0,255,
                     GM.mouse_position_.x,GM.mouse_position_.y,
                     0,1,1,
                     "Hello world", GM.arial_);
    }
  }
  
  ImGui::SFML::Update(*GM.window_->sfml_window_, GM.deltaClock_.restart());
  // TODO: calculate delta
}

void Game::renderEditor(){
  //We render the UI
  ui_->renderUI();
  // render
  GM.window_->clear();
  GM.scene_->drawScene();  

  ImGui::SFML::Render(*GM.window_->sfml_window_);
  GM.window_->display();
}

void Game::updateGame(){
  //We are still rendering a part of the UI, so we need the update to be 
  //effective
  ImGui::SFML::Update(*GM.window_->sfml_window_, GM.deltaClock_.restart());
  
  // TODO: Check game input value
  GM.scene_->update();  
}

void Game::renderGame(){  
  //Only part of the UI that needs to be displayed while we are at game mode
  ui_->UiStartGameMenu();
  GM.window_->clear();
  GM.scene_->drawScene(); 

  ImGui::SFML::Render(*GM.window_->sfml_window_);
  GM.window_->display();
}
