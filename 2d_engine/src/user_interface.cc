// user_interface.cc
// Jose Maria Martinez
// Implementation of the functions to control the user interface of the app

#include "imgui.h"
#include "imgui-SFML.h"
#include "user_interface.h"
//#include <SFML/Graphics.hpp>


UserInterface::UserInterface(){};

UserInterface::~UserInterface(){
  ImGui::SFML::Shutdown();
};

void UserInterface::init(sf::RenderWindow &window){
  status_ui_ = kIdle;
  edit_type_ui_ = kNull;
  mouse_status_ = kNothing;
  mouse_position_.x = 0;
  mouse_position_.y = 0;
  draw_origin_point_.x = 0;
  draw_origin_point_.y = 0;
  ui_is_drawing_ = 0;
  deltaClock_.restart();
  drawing_rect_ = nullptr;
  ImGui::SFML::Init(window);
}
//TODO First basic refactoring check if event is necessary
void UserInterface::processInput(sf::RenderWindow &window, sf::Event &event){

  //We check sfml and imgui events
  while (window.pollEvent(event)){
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left &&
        !ImGui::IsAnyWindowHovered()) {
      mouse_status_ = kPressed;
    }
    if (event.type == sf::Event::MouseButtonReleased && 
        event.mouseButton.button == sf::Mouse::Left ) {
      mouse_status_ = kReleased;
    }
    if (event.type == sf::Event::Closed) {
      window.close();
      GM.game_over_ = 1;
    }
    if(event.type == sf::Event::KeyPressed){  
      // Exit if press ESC    
      if (event.key.code == sf::Keyboard::Escape)
      {
        window.close();
        GM.game_over_ = 1;
      }
    }
  }
}

