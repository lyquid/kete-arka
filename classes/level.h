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
  bool isCompleted();
  static void initProtoLevels(Level *ptl);
  void setNumber(int lvl_num);

 private:
  void initBricks();
  Brick bricks_[kLevelMaxRows][kLevelMaxColumns];
  int bricks_remaining_;
  bool completed_;
  BrickTypes layout_[kLevelMaxRows * kLevelMaxColumns];
  std::string name_;
  int number_;
  Player *player_; 
  // level background and borders
  void initGraphics();
  Background background_;
  sf::VertexArray background_va_;
  sf::Texture background_tx_;
  sf::VertexArray border_left_;         
  sf::Texture border_left_tx_;
  sf::VertexArray border_right_;
  sf::Texture border_right_tx_;
  sf::VertexArray border_top_;
  sf::Texture border_top_tx_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_