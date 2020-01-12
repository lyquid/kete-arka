#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include <string> // std::string

#include "../config.h"
#include "../levels.h"
#include "player.h"

struct Brick {
  BrickTypes type = _;
  bool active;
  unsigned int resistance;
  unsigned int points;
  sf::RectangleShape shape;
};

class Level {
 public:
  Level() {}
  ~Level() {}
  void decreaseResistance(int i, int j);
  void draw(sf::RenderWindow &window);
  Brick (*getBricks())[kLevelMaxColumns];
  std::string getName();
  int getNumber();
  void init(Player *ptp);
  bool isCompleted();
  void setLayout(const BrickTypes *new_layout);
  void setName(std::string name);
  void setNumber(int lvl_num);
  static void initProtoLevels(Level *ptl); 

 private:
  void initBricks();
  Brick bricks_[kLevelMaxRows][kLevelMaxColumns];
  int bricks_remaining_;
  bool completed_;
  BrickTypes layout_[kLevelMaxRows * kLevelMaxColumns];
  std::string name_;
  int number_;
  Player *player_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_