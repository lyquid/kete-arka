#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include <chrono>
#include <iostream> // std::cout /// to be removed
#include <random>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "../levels.h"
#include "player.h"
#include "powerups.h"

struct Brick {
  BrickTypes type;
  bool active;
  unsigned int resistance;
  unsigned int points;
  sf::RectangleShape shape;
  bool beveled;
  sf::VertexArray bevel;
};

class Level {
 public:
  Level():
    completed_(false),
    bricks_remaining_(0u),
    break_active_(false),
    pwrup_active_(false),
    pwrup_type_(PowerUpTypes::Nil) {}
  ~Level() {}
  /* Setters & getters */
  void complete() { completed_ = true; };
  void setNumber(unsigned int lvl_num) { number_ = lvl_num; };
  Brick (*getBricks())[kLevelMaxColumns] { return bricks_; };
  std::string getName() { return name_; };
  unsigned int getNumber() { return number_; };
  bool isCompleted() { return completed_; };
  /* Initializers */
  void init(Player* ptp);
  static void initGraphics();
  static void initProtoLevels(Level* ptl);
  /* Ohters */
  void decreaseResistance(sf::Vector2u pos);
  void draw(sf::RenderWindow& window);
  void updatePowerUpFall(float delta_time);
  /* Power-up generation stuff */
  bool catchedPowerUp() { return new_pwrup_; };
  PowerUpTypes getCatchedPowerUp() { return catched_pwrup_; };
  void eraseCatchedPowerUp();
  /* Power-up effects */
  void deactivatePowerUp();
  PowerUpTypes getPowerUp() { return pwrup_type_; };
  bool isBreakActive() { return break_active_; };
  bool isPowerUpActive() { return pwrup_active_; };
  void setPowerUp(PowerUpTypes type);
  void updateBreakAnim();
 
 private:
  /* Basic */
  bool completed_;
  std::string name_;
  unsigned int number_;
  Player* player_;
  /* Bricks */
  void initBricks();
  void setBevel(sf::Vector2f position, sf::Vector2u brick);
  Brick bricks_[kLevelMaxRows][kLevelMaxColumns];
  unsigned int bricks_remaining_;
  BrickTypes layout_[kLevelMaxRows * kLevelMaxColumns];
  /* Background and borders */
  void initBackground();
  Background background_;
  sf::VertexArray background_va_;
  sf::Texture background_tx_;
  static sf::VertexArray border_left_;
  static sf::Texture border_left_tx_;
  static sf::VertexArray border_right_;
  static sf::Texture border_right_tx_;
  static sf::VertexArray border_top_;
  static sf::Texture border_top_tx_;
  static const std::string kImagePath_;
  /* Power-up generation stuff */
  bool checkPowerUpSpawn();
  void deactivatePowerUpFall();
  void generatePowerUpSequence(unsigned int surprise_bricks);
  void spawnPowerUp(const sf::Vector2f& where);
  static PowerUp power_up_;
  static PowerUpTypes catched_pwrup_;
  static bool new_pwrup_;
  static const sf::Vector2f kPowerUpSize_;
  static const float kPowerUpSpeed_;
  static const float kPowerUpAnimSpeed_;
  static const unsigned int kPowerUpFrames_;
  static std::vector<sf::Texture> break_tx_;
  static std::vector<sf::Texture> catch_tx_;
  static std::vector<sf::Texture> disruption_tx_;
  static std::vector<sf::Texture> enlarge_tx_;
  static std::vector<sf::Texture> laser_tx_;
  static std::vector<sf::Texture> player_tx_;
  static std::vector<sf::Texture> slow_tx_;
  static std::vector<sf::Texture>::iterator pwrup_tx_it_;
  static std::vector<sf::Texture>* ptx_;
  static sf::Clock pwrup_anim_clk_;
  static unsigned int pwrup_anim_frame_;
  std::vector<unsigned int> pwrup_sequence_;
  std::vector<unsigned int>::const_iterator seq_it_;
  unsigned int bricks_to_pwrup_;
  /* Power-up effects */
  void loadBreakTx();
  bool break_active_;
  bool pwrup_active_; /* This is useless until we have more level controlled pwrups */
  PowerUpTypes pwrup_type_;
  static const sf::Vector2f kBreakSize_;
  static const sf::Vector2f kBreakPosition_;
  static const unsigned int kBreakAnimFrames_;
  static const float kBreakAnimSpeed_;
  static sf::RectangleShape break_shape_;
  static std::vector<sf::Texture> break_effect_tx_;
  static sf::Clock break_anim_clk_;
  static unsigned int break_anim_frame_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_