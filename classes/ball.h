#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <SFML/Graphics.hpp>

#include <chrono>
#include <cmath>    // std::abs
#include <iostream> // std::cout
#include <random>
#include <vector>

#include "../config.h"
#include "level.h"
#include "logger.h"
#include "player.h"
#include "powerups.h"

struct BallShape {
  bool            active;
  sf::Vector2f    direction;
  sf::Vector2f    last_position;
  sf::CircleShape shape;
};

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
  /* Power-ups stuff */
  void deactivatePowerUp();
  PowerUpTypes getPowerUp() { return pwrup_type_; };
  bool isPowerUpActive() { return pwrup_active_; };
  void setPowerUp(PowerUpTypes type);
  void updatePowerUps();
  /* Catch power-up */
  void followVaus(const Vaus& vaus);
  bool isCatched() { return catched_; };
  void release() { catched_ = false; };

 private:
  bool checkBrickCollision(BallShape& ball, Brick bricks[][kLevelMaxColumns]);
  bool checkBorderCollision(BallShape& ball);
  bool checkVausCollision(BallShape& ball, const Vaus& vaus);
  void invertHorizontalDirection(BallShape& ball, float variation);
  void invertVerticalDirection(BallShape& ball, float variation);
  void randomizeBounceAngle(BallShape& ball, Collisions collision);
  void updateFlashFlag();
  static float sumAbs(float num1, float num2);
  static std::vector<BallShape> balls_;
  bool ball_flash_flag_;
  sf::Clock flash_clock_;
  Level* level_;
  bool moving_flag_;
  Player* player_;
  sf::Clock start_clock_;
  float speed_;
  /* Power-ups stuff */
  bool pwrup_active_;
  PowerUpTypes pwrup_type_;
  /* Slow power-up */
  void slowPowerUp();
  void speedUp();
  sf::Clock slow_clk_;
  float slow_timer_;
  /* Disruption power-up */
  void activateDisruption();
  static const unsigned int kDisruptionMaxBalls_;
  static unsigned int active_balls_;
  /* Catch power-up */
  float generateRandomTime(float min, float max);
  static const float kCatchMaxTime_;
  static const float kCatchMinTime_;
  static sf::Clock catch_clk_;
  static float time_to_release_;
  static bool catched_;
  static float offset_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_