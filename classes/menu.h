#ifndef KETE_ARKA_CLASSES_MENU_H_
#define KETE_ARKA_CLASSES_MENU_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Menu {
 public:
  Menu() {
    render_press_start_text_ = true;
  }
  ~Menu() {}
  void drawPauseScreen(sf::RenderWindow* window);
  void drawTitleScreen(sf::RenderWindow* window);
  void init(const sf::Font* font);

 private:
  void initText(sf::Text* text, const sf::String string_text, const sf::Font* font, const int size);
  void setFlashingPressStartText();
  sf::Text pause_text_;
  sf::Clock press_start_flashing_clock_;
  sf::Text press_start_text_;
  bool render_press_start_text_;
  sf::Text title_text_;
};

#endif // KETE_ARKA_CLASSES_MENU_H_
