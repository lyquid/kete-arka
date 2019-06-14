#ifndef KETE_ARKA_CLASSES_MENU_H_
#define KETE_ARKA_CLASSES_MENU_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Menu {
 public:
  Menu() {
    render_flashing_text_flag_ = true;
  }
  ~Menu() {}
  void drawPauseScreen(sf::RenderWindow& window);
  void drawTitleScreen(sf::RenderWindow& window);
  void init(const sf::Font* font);
  void setRenderFlashingTextFlag(bool status);

 private:
  void initText(sf::Text* text, const sf::String string_text, const sf::Font* font, const int size);
  void checkFlashingTextFlag();
  sf::Clock flashing_text_clock_;
  sf::Text pause_text_;
  sf::Text press_start_text_;
  bool render_flashing_text_flag_;
  sf::Text title_text_;
};

#endif // KETE_ARKA_CLASSES_MENU_H_
