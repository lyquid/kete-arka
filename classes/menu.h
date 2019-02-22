#ifndef KETE_ARKA_CLASSES_MENU_H_
#define KETE_ARKA_CLASSES_MENU_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Menu {
 public:
  Menu() {}
  ~Menu() {}
  void draw(sf::RenderWindow* window);
  void init(sf::Font* font);

 private:
  void initText(sf::Text* text, sf::Font* font, int size);
  sf::Text subtitle_;
  sf::Text title_;
};

#endif // KETE_ARKA_CLASSES_MENU_H_