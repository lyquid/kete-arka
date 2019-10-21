#ifndef KETE_ARKA_CLASSES_BRICK_H_
#define KETE_ARKA_CLASSES_BRICK_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Brick {
 public:
  Brick() {
    init();
  }
  ~Brick() {}
  void draw(sf::RenderWindow& window);
  sf::RectangleShape getBrickShape();
  sf::Vector2f getBrickSize();

 private:
  void init();
  sf::RectangleShape shape_;
};

#endif  // KETE_ARKA_CLASSES_BRICK_H_