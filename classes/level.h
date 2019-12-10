#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include "../config.h"
#include "brick.h"
#include "player.h"

class Level {
 public:
  Level() {}
  ~Level() {}
  void draw(sf::RenderWindow &window);
  Brick (*getBricks())[kBrickDefaultColumns];
  int getLevelNumber();
  void init(Player *ptp);
  void initBricks(Player *ptp);
  bool isCompleted();
  int setLevelNumber(const int num_lvl);
  static void setLevelsNumbers(Level *ptl);

 private:
  Brick bricks_[kBrickDefaultRows][kBrickDefaultColumns];
  int bricks_remaining_;
  bool completed_;
  int lvl_number_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_
