// Comments can be found at the header
#include "window.h"

uint8_t Window::total_windows_ = 0;
Window::Window(const sf::Vector2u size, const sf::String& title, 
               unsigned int frame_rate_limit){
  sfml_window_ = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title);
  sfml_window_->setFramerateLimit(60);
  frame_rate_limit_ = frame_rate_limit;
  Window::total_windows_++;
}

Window* Window::CreateWindow(const sf::Vector2u size, const sf::String& title, 
                          unsigned int frame_rate_limit){
                            
  if(Window::total_windows_ < kMaxWindows){
    Window* p_window = new Window(size, title, frame_rate_limit);
    return p_window;
  }else{
    return nullptr;
  }
}
 
bool Window::isOpen(){
  return sfml_window_->isOpen();
}
void Window::display(){
  sfml_window_->display();
}
void Window::close(){
  sfml_window_->close();
}
void Window::clear(){
  sfml_window_->clear();
}
void Window::draw(const sf::Drawable& drawable){
  sfml_window_->draw(drawable);
}
/*
sf::RenderWindow getSfmlWindow(){
  return *window;
}*/
