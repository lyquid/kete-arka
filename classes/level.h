#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include <chrono>
#include <random>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "../levels.h"
#include "player.h"

enum class PowerUpTypes { 
  Bounce, Catch, Duplicate, 
  Enlarge, Laser, Pitufo, SpeedDown,
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
  Level() {}
  ~Level() {}
  void complete();
  void decreaseResistance(sf::Vector2u brick);
  void draw(sf::RenderWindow &window);
  Brick (*getBricks())[kLevelMaxColumns];
  std::string getName();
  int getNumber();
  void init(Player* ptp);
  static void initBorderGraphics();
  static void initProtoLevels(Level* ptl);
  bool isCompleted();
  void setNumber(int lvl_num);
  void updatePowerUp(float delta_time);
 
 private:
  void initBackground();
  void initBricks();
  void setBevel(sf::Vector2f position, sf::Vector2u brick);
  Brick bricks_[kLevelMaxRows][kLevelMaxColumns];
  int bricks_remaining_;
  bool completed_;
  BrickTypes layout_[kLevelMaxRows * kLevelMaxColumns];
  std::string name_;
  int number_;
  Player* player_;
  /* Level background and borders */
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
  /* Power-up stuff */
  bool checkPowerUpSpawn();
  void generatePowerUpSequence(unsigned int surprise_bricks);
  void spawnPowerUp(const sf::Vector2f &where);
  std::vector<unsigned int> pwrup_sequence_;
  std::vector<unsigned int>::const_iterator seq_it_;
  unsigned int bricks_to_pwup_;
  bool pwrup_on_screen_;
  PowerUp power_up_;
  static const sf::Vector2f kPowerUpSize_;
  static const float kPowerUpSpeed_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_