#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>

class  Window{
 public:
  Window() {};
  void CreateWindow(const sf::Vector2u size, const sf::String& title, 
                    unsigned int frameRateLimit = 60);
  bool IsOpen();
  void Display();
  void Close();
  void Clear();
  void Draw(const sf::Drawable& drawable);
  //sf::RenderWindow getSfmlWindow();

  unsigned int frameRateLimit_;
  sf::RenderWindow *sfml_window_;

 private:
  sf::Event event;
  Window(const Window& other){};
};
#endif