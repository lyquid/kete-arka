#include "ship.h"

/////////////////////////////////////////////////
/// @brief Returns the ship's shape.
///
/// @return A RectangleShape based on the ship's shape.
///
/// Returns a RectangleShape representing the ship's shape.
/////////////////////////////////////////////////
sf::RectangleShape Ship::getShape() {
  return ship_shape_;
}

/////////////////////////////////////////////////
/// @brief Initializes ship's properties.
///
/// Sets the color to the default ship's color, the size 
/// to the default ship's size and the position to the 
/// default ship's position.
/////////////////////////////////////////////////
void Ship::init() {
  ship_shape_.setFillColor(kShipDefaultColor);
  ship_shape_.setSize(kShipDefaultSize);
  ship_shape_.setPosition(kShipDefaultPosition);
}

/////////////////////////////////////////////////
/// @brief Moves the ship in a valid way.
///
/// @param offset The vector to be added to the current position.
///
/// Checks if we want to move the ship right or left and 
/// keeps the ship within the screen boundaries.
/////////////////////////////////////////////////
void Ship::move(sf::Vector2f offset) {
  if ((offset.x < 0 && ship_shape_.getPosition().x > 0)                                     // wants to go left
   || (offset.x > 0 && ship_shape_.getPosition().x + kShipDefaultSize.x < kScreenWidth)) {  // wants to go right
    ship_shape_.move(offset);
  }
}
