#ifndef KETE_ARKA_CLASSES_GUI_H_
#define KETE_ARKA_CLASSES_GUI_H_

#include "../config.h"

class GUI {
 public:
  GUI() {
    init();
  }
  ~GUI() {}
  void draw(sf::RenderWindow &window);

 private:
  void init();
  sf::RectangleShape left_;
  sf::RectangleShape middle_;
  sf::RectangleShape right_;
};

#endif  // KETE_ARKA_CLASSES_GUI_H_