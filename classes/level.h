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

enum class PowerUpTypes { 
  Break, Catch, Disruption, 
  Enlarge, Laser, Player, Slow,
  count
};

struct Brick {
  BrickTypes type;
  bool active;
  unsigned int resistance;
  unsigned int points;
  sf::RectangleShape shape;
  bool beveled;
  sf::VertexArray bevel;
};

struct PowerUp {
  bool active;
  sf::RectangleShape shape;
  PowerUpTypes type;
};

class Level {
 public:
  Level():
    completed_(false),
    bricks_remaining_(0u) {}
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
  void updatePowerUp(float delta_time);
 
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
  /* Power-ups stuff */
  bool checkPowerUpSpawn();
  void deactivatePowerUpFall();
  void generatePowerUpSequence(unsigned int surprise_bricks);
  void spawnPowerUp(const sf::Vector2f& where);
  static PowerUp power_up_;
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
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_