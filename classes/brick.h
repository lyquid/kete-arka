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
  void decreaseResistance(int decrease_by = 1);
  void draw(sf::RenderWindow& window);
  sf::Vector2f getPosition();
  int getResistance();
  sf::RectangleShape getShape();
  sf::Vector2f getSize();
  bool isActive();
  void setActive(bool status);
  void setPosition(sf::Vector2f position);
  void setResistance(int resistance);

 private:
  void init();
  bool active_;
  int resistance_;
  sf::RectangleShape shape_;
};

#endif  // KETE_ARKA_CLASSES_BRICK_H_