#ifndef KETE_ARKA_CLASSES_PLAYER_H_
#define KETE_ARKA_CLASSES_PLAYER_H_

#include "../config.h"
#include "gui.h"

class Player {
 public:
  Player() {}
  ~Player() {}
  void decreaseLives(int decrease_by = 1);
  int getLives();
  int getScore();
  void increaseScore(int increase_by);
  void init(GUI *ptg);
  bool isDead();
  void reset();

 private:
  bool dead_;
  GUI *gui_;
  int lives_;
  unsigned long long int score_;
};

#endif  // KETE_ARKA_CLASSES_PLAYER_H_
