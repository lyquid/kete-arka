#ifndef KETE_ARKA_CLASSES_POWERUPS_H_
#define KETE_ARKA_CLASSES_POWERUPS_H_

#include <SFML/Graphics.hpp>

enum class PowerUpTypes {
  Nil, Break, Catch, Disruption, 
  Enlarge, Laser, Player, Slow,
  count
};

struct Laser {
  bool active;
  sf::RectangleShape shape;
};

struct PowerUp {
  bool active;
  sf::RectangleShape shape;
  PowerUpTypes type;
};

#endif // KETE_ARKA_CLASSES_POWERUPS_H_