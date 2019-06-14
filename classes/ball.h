#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Ball {
 public:
  Ball() {
    reset();
  }
  ~Ball() {}
  void draw(sf::RenderWindow& window);
  void move(float delta_time);
  void reset();

 private:
  bool checkBoundaryCollision();
  bool checkMachineWins();
  sf::CircleShape ball_shape_;
  sf::Vector2f direction_;
  float speed_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_
