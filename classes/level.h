#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include "../config.h"
#include "brick.h"

class Player; 

class Level {
 public:
  Level() {}
  ~Level() {}
  void draw(sf::RenderWindow &window);
  Brick (*getBricks())[kLevelMaxColumns];
  sf::String getLevelName();
  int getLevelNumber();
  void init(Player *ptp);
  void initBricks(Player *ptp);
  bool isCompleted();
  void setLevelName(sf::String name);
  void setLevelNumber(int lvl_num);

 private:
  Brick bricks_[kLevelMaxRows][kLevelMaxColumns];
  int bricks_remaining_;
  bool completed_;
  sf::String name_;
  int number_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_
