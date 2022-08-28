#ifndef KETE_ARKA_CLASSES_BALL_H_
#define KETE_ARKA_CLASSES_BALL_H_

#include <chrono>
#include <cmath>    // std::abs
#include <iostream> // std::cout
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../config.h"
#include "level.h"
#include "logger.h"
#include "player.h"

class Ball {
 public:
  Ball() {}
  ~Ball() {}
  void draw(sf::RenderWindow& window, k::GameStates state);
  void init(Player* ptp);
  void move(float delta_time, const k::Vaus& vaus, const k::Brick bricks[][k::kLevelMaxColumns]);
  void reset();
  void setLevel(Level* ptl) { level_ = ptl; }
  /* Power-ups stuff */
  void deactivatePowerUp();
  k::PowerUpTypes getPowerUp() const { return pwrup_type_; }
  bool isPowerUpActive() const { return pwrup_active_; }
  void setPowerUp(const k::PowerUpTypes& type);
  void updatePowerUps();
  /* Catch power-up */
  void followVaus(const k::Vaus& vaus);
  bool isCatched() const { return catched_; }
  void release() { catched_ = false; }
  
 private:
  /* Ball default settings */
  static constexpr float kBallDefaultRadius_       = 5.f;
  static constexpr float kBallDefaultSpeed_        = 400.f;
  static constexpr float kBallDefaultDisplacement_ = 1.41f;
  static const sf::Vector2f kBallDefaultPosition_;
  static const sf::Color kBallDefaultColor_;
  enum class Collisions {
    Top, Bottom, Left, Right,
    TopShip, BottomShip, LeftShip, RightShip,
    TopBrick, BottomBrick, LeftBrick, RightBrick
  };
  struct BallShape {
    bool            active;
    sf::Vector2f    direction;
    sf::Vector2f    last_position;
    sf::CircleShape shape;
  };
  bool checkBrickCollision(BallShape& ball, const k::Brick bricks[][k::kLevelMaxColumns]);
  bool checkBorderCollision(BallShape& ball);
  bool checkVausCollision(BallShape& ball, const k::Vaus& vaus);
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
  k::PowerUpTypes pwrup_type_;
  /* Slow power-up */
  void slowPowerUp();
  void speedUp();
  sf::Clock slow_clk_;
  float slow_timer_;
  /* Disruption power-up */
  void activateDisruption();
  static constexpr unsigned int kDisruptionMaxBalls_ = 3u;
  static unsigned int active_balls_;
  /* Catch power-up */
  float generateRandomTime(float min, float max);
  static constexpr float kCatchMaxTime_ = 3.00f;
  static constexpr float kCatchMinTime_ = 1.50f;
  static sf::Clock catch_clk_;
  static float time_to_release_;
  static bool catched_;
  static float offset_;
};

#endif  // KETE_ARKA_CLASSES_BALL_H_
