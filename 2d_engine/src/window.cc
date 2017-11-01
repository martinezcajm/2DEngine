#include "window.h"

void Window::CreateWindow(const sf::Vector2u size, const sf::String& title, 
                          unsigned int frameRateLimit){
  sfml_window_ = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title);
  sfml_window_->setFramerateLimit(60);
  frameRateLimit_ = frameRateLimit;
}
 
bool Window::IsOpen(){
  while (sfml_window_->pollEvent(event))
  {
    //ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed){
      sfml_window_->close();
    }
  }

  return sfml_window_->isOpen();

}
void Window::Display(){
  sfml_window_->display();
}
void Window::Close(){
  sfml_window_->close();
}
void Window::Clear(){
  sfml_window_->clear();
}
void Window::Draw(const sf::Drawable& drawable){
  sfml_window_->draw(drawable);
}
/*
sf::RenderWindow getSfmlWindow(){
  return *window;
}*/
