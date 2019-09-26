#include "ship.h"

/////////////////////////////////////////////////
/// @brief Draws the ship to the specified RenderWindow.
///
/// @param window The RenderWindow to draw the ship on.
///
/// Draws the ship to the specified RenderWindow.
/////////////////////////////////////////////////
void Ship::draw(sf::RenderWindow& window) {
  window.draw(ship_shape_);
}

/////////////////////////////////////////////////
/// @brief Returns the ship's shape.
///
/// @return A RectangleShape representing the ship's shape.
///
/// Returns a RectangleShape representing the ship's 
/// current shape.
/////////////////////////////////////////////////
sf::RectangleShape Ship::getShipShape() {
  return ship_shape_;
}

/////////////////////////////////////////////////
/// @brief Returns the ship's size.
///
/// @return A Vector2f representing the ship's size.
///
/// Returns a Vector2f representing the ship's 
/// current size.
/////////////////////////////////////////////////
sf::Vector2f Ship::getShipSize() {
  return ship_shape_.getSize();
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
  resetPosition();
}

/////////////////////////////////////////////////
/// @brief Moves the ship in a valid way.
///
/// @param offset The vector to be added to the current position.
///
/// Checks if we want to move the ship right or left and 
/// keeps the ship within the screen boundaries.
/////////////////////////////////////////////////
void Ship::move(const sf::Vector2f offset) {
  if ((offset.x < 0 && ship_shape_.getPosition().x > 0)                                     // wants to go left
   || (offset.x > 0 && ship_shape_.getPosition().x + kShipDefaultSize.x < kScreenWidth)) {  // wants to go right
    ship_shape_.move(offset);
  }
}

/////////////////////////////////////////////////
/// @brief Resets ship's position.
///
/// Resets the ship's positions to it's original
/// default position.
/////////////////////////////////////////////////
void Ship::resetPosition() {
  ship_shape_.setPosition(kShipDefaultPosition);
}
