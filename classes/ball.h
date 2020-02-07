#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <SFML/Graphics.hpp>

#include <chrono>
#include <cmath>    // std::abs
#include <iostream> // std::cout
#include <random>

#include "../config.h"
#include "level.h"
#include "logger.h"
#include "player.h"

class Ball {
 public:
  Ball():
    pwrup_active_(false) {}
  ~Ball() {}
  void draw(sf::RenderWindow& window, GameStates state);
  void init(Player* ptp);
  void move(float delta_time, const Vaus& vaus, Brick bricks[][kLevelMaxColumns]);
  void reset();
  void setLevel(Level* ptl) { level_ = ptl; };
  void slowPowerUp();
  /* Power-ups stuff */
  void deactivatePowerUp();
  PowerUpTypes getPowerUp() { return pwrup_type_; };
  bool isPowerUpActive() { return pwrup_active_; };
  void setPowerUp(PowerUpTypes type);
  void updatePowerUps();

 private:
  bool checkBrickCollision(Brick bricks[][kLevelMaxColumns]);
  bool checkBorderCollision();
  bool checkVausCollision(const Vaus& vaus);
  void invertHorizontalDirection(float variation);
  void invertVerticalDirection(float variation);
  void randomizeBounceAngle(Collisions collision);
  void updateFlashFlag();
  static float sumAbs(float num1, float num2);
  bool ball_flash_flag_;
  float current_radius_;
  sf::Vector2f direction_;
  sf::Clock flash_clock_;
  sf::Vector2f last_position_;
  Level* level_;
  bool moving_flag_;
  Player* player_;
  sf::Clock start_clock_;
  sf::CircleShape shape_;
  float speed_;
  /* Power-ups stuff */
  void speedUp();
  bool pwrup_active_;
  PowerUpTypes pwrup_type_;
  sf::Clock slow_clk_;
  float slow_timer_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_