void UserInterface::update(sf::RenderWindow &window){
  // Actualizar estados
  if(status_ui_ == kDraw){
    if(mouse_status_ == kPressed){
      mouse_status_ = kNothing;
      drawing_rect_ = POOL.getRect();
      //The limit of rects has been reached
      if(drawing_rect_ == nullptr){
        ui_is_drawing_ = 0;
      }else{
        //We insert the rect to the scene
        GM.scene_->addDrawableEntity(*drawing_rect_);
        ui_is_drawing_ = 1;
        draw_origin_point_ = static_cast<sf::Vector2f>(
                      sf::Mouse::getPosition(window));
        drawing_rect_->init(1,
           0,0, 
           255,0,0,255,
           0,255,0,255,
           draw_origin_point_.x, draw_origin_point_.y,
           0,1,1);
      }
    }else if(mouse_status_ == kReleased){
      mouse_status_ = kNothing;
      if(ui_is_drawing_){
        ui_is_drawing_ = 0;
        mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(window));
        drawing_rect_->resize(
                 mouse_position_.x - draw_origin_point_.x,
                 mouse_position_.y - draw_origin_point_.y);
        
      }
    }
    if(ui_is_drawing_){
      mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(window));
      drawing_rect_->resize(mouse_position_.x - draw_origin_point_.x,
                            mouse_position_.y - draw_origin_point_.y);
    }
  }else if((status_ui_ == kSelection|| 
          status_ui_ == kMultiselect) && 
           mouse_status_ == kPressed){
    mouse_status_ = kNothing;
    mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(window));
    GM.selected_id_ = GM.scene_-> checkCollision(mouse_position_);
    //Get Drawable 
    // 0 - nothing
      // 1 - Background
      // 2 - Rect
      // 3 - Label
      // 4 - Sprite
    /*if(GM.selected_type_ == 0){
      edit_type_ui_ = UiEditType::kNull;
      GM.background_selection_ = nullptr;
      GM.rect_selection_ = nullptr;
      GM.label_selection_ = nullptr;
      GM.sprite_selection_ = nullptr;
    }else if(GM.selected_type_ == 1){
      GM.background_selection_ = GM.scene_->getBackground(GM.selected_id_);
      if(status_ui_ == kSelection){
        edit_type_ui_ = kBackground;
        GM.rect_selection_ = nullptr;
        GM.label_selection_ = nullptr;
        GM.sprite_selection_ = nullptr;
      }
      //We don't want to be able to multi select the background, as there's
      //no sense in moving it
    }else if(GM.selected_type_ == 2){
      GM.rect_selection_ = GM.scene_->getRect(GM.selected_id_);
      if(status_ui_ == kSelection){
        edit_type_ui_ = kRect;
        GM.background_selection_ = nullptr;
        GM.label_selection_ = nullptr;
        GM.sprite_selection_ = nullptr;
      }else if(status_ui_ == kMultiselect){
        edit_type_ui_ = kMulti;
        GM.rect_selection_->tag_ = (GM.rect_selection_->tag_) ?
                                    0 : GM.selected_item_tag_;
      }
    } else if(GM.selected_type_ == 3){
      GM.label_selection_ = GM.scene_->getLabel(GM.selected_id_);
      if(status_ui_ == kSelection){
        edit_type_ui_ = kLabel;
        GM.background_selection_ = nullptr;
        GM.rect_selection_ = nullptr;
        GM.sprite_selection_ = nullptr;
      }else if(status_ui_ == kMultiselect){
        edit_type_ui_ = kMulti;
        GM.label_selection_->tag_ = (GM.label_selection_->tag_) ?
                                     0 : GM.selected_item_tag_;
      }
    } else if(GM.selected_type_ == 4){
      GM.sprite_selection_ = GM.scene_->getSprite(GM.selected_id_); 
      if(status_ui_ == kSelection){
        edit_type_ui_ = kSprite;
        GM.background_selection_ = nullptr;
        GM.rect_selection_ = nullptr;
        GM.label_selection_ = nullptr;        
      }else if(status_ui_ == kMultiselect){
        edit_type_ui_ = kMulti;
        GM.sprite_selection_->tag_ = (GM.sprite_selection_->tag_) ?
                                      0 : GM.selected_item_tag_;
      }      
    }*/
  }
  else if(status_ui_ == kWrite && 
           mouse_status_ == kPressed){
    mouse_status_ = kNothing;
    Label *tmp_label = POOL.getLabel();
    //If the limit of labels hasn't been reached
    if(tmp_label != nullptr){
      mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(window));
      GM.scene_->addDrawableEntity(*tmp_label);
      tmp_label->init(255,0,0,255,
                     mouse_position_.x,mouse_position_.y,
                     0,1,1,
                     "Hello world", GM.arial_);
    }
  }
  
  ImGui::SFML::Update(window, deltaClock_.restart());
}

