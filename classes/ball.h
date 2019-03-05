#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <math.h>
#include <SFML/Graphics.hpp>

#include "../config.h"

class Ball {
 public:
  Ball() {
    reset();
  }
  ~Ball() {}
  sf::Vector2f getPosition();
  sf::CircleShape getShape();
  void move(float delta_time);
  void reset();

 private:
  float angle_;
  sf::CircleShape circle_shape_;
  float speed_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_
