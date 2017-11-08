#include "imgui.h"
#include "imgui-SFML.h"
#include "rect.h"
#include "label.h"
#include "sprite.h"
#include "game.h"
#include "scene.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

sf::Font font;

Game::Game(){ }
Game::~Game(){
  POOL.free();
}

void Game::init(){
  GM.game_over_ = false;
  GM.is_editor_ = true;
  ImGui::SFML::Init(*GM.window_->sfml_window_);
  POOL.init();

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

  //GM.scene_->removeRect(4);

  GM.sprite_test_ = Sprite::CreateSprite();
  GM.sprite_test_->init(0,0,
    0,1,1,
    *GM.texture_);
      
  sf::Vector2f position;
  uint8_t i = 0;
  position.x = 100;
  position.y = 200;
  GM.scene_->checkCollision(position, &i);
  GM.scene_->saveScene("scene.json");
  GM.scene_->loadScene("scene.json");
}

void Game::finish(){
  // TODO: release all the memory

  // TODO: say goodbye
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
		GM.game_over_ = true;
	}
  }  

  if(!GM.window_->isOpen()){
    GM.game_over_ = true;
  }
}

void Game::updateEditor(){
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
        GM.scene_->addRect(*GM.drawing_rect_);
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
  }else if(GM.status_ui_ == UiStatus::kSelection && 
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
      GM.edit_type_ui_ = UiEditType::kBackground;
      GM.background_selection_ = GM.scene_->getBackground(GM.selected_id_);
      GM.rect_selection_ = nullptr;
      GM.label_selection_ = nullptr;
      GM.sprite_selection_ = nullptr;
    }else if(GM.selected_type_ == 2){
      GM.edit_type_ui_ = UiEditType::kRect;
      GM.background_selection_ = nullptr;
      GM.rect_selection_ = GM.scene_->getRect(GM.selected_id_);
      GM.label_selection_ = nullptr;
      GM.sprite_selection_ = nullptr;
    } else if(GM.selected_type_ == 3){
      GM.edit_type_ui_ = UiEditType::kLabel;
      GM.background_selection_ = nullptr;
      GM.rect_selection_ = nullptr;
      GM.label_selection_ = GM.scene_->getLabel(GM.selected_id_);
      GM.sprite_selection_ = nullptr;
    } else if(GM.selected_type_ == 4){
      GM.edit_type_ui_ = UiEditType::kSprite;
      GM.background_selection_ = nullptr;
      GM.rect_selection_ = nullptr;
      GM.label_selection_ = nullptr;
      GM.sprite_selection_ = GM.scene_->getSprite(GM.selected_id_);
    }
  }else if(GM.status_ui_ == UiStatus::kWrite && 
           GM.mouse_status_ == MouseStatus::kPressed){
    GM.mouse_status_ = MouseStatus::kNothing;
    Label *tmpLabel = POOL.getLabel();
    //If the limit of labels hasn't been reached
    if(tmpLabel != nullptr){
      GM.mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(*GM.window_->sfml_window_));
      GM.scene_->addLabel(*tmpLabel);
      font.loadFromFile("../data/fonts/arial.ttf");
      tmpLabel->init(255,0,0,255,
                     GM.mouse_position_.x,GM.mouse_position_.y,
                     0,1,1,
                     "Hello world", font);
    }
    
  }
  
  ImGui::SFML::Update(*GM.window_->sfml_window_, GM.deltaClock_.restart());
  // TODO: calculate delta
  // TODO: Check input value

  // TODO: Call the rest of update
}

void Game::renderEditor(){
  // TODO: Frameskip control
  // TODO: call the rest of draws
  //We render the UI
  renderUI();
  // render
  GM.window_->clear();

  GM.scene_->drawScene();
  //GM.scene_->getRect(1)->draw(*GM.window_->sfml_window_);
  //GM.scene_->getRect(2)->draw(*GM.window_->sfml_window_);
  //GM.rect_test->draw(*GM.window->sfml_window_);
  //GM.label_test_->draw(*GM.window_->sfml_window_);
  GM.sprite_test_->draw(*GM.window_->sfml_window_);
  

  //GM.scene.zOrderMapRect_

  ImGui::SFML::Render(*GM.window_->sfml_window_);
  GM.window_->display();


  //GameManager::instance().window->Display();
}

void Game::updateGame(){
}

void Game::renderGame(){  
}

