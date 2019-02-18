#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <SFML/Graphics.hpp>

class Ball {
 public:
  Ball() {}
  ~Ball() {}

  void create(sf::Vector2f position, float radius);
  sf::Vector2f getPosition();
  float getRadius();
  void setPosition(sf::Vector2f position);
  void setRadius(float radius);

 private:
  sf::Vector2f position;
  float radius = 10.f;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_
