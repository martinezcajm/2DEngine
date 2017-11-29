// user_interface.cc
// Jose Maria Martinez
// Implementation of the functions to control the user interface of the app

#include "imgui.h"
#include "imgui-SFML.h"
#include "user_interface.h"


UserInterface::UserInterface(){};

UserInterface::~UserInterface(){};

void UserInterface::renderUI(){
  UiLoadMenu();    
  UiStartGameMenu();
  ImGui::Begin("Selection");
  if (ImGui::CollapsingHeader("Edit")){
    static int32_t ui_z_order = 0;
    if(GM.edit_type_ui_ == UiEditType::kRect){
      UiLoadRectValuesEdit(*GM.rect_selection_);
      ImGui::Text("The actual z-order is: %i", GM.rect_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderRect(GM.rect_selection_->id(),ui_z_order);
      }
      if (ImGui::Button("DeleteRect")) {
        GM.scene_->removeRect(GM.rect_selection_->id());
        POOL.returnRect(*GM.rect_selection_);
        GM.rect_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }else if(GM.edit_type_ui_ == UiEditType::kLabel){
      UiLoadLabelValuesEdit(*GM.label_selection_);
      ImGui::Text("The actual z-order is: %i", GM.label_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderLabel(GM.label_selection_->id(),ui_z_order);
      }
      if (ImGui::Button("DeleteLabel")) {
        GM.scene_->removeLabel(GM.label_selection_->id());
        POOL.returnLabel(*GM.label_selection_);
        GM.label_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }else if(GM.edit_type_ui_ == UiEditType::kSprite){
      UiLoadCommonValuesEdit(*GM.sprite_selection_);
      ImGui::Text("The actual z-order is: %i", GM.sprite_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderSprite(GM.sprite_selection_->id(),ui_z_order);
      }
      if (ImGui::Button("DeleteSprite")) {
        GM.scene_->removeSprite(GM.sprite_selection_->id());
        POOL.returnSprite(*GM.sprite_selection_);
        GM.sprite_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }else if(GM.edit_type_ui_ == UiEditType::kBackground){
      UiLoadBackgroundValuesEdit(*GM.background_selection_);
      ImGui::Text("The actual z-order is: %i", 
                  GM.background_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        GM.scene_->changeZOrderBackground(GM.background_selection_->id(),
                                          ui_z_order);
      }
      if (ImGui::Button("DeleteBackground")) {
        GM.scene_->removeBackground(GM.background_selection_->id());
        POOL.returnBackground(*GM.background_selection_);
        GM.background_selection_ = nullptr;
        GM.edit_type_ui_ = UiEditType::kNull;
      }
    }else if(GM.edit_type_ui_ == UiEditType::kMulti){
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
  if(GM.status_ui_ == UiStatus::kMultiselect){
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
    if(GM.status_ui_ == UiStatus::kMultiselect){
      GM.status_ui_ = UiStatus::kIdle;
      GM.edit_type_ui_ = UiEditType::kNull;
      GM.ui_is_drawing_ = 0;
    }else{
      GM.status_ui_ = UiStatus::kMultiselect;
      GM.edit_type_ui_ = UiEditType::kMulti;
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
          GM.scene_->addBackground(*tmp_bg);
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
          GM.scene_->addSprite(*tmp_sprite);
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