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
  //mouse_status_ = kNothing;
  mouse_position_.x = 0;
  mouse_position_.y = 0;
  draw_origin_point_.x = 0;
  draw_origin_point_.y = 0;
  ui_is_drawing_ = 0;
  //deltaClock_.restart();
  drawing_rect_ = nullptr;

  rect_selection_ = nullptr;
  label_selection_ = nullptr;
  sprite_selection_ = nullptr;
  background_selection_ = nullptr;
  wall_selection_ = nullptr;
  brick_selection_ = nullptr;
  ball_selection_ = nullptr;
  player_selection_ = nullptr;

  ImGui::SFML::Init(window);
}

void UserInterface::update(sf::RenderWindow &window, Scene &scene){
  // Actualizar estados
  if(status_ui_ == kDraw){
    if(GM.mouse_status_ == MouseStatus::kPressed){
      GM.mouse_status_ = MouseStatus::kNothing;
      drawing_rect_ = POOL.getRect();
      //The limit of rects has been reached
      if(drawing_rect_ == nullptr){
        ui_is_drawing_ = 0;
      }else{
        //We insert the rect to the scene
        scene.addDrawableEntity(*drawing_rect_);
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
    }else if(GM.mouse_status_ == MouseStatus::kReleased){
      GM.mouse_status_ = MouseStatus::kNothing;
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
           GM.mouse_status_ == MouseStatus::kPressed){
    GM.mouse_status_ = MouseStatus::kNothing;
    mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(window));
    //We check if there's any entity in the position the user clicked
    GM.selected_id_ = scene.checkCollision(mouse_position_);
    DrawableEntity *aux = scene.getDrawableEntity(GM.selected_id_);
    //We reset all the selection variables of the game manager to nullptr
    background_selection_ = nullptr;
    rect_selection_ = nullptr;
    label_selection_ = nullptr;
    sprite_selection_ = nullptr;
    wall_selection_ = nullptr;
    brick_selection_ = nullptr;
    ball_selection_ = nullptr;
    player_selection_ = nullptr;
    //The click mouse was in an empty position
    if(aux == nullptr){
      edit_type_ui_ = kNull;
      
    }else{
      Entity::Type entity_type = aux->type();
      //We don't want to be able to multi select the background, as there's
      //no sense in moving it
      if(status_ui_ == kMultiselect && entity_type != Entity::kBackground){
        edit_type_ui_ = kMulti;
        aux->selection_tag_ = (aux->selection_tag_)?0 : GM.selected_item_tag_;
      }//We check the type of the drawable entity we have selected and store it
      //in the game manager slection
      else if(entity_type == Entity::kRect){
        edit_type_ui_ = kRect;
        Rect *rect = static_cast<Rect*>(aux);
        rect_selection_ = rect;
      }else if(entity_type == Entity::kBackground){
        edit_type_ui_ = kBackground;
        Background *bg = static_cast<Background*>(aux);
        background_selection_ = bg;
      }else if(entity_type == Entity::kLabel){
        edit_type_ui_ = kLabel;
        Label *label = static_cast<Label*>(aux);
        label_selection_ = label;
      }else if(entity_type == Entity::kSprite){
        edit_type_ui_ = kSprite;
        Sprite *sprite = static_cast<Sprite*>(aux);
        sprite_selection_ = sprite; 
      }else if(entity_type == Entity::kWall){
        edit_type_ui_ = kWall;
        Wall *wall = static_cast<Wall*>(aux);
        wall_selection_ = wall;
      }else if(entity_type == Entity::kBrick){
        edit_type_ui_ = kBrick;
        Brick *brick = static_cast<Brick*>(aux);
        brick_selection_ = brick;
      }else if(entity_type == Entity::kBall){
        edit_type_ui_ = kBall;
        Ball *ball = static_cast<Ball*>(aux);
        ball_selection_ = ball;
      }else if(entity_type == Entity::kPlayer){
        edit_type_ui_ = kPlayer;
        Player *player = static_cast<Player*>(aux);
        player_selection_ = player;
      }
    }
  }
  else if(status_ui_ == kWrite && 
           GM.mouse_status_ == MouseStatus::kPressed){
    GM.mouse_status_ = MouseStatus::kNothing;
    Label *tmp_label = POOL.getLabel();
    //If the limit of labels hasn't been reached
    if(tmp_label != nullptr){
      mouse_position_ = static_cast<sf::Vector2f>(
                       sf::Mouse::getPosition(window));
                       scene.addDrawableEntity(*tmp_label);
      tmp_label->init(255,0,0,255,
                     mouse_position_.x,mouse_position_.y,
                     0,1,1,
                     "Hello world", GM.arial_);
    }
  }
  
  ImGui::SFML::Update(window, GM.deltaClock_.restart());
}

void UserInterface::renderUI(sf::RenderWindow &window, Scene &scene){
  UiLoadMenu(scene);    
  UiStartGameMenu();
  //UiTextureManager();
  ImGui::Begin("Selection");
  if (ImGui::CollapsingHeader("Edit")){
    static int32_t ui_z_order = 0;
    if(edit_type_ui_ == kRect){
      UiLoadRectValuesEdit(*rect_selection_);
      ImGui::Text("The actual z-order is: %i", rect_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(rect_selection_->id(),
                                              ui_z_order);
      }
      if (ImGui::Button("DeleteRect")) {
        scene.removeDrawableEntity(rect_selection_->id());
        POOL.returnRect(*rect_selection_);
        rect_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kLabel){
      UiLoadLabelValuesEdit(*label_selection_);
      ImGui::Text("The actual z-order is: %i", label_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(label_selection_->id(),
                                              ui_z_order);
      }
      if (ImGui::Button("DeleteLabel")) {
        scene.removeDrawableEntity(label_selection_->id());
        POOL.returnLabel(*label_selection_);
        label_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kSprite){
      UiLoadCommonValuesEdit(*sprite_selection_);
      ImGui::Text("The actual z-order is: %i", sprite_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(sprite_selection_->id(),
                                              ui_z_order);
      }
      if (ImGui::Button("DeleteSprite")) {
        scene.removeDrawableEntity(sprite_selection_->id());
        POOL.returnSprite(*sprite_selection_);
        sprite_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kBackground){
      UiLoadBackgroundValuesEdit(*background_selection_);
      ImGui::Text("The actual z-order is: %i", 
                  background_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(background_selection_->id(),
                                              ui_z_order);
      }
      if (ImGui::Button("DeleteBackground")) {
        scene.removeDrawableEntity(background_selection_->id());
        POOL.returnBackground(*background_selection_);
        background_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kWall){
      UiLoadRectValuesEdit(*wall_selection_);
      ImGui::Text("The actual z-order is: %i", 
                  wall_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(wall_selection_->id(),
                                          ui_z_order);
      }
      if (ImGui::Button("DeleteWall")) {
        scene.removeDrawableEntity(wall_selection_->id());
        POOL.returnWall(*wall_selection_);
        wall_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kBrick){
      UiLoadRectValuesEdit(*brick_selection_);
      UiLoadBrickValuesEdit(*brick_selection_);
      ImGui::Text("The actual z-order is: %i", 
                  brick_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(brick_selection_->id(),
                                          ui_z_order);
      }
      if (ImGui::Button("DeleteBrick")) {
        scene.removeDrawableEntity(brick_selection_->id());
        POOL.returnBrick(*brick_selection_);
        brick_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kBall){
      UiLoadCommonValuesEdit(*ball_selection_);
      UiLoadBallValuesEdit(*ball_selection_);
      ImGui::Text("The actual z-order is: %i", 
                  ball_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(ball_selection_->id(),
                                          ui_z_order);
      }
      if (ImGui::Button("DeleteBall")) {
        scene.removeDrawableEntity(ball_selection_->id());
        POOL.returnBall(*ball_selection_);
        ball_selection_ = nullptr;
        edit_type_ui_ = kNull;
      }
    }else if(edit_type_ui_ == kPlayer){
      UiLoadCommonValuesEdit(*player_selection_);
      UiLoadPlayerValuesEdit(*player_selection_);
      ImGui::Text("The actual z-order is: %i", 
                  player_selection_->z_order_);
      ImGui::InputInt("New z-order", &ui_z_order, 1, 1);
      if(ImGui::Button("change z-order")){
        scene.changeZOrderDrawableEntity(player_selection_->id(),
                                          ui_z_order);
      }
      if (ImGui::Button("DeletePlayer")) {
        scene.removeDrawableEntity(player_selection_->id());
        POOL.returnPlayer(*player_selection_);
        player_selection_ = nullptr;
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
        scene.getDrawableEntitiesByTag(GM.selected_item_tag_);
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
  if (ImGui::TreeNode("Tag")){
    ImGui::InputInt("tag", &d_entity.tag_, 1.0f, 1.0f);
    ImGui::TreePop();
  } 
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

void UserInterface::UiLoadPlayerValuesEdit(Player &player){
  if (ImGui::TreeNode("speed player")){
    ImGui::InputInt("speedx", &player.speed_.x, 1, 1);
    ImGui::InputInt("speedy", &player.speed_.y, 1, 1);
    ImGui::TreePop();
  }
}

void UserInterface::UiLoadBallValuesEdit(Ball &ball){
  if (ImGui::TreeNode("speed ball")){
    ImGui::InputInt("speedx", &ball.speed_.x, 1, 1);
    ImGui::InputInt("speedy", &ball.speed_.y, 1, 1);
    ImGui::TreePop();
  }
}

void UserInterface::UiLoadBrickValuesEdit(Brick &brick){
  if (ImGui::TreeNode("lives brick")){
    ImGui::InputInt("lives", &brick.lives_, 1, 1);
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

void UserInterface::UiLoadMenu(Scene &scene){
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
      //GM.scene_->loadScene("../data/scene.json", GM.arial_);
      std::string path = "";
      path = GM.native_dialog_->openFileDialog(
          "Select the scene to load",
          "../data/",
          1,
          kFilterPatternsJson,
          NULL);
      if (path != "") {
        scene.loadScene(path, GM.arial_);
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
        scene.saveScene(path);
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
        std::string str("2d_engine");        
        std::size_t found = path.find(str);        
        path.replace(found, 9, "..");        
        path = path.substr(found);
        
        Background *tmp_bg = POOL.getBackground();
        //If the limit of backgrounds hasn't been reached
        if(tmp_bg != nullptr){
          scene.addDrawableEntity(*tmp_bg);
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
        std::string str("2d_engine");        
        std::size_t found = path.find(str);        
        path.replace(found, 9, "..");        
        path = path.substr(found);

        Sprite *tmp_sprite = POOL.getSprite();
        //If the limit of sprites hasn't been reached
        if(tmp_sprite != nullptr){
          scene.addDrawableEntity(*tmp_sprite);
          tmp_sprite->init(0,0,
                           0,1,1,
                           path);
        }
      }
    }
    ImGui::TreePop();
  }
  if(ImGui::TreeNode("Game objects creation")){
    if (ImGui::Button("Player")) {
      std::string path = "";
      path = GM.native_dialog_->openFileDialog(
          "Select an image for the player",
          "../data/",
          3,
          kFilterPatternsImage,
          NULL);
      if (path != "") {
        std::string str("2d_engine");        
        std::size_t found = path.find(str);        
        path.replace(found, 9, "..");        
        path = path.substr(found);

        Player *tmp_player = POOL.getPlayer();
        //If the limit of sprites hasn't been reached
        if(tmp_player != nullptr){
          scene.addDrawableEntity(*tmp_player);
          tmp_player->init(0,0,
                           1,1,
                           1,1,
                           path);
        }
      }
    }
    if (ImGui::Button("Ball")) {
      std::string path = "";
      path = GM.native_dialog_->openFileDialog(
          "Select an image for the ball",
          "../data/",
          3,
          kFilterPatternsImage,
          NULL);
      if (path != "") {
        std::string str("2d_engine");        
        std::size_t found = path.find(str);        
        path.replace(found, 9, "..");        
        path = path.substr(found);

        Ball *tmp_ball = POOL.getBall();
        //If the limit of sprites hasn't been reached
        if(tmp_ball != nullptr){
          scene.addDrawableEntity(*tmp_ball);
          tmp_ball->init(0,0,
                         1,1,
                         1,1,
                         path);
        }
      }
    }
    if (ImGui::Button("Brick")) {
      Brick *tmp_brick = POOL.getBrick();
      //If the limit of sprites hasn't been reached
      if(tmp_brick != nullptr){
        scene.addDrawableEntity(*tmp_brick);
        tmp_brick->init(70,40,
                       255,0,0,255,
                       0,255,0,255,
                       0,0,0,
                       1,1,1);
      }
    }
    if (ImGui::Button("Wall")) {
      Wall *tmp_wall = POOL.getWall();
      //If the limit of sprites hasn't been reached
      if(tmp_wall != nullptr){
        scene.addDrawableEntity(*tmp_wall);
        tmp_wall->init(30,796,
                       255,0,0,255,
                       0,255,0,255,
                       2,2,0,
                       1,1);
      }
    }
    ImGui::TreePop();
  }
  ImGui::End();
}

/*void UserInterface::UiTextureManager(){
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
}*/