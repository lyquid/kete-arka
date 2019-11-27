#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <cmath>
#include <iostream>

#include "../config.h"
#include "brick.h"
#include "logger.h"
#include "player.h"
#include "ship.h"

class Ball {
 public:
  Ball() {}
  ~Ball() {}
  void draw(sf::RenderWindow &window);
  void init(Player *ptp, Ship *pts);
  void move(const float delta_time, Ship ship, Brick bricks[][kBrickDefaultColumns]);
  void reset();

 private:
  bool checkBrickCollision(Brick bricks[][kBrickDefaultColumns]);
  bool checkBorderCollision();
  bool checkShipCollision(Ship ship);
  void invertHorizontalDirection(const float variation);
  void invertVerticalDirection(const float variation);
  void randomizeBounceAngle(const Collisions collision);
  void updateFlashFlag();
  static float sumAbs(const float num1, const float num2);
  bool ball_flash_flag_;
  float current_radius_;
  sf::Vector2f direction_;
  sf::Clock flash_clock_;
  sf::Vector2f last_position_;
  bool moving_flag_;
  Player *player_;
  Ship *ship_;
  sf::Clock start_clock_;
  sf::CircleShape shape_;
  float speed_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_