#ifndef KETE_ARKA_CLASSES_GUI_H_
#define KETE_ARKA_CLASSES_GUI_H_

#include "../config.h"

class GUI {
 public:
  GUI() {}
  ~GUI() {}
  void draw(sf::RenderWindow &window);
  void init(const sf::Font &font);
  static void initText( sf::Text          &text, 
                        const sf::String  string_text, 
                        const sf::Font    &font, 
                        const int         size, 
                        const sf::Color   color, 
                        const bool        centered );
 private:
  void initLayout();
  sf::RectangleShape left_;
  sf::RectangleShape middle_;
  sf::RectangleShape right_;
  sf::Text level_text_;
  sf::Text lives_text_;
  sf::Text score_text_;
};

#endif  // KETE_ARKA_CLASSES_GUI_H_