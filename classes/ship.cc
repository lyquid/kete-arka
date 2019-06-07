#include "ship.h"

sf::RectangleShape Ship::getShape() {
  return ship_shape_;
}

void Ship::init() {
  ship_shape_.setFillColor(kShipDefaultColor);
  ship_shape_.setSize(kShipDefaultSize);
  ship_shape_.setOrigin(sf::Vector2f(kShipDefaultSize.x / 2.f, kShipDefaultSize.y / 2.f));
  ship_shape_.setPosition(kShipDefaultPosition);
}

bool Ship::moveLeft() {
  return false;
}

bool Ship::moveRight() {
  return false;
}
