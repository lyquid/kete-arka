#ifndef KETE_ARKA_CLASSES_SHIP_H_
#define KETE_ARKA_CLASSES_SHIP_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

class Ship {
 public:
  Ship() {}
  ~Ship() {}

 private:
  bool moveLeft();
  bool moveRight();
  float speed_;
};

#endif  // KETE_ARKA_CLASSES_SHIP_H_
