#ifndef KETE_ARKA_CLASSES_PLAYER_H_
#define KETE_ARKA_CLASSES_PLAYER_H_

#include "../config.h"

class Player {
 public:
  Player() {
    init();
  }
  ~Player() {}
  void descreaseLives(int decrease_by = 1);
  void increaseScore(int increase_by);
  bool isDead();
  int getLives();
  int getScore();

 private:
  void init();
  bool dead_;
  int lives_;
  int score_;
};

#endif  // KETE_ARKA_CLASSES_PLAYER_H_
