#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <cstdint>

/** @Brief Class create and manage the windows
*
* This class create and manage the windows of the game editor
*
*/
class  Window{
 public:
  /** @Factory that creates windows
  *
  * Checks that the number of window didn't pass the maxim established.
  * In case the maximum of window has been reached it will return nullptr. 
  *
  * @return Window* returns a pointer to the Window created or nullptr if the 
  *  maximum of windows has been reached
  */
  static Window* CreateWindow(const sf::Vector2u size, const sf::String& title, 
                              unsigned int frameRateLimit = 60);

  /** @Checks if the window is open
  *
  * Checks if the window is open.
  *
  * @return bool returns true if the window is open and false if not.
  */
  bool isOpen();
  /** @Display the window
  *
  * Display on screen the elements that has been rendered to the window so far. 
  *
  * @return void.
  */
  void display();
  /** @Close the window
  *
  * Close the window. 
  *
  * @return void.
  */
  void close();
  /** @Clear the window
  *
  * Clear the window and put it black.
  *
  * @return void.
  */
  void clear();
  
  /** @Draw a drawable object.
  *
  * Draw a drawable object to the render-target.
  *
  * @return void.
  */
  void draw(const sf::Drawable& drawable);

  unsigned int frame_rate_limit_;
  static const uint8_t kMaxWindows = 1;
  sf::RenderWindow *sfml_window_;
  sf::Event event_;
 private:
  Window(const sf::Vector2u size, const sf::String& title, 
         unsigned int frameRateLimit);
  Window();
  ~Window() {};
  Window(const Window& other){};

  static uint8_t total_windows_;
};
#endif