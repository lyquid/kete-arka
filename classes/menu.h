#ifndef KETE_ARKA_CLASSES_MENU_H_
#define KETE_ARKA_CLASSES_MENU_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Menu {
 public:
  Menu() {}
  ~Menu() {}
  void drawPauseScreen(sf::RenderWindow* window);
  void drawTitleScreen(sf::RenderWindow* window);
  void init(const sf::Font* font);

 private:
  void initText(sf::Text* text, const sf::String string_text, const sf::Font* font, const int size);
  sf::Text press_start_text_;
  sf::Text title_text_;
  sf::Text pause_text_;
};

#endif // KETE_ARKA_CLASSES_MENU_H_
