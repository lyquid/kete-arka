#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "../config.h"
#include "brick.h"
#include "logger.h"
#include "ship.h"

template <typename T> std::string toString(const T& t);

class Ball {
 public:
  Ball() {
    reset();
  }
  ~Ball() {}
  void draw(sf::RenderWindow& window);
  void move(const float delta_time, Ship ship, Brick brick);
  void reset();

 private:
  bool checkBrickCollision(Brick brick);
  bool checkBorderCollision();
  bool checkMachineWins();
  bool checkShipCollision(Ship ship);
  void invertHorizontalDirection(const float variation);
  void invertVerticalDirection(const float variation);
  void randomizeBounceAngle(const Collisions collision);  
  static float sumAbs(const float num1, const float num2);
  float current_radius_;
  sf::Vector2f direction_;
  sf::Vector2f last_position_;
  sf::CircleShape shape_;
  float speed_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_