void Game::renderUI(){
  UiLoadMenu();      
  ImGui::Begin("Selection");
  if (ImGui::CollapsingHeader("Edit")){
    if(GM.edit_type_ui_ == UiEditType::kRect){
      UiLoadRectValuesEdit(*GM.rect_selection_);
      if (ImGui::Button("DeleteRect")) {
        GM.scene_->removeRect(GM.rect_selection_->id());
        POOL.returnRect(*GM.rect_selection_);
        GM.rect_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }else if(GM.edit_type_ui_ == UiEditType::kLabel){
      UiLoadLabelValuesEdit(*GM.label_selection_);
      if (ImGui::Button("DeleteLabel")) {
        GM.scene_->removeLabel(GM.label_selection_->id());
        POOL.returnLabel(*GM.label_selection_);
        GM.label_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }else if(GM.edit_type_ui_ == UiEditType::kSprite){
      UiLoadCommonValuesEdit(*GM.sprite_selection_);
      if (ImGui::Button("DeleteSprite")) {
        GM.scene_->removeSprite(GM.sprite_selection_->id());
        POOL.returnSprite(*GM.sprite_selection_);
        GM.sprite_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }else if(GM.edit_type_ui_ == UiEditType::kBackground){
      UiLoadBackgroundValuesEdit(*GM.background_selection_);
      if (ImGui::Button("DeleteBackground")) {
        GM.scene_->removeBackground(GM.background_selection_->id());
        POOL.returnBackground(*GM.background_selection_);
        GM.background_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }
  } 
  ImGui::End();
}

void Game::UiLoadCommonValuesEdit(DrawableEntity &d_entity){
  if (ImGui::TreeNode("Position")){
    ImGui::InputFloat("x", &d_entity.position_.x, 1.0f, 1.0f);
    ImGui::InputFloat("y", &d_entity.position_.y, 1.0f, 1.0f);
    ImGui::InputInt("zOrder", &d_entity.z_order_, 1, 1);
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Color")){
    static float color[4] = { 0.f, 0.f, 0.f, 0.f };
    color[0] = static_cast<float>(d_entity.color_.r/255.f);
    color[1] = static_cast<float>(d_entity.color_.g/255.f); 
    color[2] = static_cast<float>(d_entity.color_.b/255.f); 
    color[3] = static_cast<float>(d_entity.color_.a/255.f); 
    if (ImGui::ColorEdit4("Rect Color", color)) {
      d_entity.color_.r = static_cast<sf::Uint8>(color[0] * 255.f);
      d_entity.color_.g = static_cast<sf::Uint8>(color[1] * 255.f);
      d_entity.color_.b = static_cast<sf::Uint8>(color[2] * 255.f);
      d_entity.color_.a = static_cast<sf::Uint8>(color[3] * 255.f);
    }
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Transformation")){
    ImGui::InputFloat("rotation", &d_entity.rotation_, 1.0f, 1.0f);
    ImGui::InputFloat("scalex", &d_entity.scale_.x, 1.0f, 1.0f);
    ImGui::InputFloat("scaley", &d_entity.scale_.y, 1.0f, 1.0f);
    ImGui::TreePop();
  } 
}

void Game::UiLoadRectValuesEdit(Rect &rect){
  static float color[4] = { 0.f, 0.f, 0.f, 0.f };
  UiLoadCommonValuesEdit(rect);
  if (ImGui::TreeNode("BorderColor")){
    color[0] = static_cast<float>(rect.rgba_fill_.r/255.f);
    color[1] = static_cast<float>(rect.rgba_fill_.g/255.f); 
    color[2] = static_cast<float>(rect.rgba_fill_.b/255.f); 
    color[3] = static_cast<float>(rect.rgba_fill_.a/255.f); 
    if (ImGui::ColorEdit4("Rect Color", color)) {
      rect.rgba_fill_.r = static_cast<sf::Uint8>(color[0] * 255.f);
      rect.rgba_fill_.g = static_cast<sf::Uint8>(color[1] * 255.f);
      rect.rgba_fill_.b = static_cast<sf::Uint8>(color[2] * 255.f);
      rect.rgba_fill_.a = static_cast<sf::Uint8>(color[3] * 255.f);
    }
    ImGui::TreePop();
  }
  if(ImGui::TreeNode("Dimensions")){
    ImGui::InputFloat("width", 
    &rect.dimensions_.x, 1.0f, 1.0f);
    ImGui::InputFloat("height", &rect.dimensions_.y, 1.0f, 1.0f);
    static bool is_solid = rect.is_solid_? true : false;
    ImGui::Checkbox("Solid", &is_solid);
    rect.is_solid_ = is_solid? 1 : 0;
    ImGui::TreePop();
  }
}

void Game::UiLoadLabelValuesEdit(Label &label){
  UiLoadCommonValuesEdit(label);
  if (ImGui::TreeNode("label")){
    ImGui::InputInt("font size", &label.font_size_, 1, 1);
    ImGui::InputText("text", label.text_, 50);
    const char* listbox_items[] = { "Arial", "Verdana" };
    static int listbox_item_current = 1;
    ImGui::ListBox("font", &listbox_item_current, listbox_items, 2, 4);
    ImGui::TreePop();
  }
}

void Game::UiLoadBackgroundValuesEdit(Background &bg){
  if (ImGui::TreeNode("movement")){
    static bool scrolls_vertically = bg.scrolls_vertically_? true : false;
    static bool scrolls_horizontally = bg.scrolls_horizontally_? true : false; 
    ImGui::InputInt("speedx", &bg.speed_.x, 1, 1);
    ImGui::InputInt("speedy", &bg.speed_.y, 1, 1);
    ImGui::Checkbox("Scrolls Vertically)", &scrolls_vertically);
    ImGui::Checkbox("Scrolls Horizontally)", &scrolls_horizontally);
    bg.scrolls_vertically_ = scrolls_vertically? 1 : 0;
    bg.scrolls_horizontally_ = scrolls_horizontally? 1 : 0;
    ImGui::TreePop();
  }
}

void Game::UiLoadMenu(){
  ImGui::Begin("Mode");
  //To give a sense of mode selection, we give a redish color when the 
  //button is the currently selected and a blueish one whe it's not.
  if(GM.status_ui_ == UiStatus::kDraw){
    ImGui::PushStyleColor(ImGuiCol_Button, 
                          ImVec4(0.65f,0.14f,0.14f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 
                          ImVec4(0.6f,0.08f,0.08f,1.0f));
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, 
                          ImVec4(0.0f,0.26f,0.69f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                          ImVec4(0.0f,0.21f,0.52f,1.0f)); 
  }
  if (ImGui::Button("Rect create")) {
    if(GM.status_ui_ == UiStatus::kDraw){
      GM.status_ui_ = UiStatus::kIdle;
      GM.ui_is_drawing_ = 0;
    }else{
      GM.status_ui_ = UiStatus::kDraw;
    }
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  if(GM.status_ui_ == UiStatus::kSelection){
    ImGui::PushStyleColor(ImGuiCol_Button, 
                          ImVec4(0.65f,0.14f,0.14f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 
                          ImVec4(0.6f,0.08f,0.08f,1.0f));
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, 
                          ImVec4(0.0f,0.26f,0.69f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                          ImVec4(0.0f,0.21f,0.52f,1.0f)); 
  }
  if (ImGui::Button("Selector")) {
    if(GM.status_ui_ == UiStatus::kSelection){
      GM.status_ui_ = UiStatus::kIdle;
    }else{
      GM.status_ui_ = UiStatus::kSelection;
    }
    GM.ui_is_drawing_ = 0;
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  if(GM.status_ui_ == UiStatus::kWrite){
    ImGui::PushStyleColor(ImGuiCol_Button, 
                          ImVec4(0.65f,0.14f,0.14f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 
                          ImVec4(0.6f,0.08f,0.08f,1.0f));
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, 
                          ImVec4(0.0f,0.26f,0.69f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                          ImVec4(0.0f,0.21f,0.52f,1.0f)); 
  }
  if (ImGui::Button("Text")) {
    if(GM.status_ui_ == UiStatus::kWrite){
      GM.status_ui_ = UiStatus::kIdle;
    }else{
      GM.status_ui_ = UiStatus::kWrite;
    }
    GM.ui_is_drawing_ = 0;
  }
  ImGui::PopStyleColor(2);
  if (ImGui::TreeNode("Scene options")){
    if (ImGui::Button("Load")) {
      
    }
    ImGui::SameLine();
    if (ImGui::Button("Save")) {
      
    }
    ImGui::TreePop();
  }
  ImGui::End();
}