void UserInterface::renderUI(sf::RenderWindow &window){
  UiLoadMenu();    
  UiStartGameMenu();
  UiTextureManager();
  ImGui::Begin("Selection");
  if (ImGui::CollapsingHeader("Edit")){
    static int32_t ui_z_order = 0;
    if(edit_type_ui_ == kRect){
      UiLoadRectValuesEdit(*GM.rect_selection_);
      ImGui::Text("The actual z-order is: %i", GM.rect_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderDrawableEntity(GM.rect_selection_->id(),ui_z_order);
      }
      if (ImGui::Button("DeleteRect")) {
        GM.scene_->removeDrawableEntity(GM.rect_selection_->id());
        POOL.returnRect(*GM.rect_selection_);
        GM.rect_selection_ = nullptr;
        edit_type_ui_ = UiEditType::kNull;
      }
    }else if(edit_type_ui_ == kLabel){
      UiLoadLabelValuesEdit(*GM.label_selection_);
      ImGui::Text("The actual z-order is: %i", GM.label_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderDrawableEntity(GM.label_selection_->id(),ui_z_order);
      }
      if (ImGui::Button("DeleteLabel")) {
        GM.scene_->removeDrawableEntity(GM.label_selection_->id());
        POOL.returnLabel(*GM.label_selection_);
        GM.label_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kSprite){
      UiLoadCommonValuesEdit(*GM.sprite_selection_);
      ImGui::Text("The actual z-order is: %i", GM.sprite_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderDrawableEntity(GM.sprite_selection_->id(),ui_z_order);
      }
      if (ImGui::Button("DeleteSprite")) {
        GM.scene_->removeDrawableEntity(GM.sprite_selection_->id());
        POOL.returnSprite(*GM.sprite_selection_);
        GM.sprite_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kBackground){
      UiLoadBackgroundValuesEdit(*GM.background_selection_);
      ImGui::Text("The actual z-order is: %i", 
                  GM.background_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderDrawableEntity(GM.background_selection_->id(),
                                          ui_z_order);
      }
      if (ImGui::Button("DeleteBackground")) {
        GM.scene_->removeDrawableEntity(GM.background_selection_->id());
        POOL.returnBackground(*GM.background_selection_);
        GM.background_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kMulti){
      static float px = 0.0f;
      static float py = 0.0f;
      if (ImGui::TreeNode("Movement")){
        ImGui::InputFloat("x", &px, 1.0f, 1.0f);
        ImGui::InputFloat("y", &py, 1.0f, 1.0f);
        ImGui::TreePop();
      }
      if (ImGui::Button("Move selected items")) {
        std::list<DrawableEntity*> selected = 
                  GM.scene_->getDrawableEntitiesByTag(GM.selected_item_tag_);
        for (std::list<DrawableEntity*>::const_iterator it =
             selected.begin(); it != selected.end(); ++it) {
          (*it)->move(px, py);
        }
      }
    }
  } 
  ImGui::End();
  ImGui::SFML::Render(window);
}

void UserInterface::UiLoadCommonValuesEdit(DrawableEntity &d_entity){
  if (ImGui::TreeNode("Position")){
    ImGui::InputFloat("x", &d_entity.position_.x, 1.0f, 1.0f);
    ImGui::InputFloat("y", &d_entity.position_.y, 1.0f, 1.0f);
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

void UserInterface::UiLoadRectValuesEdit(Rect &rect){
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

void UserInterface::UiLoadLabelValuesEdit(Label &label){
  UiLoadCommonValuesEdit(label);
  if (ImGui::TreeNode("label")){
    ImGui::InputText("text", label.text_, 50);
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Font")){
    ImGui::InputInt("font size", &label.font_size_, 1, 1);
    if (ImGui::Button("Arial")) {
      label.set_font(GM.arial_);
    }
    ImGui::SameLine();
    if (ImGui::Button("Verdana")) {
      label.set_font(GM.verdana_);
    }
    ImGui::TreePop();
  }
}

void UserInterface::UiLoadBackgroundValuesEdit(Background &bg){
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

void UserInterface::UiStartGameMenu(){
  ImGui::Begin("GameMode");
  if(ImGui::Button("GameStart")){
    GM.is_editor_ = !GM.is_editor_;
  }
  ImGui::End();
}

void UserInterface::UiLoadMenu(){
  ImGui::Begin("Mode");
  //To give a sense of mode selection, we give a redish color when the 
  //button is the currently selected and a blueish one whe it's not.
  if(status_ui_ == kDraw){
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
    if(status_ui_ == kDraw){
      status_ui_ = kIdle;
      ui_is_drawing_ = 0;
    }else{
      status_ui_ = kDraw;
    }
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  if(status_ui_ == kSelection){
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
    if(status_ui_ == kSelection){
      status_ui_ = kIdle;
    }else{
      status_ui_ = kSelection;
    }
    ui_is_drawing_ = 0;
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  if(status_ui_ == kWrite){
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
    if(status_ui_ == kWrite){
      status_ui_ = kIdle;
    }else{
      status_ui_ = kWrite;
    }
    ui_is_drawing_ = 0;
  }
  ImGui::PopStyleColor(2);
  if(status_ui_ == kMultiselect){
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
  if (ImGui::Button("Multi Selection")) {
    if(status_ui_ == kMultiselect){
      status_ui_ = kIdle;
      edit_type_ui_ = kNull;
      ui_is_drawing_ = 0;
    }else{
      status_ui_ = kMultiselect;
      edit_type_ui_ = kMulti;
    }
  }
  ImGui::PopStyleColor(2);
  if (ImGui::TreeNode("Scene options")){
    if (ImGui::Button("Load")) {
      GM.scene_->loadScene("../data/scene.json", GM.arial_);
      std::string path = "";
      path = GM.native_dialog_->openFileDialog(
          "Select the scene to load",
          "../data/",
          1,
          kFilterPatternsJson,
          NULL);
      if (path != "") {
        GM.scene_->loadScene(path, GM.arial_);
      }
    }
    ImGui::SameLine();
    if (ImGui::Button("Save")) {
      std::string path = "";
      //GM.scene_->saveScene("scene.json");   
      path = GM.native_dialog_->saveFileDialog(
          "Save scene as",
          "../data/scene.json",
          1,
          kFilterPatternsJson,
          NULL);
      if (path != "") {
        GM.scene_->saveScene(path);
      }
    }
    ImGui::TreePop();
  }
  if(ImGui::TreeNode("Graphics creation")){
    if (ImGui::Button("Background")) {
      std::string path = "";
      path = GM.native_dialog_->openFileDialog(
          "Select an image for the background",
          "../data/",
          3,
          kFilterPatternsImage,
          NULL);
      if (path != "") {
        Background *tmp_bg = POOL.getBackground();
        //If the limit of backgrounds hasn't been reached
        if(tmp_bg != nullptr){
          GM.scene_->addDrawableEntity(*tmp_bg);
          tmp_bg->init(path,
                       GM.window_->sfml_window_->getSize().x,
                       GM.window_->sfml_window_->getSize().y);
        }
      }
    }
    if (ImGui::Button("Sprite")) {
      std::string path = "";
      path = GM.native_dialog_->openFileDialog(
          "Select an image for the sprite",
          "../data/",
          3,
          kFilterPatternsImage,
          NULL);
      if (path != "") {
        Sprite *tmp_sprite = POOL.getSprite();
        //If the limit of sprites hasn't been reached
        if(tmp_sprite != nullptr){
          GM.scene_->addDrawableEntity(*tmp_sprite);
          tmp_sprite->init(0,0,
                           0,1,1,
                           path);
        }
      }
    }
    ImGui::TreePop();
  }
  ImGui::End();
}

void UserInterface::UiTextureManager(){
  ImGui::Begin("Textures");
  const char* listbox_items[] = { "Texture1", "Texture2", "Texture3"};
            static int listbox_item_current = 1;
            ImGui::ListBox("", &listbox_item_current, listbox_items, 3, 3);
  if (ImGui::Button("Create Texture")) {
    std::string path = "";
    path = GM.native_dialog_->openFileDialog(
        "Select an image for the texture",
        "../data/",
        3,
        kFilterPatternsImage,
        NULL);
    if (path != "") {
      sf::Texture *tmp_texture = nullptr;
      tmp_texture = GM.scene_->getTexture(path);
      if(tmp_texture == nullptr){
        tmp_texture->loadFromFile(path);
        GM.scene_->addTexture(*tmp_texture, path);
      }else{
        //The texture already exists. TODO open an error window
      }
    }
  }
  if(ImGui::Button("Sprite from texture")){

  }
  ImGui::End();
}

/*
  sf::Texture texture;
  texture.loadFromFile("../data/enemy.png");
  GM.scene_->addSprite(*sprite_test);
  Sprite *sprite_test2 = POOL.getSprite();
  uint8_t error;
  sprite_test2->init(300,400,0,1,1,texture,error);
  GM.scene_->addSprite(*sprite_test2);
  */