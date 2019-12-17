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
  Brick (*getBricks())[kBrickDefaultColumns];
  sf::String getLevelName();
  int getLevelNumber();
  void init(Player *ptp);
  void initBricks(Player *ptp);
  bool isCompleted();
  void setLevelName(const sf::String name);
  void setLevelNumber(const int num_lvl);

 private:
  Brick bricks_[kBrickDefaultRows][kBrickDefaultColumns];
  int bricks_remaining_;
  bool completed_;
  sf::String name_;
  int number_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_
