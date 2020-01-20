#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include <string> // std::string

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "../levels.h"
#include "player.h"

struct Brick {
  BrickTypes type;
  bool active;
  unsigned int resistance;
  unsigned int points;
  sf::RectangleShape shape;
};

const std::string kImagePath = "assets/img/";

class Level {
 public:
  Level() {}
  ~Level() {}
  void complete();
  void decreaseResistance(int i, int j);
  void draw(sf::RenderWindow &window);
  Brick (*getBricks())[kLevelMaxColumns];
  std::string getName();
  int getNumber();
  void init(Player *ptp);
  static void initBorderGraphics();
  static void initProtoLevels(Level *ptl);
  bool isCompleted();
  void setNumber(int lvl_num);
 
 private:
  void initBackground();
  void initBricks();
  Brick bricks_[kLevelMaxRows][kLevelMaxColumns];
  int bricks_remaining_;
  bool completed_;
  BrickTypes layout_[kLevelMaxRows * kLevelMaxColumns];
  std::string name_;
  int number_;
  Player *player_; 
  // level background and borders
  Background background_;
  sf::VertexArray background_va_;
  sf::Texture background_tx_;
  static sf::VertexArray border_left_;         
  static sf::Texture border_left_tx_;
  static sf::VertexArray border_right_;
  static sf::Texture border_right_tx_;
  static sf::VertexArray border_top_;
  static sf::Texture border_top_tx_; 
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_