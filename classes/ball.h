#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <cmath>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "../config.h"
#include "ship.h"

class Ball {
 public:
  Ball() {
    reset();
  }
  ~Ball() {}
  void draw(sf::RenderWindow& window);
  void move(const float delta_time, Ship ship);
  void reset();

 private:
  bool checkBorderCollision();
  bool checkMachineWins();
  bool checkShipCollision(Ship ship);
  void randomizeBounceAngle(const Borders border);  
  sf::Vector2f direction_;
  sf::Vector2f last_position_;
  sf::CircleShape shape_;
  float speed_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_