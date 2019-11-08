#ifndef KETE_ARKA_CLASSES_BRICK_H_
#define KETE_ARKA_CLASSES_BRICK_H_

#include "../config.h"
#include "gui.h"
#include "player.h"

class Brick {
 public:
  Brick() {
    init();
  }
  ~Brick() {}
  void decreaseResistance(const int decrease_by = 1);
  void draw(sf::RenderWindow &window);
  sf::Vector2f getPosition();
  int getResistance();
  sf::RectangleShape getShape();
  sf::Vector2f getSize();
  bool isActive();
  void setActive(const bool status);
  void setGui(GUI *ptg);
  void setPlayer(Player *ptp); // can we make this with a reference instead?
  void setPosition(const sf::Vector2f position);
  void setResistance(const int resistance);

 private:
  void init();
  bool active_;
  GUI *gui_;
  Player *player_;
  int resistance_;
  sf::RectangleShape shape_;
};

#endif  // KETE_ARKA_CLASSES_BRICK_H_