#ifndef KETE_ARKA_CLASSES_SHIP_H_
#define KETE_ARKA_CLASSES_SHIP_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Ship {
 public:
  Ship() {
    init();
  }
  ~Ship() {}
  sf::RectangleShape getShape();

 private:
  void init();
  bool moveLeft();
  bool moveRight();
  sf::RectangleShape ship_shape_;
  float speed_;
};

#endif  // KETE_ARKA_CLASSES_SHIP_H_
