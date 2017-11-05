#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <cstdint>

class  Window{
 public:
  static Window* CreateWindow(const sf::Vector2u size, const sf::String& title, 
                              unsigned int frameRateLimit = 60);
  // GUSTAVO: Please remember that method names go normally likeThisExample()
  bool isOpen();
  void display();
  void close();
  void clear();
  void draw(const sf::Drawable& drawable);
  //sf::RenderWindow getSfmlWindow();

  static const uint8_t kMaxWindows = 1;
  unsigned int frame_rate_limit_;
  sf::RenderWindow *sfml_window_;
 private:
  Window(const sf::Vector2u size, const sf::String& title, 
         unsigned int frameRateLimit);
  Window() {};
  Window(const Window& other){};

  sf::Event event_;
  static uint8_t total_windows_;
};
#endif