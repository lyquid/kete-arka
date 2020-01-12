#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include <string> // std::string

#include "../config.h"
#include "../levels.h"
#include "brick.h"

class Player; 

class Level {
 public:
  Level() {}
  ~Level() {}
  void draw(sf::RenderWindow &window);
  Brick (*getBricks())[kLevelMaxColumns];
  std::string getName();
  int getNumber();
  void init(Player *ptp);
  bool isCompleted();
  void setLayout(const int *new_layout);
  void setName(std::string name);
  void setNumber(int lvl_num);
  static void initProtoLevels(Level *ptl); 

 private:
  void initBricks(Player *ptp);
  Brick bricks_[kLevelMaxRows][kLevelMaxColumns];
  int bricks_remaining_;
  // bool completed_;
  int layout_[kLevelMaxRows * kLevelMaxColumns];
  std::string name_;
  int number_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_