#include "ship.h"

/////////////////////////////////////////////////
/// @brief Draws the ship to the specified RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the ship on.
///
/// Draws the ship to the specified RenderWindow.
/////////////////////////////////////////////////
void Ship::draw(sf::RenderWindow &window) {
  window.draw(shape_);
}

/////////////////////////////////////////////////
/// @brief Returns the ship's shape.
///
/// @return A sf::RectangleShape representing the ship's shape.
///
/// Returns a sf::RectangleShape representing the ship's 
/// current shape.
/////////////////////////////////////////////////
sf::RectangleShape Ship::getShape() {
  return shape_;
}

/////////////////////////////////////////////////
/// @brief Returns the ship's size.
///
/// @return A sf::Vector2f representing the ship's size.
///
/// Returns a sf::Vector2f representing the ship's 
/// current size.
/////////////////////////////////////////////////
sf::Vector2f Ship::getSize() {
  return shape_.getSize();
}

/////////////////////////////////////////////////
/// @brief Initializes ship's properties.
///
/// Sets the color to the default ship's color, the size 
/// to the default ship's size and the position to the 
/// default ship's position.
/////////////////////////////////////////////////
void Ship::init() {
  shape_.setFillColor(kShipDefaultColor);
  shape_.setSize(kShipDefaultSize);
  resetPosition();
}

/////////////////////////////////////////////////
/// @brief Moves the ship in a valid way.
///
/// @param offset - The sf::Vector2f to be added to the current position.
///
/// Checks if we want to move the ship right or left and 
/// keeps the ship within the screen boundaries.
/////////////////////////////////////////////////
void Ship::move(sf::Vector2f offset) {
  if (offset.x < 0 && shape_.getPosition().x + offset.x >= kGUIBorderThickness) {
    // wants to go left
      shape_.move(offset);
  } else if (offset.x > 0 && shape_.getPosition().x + kShipDefaultSize.x + offset.x <= kScreenWidth - kGUIBorderThickness) {
    // wants to go right
      shape_.move(offset);
  }
}

/////////////////////////////////////////////////
/// @brief Resets the ship's properties.
///
/// Sets the color to the default ship's color, the size 
/// to the default ship's size and the position to the 
/// default ship's position.
/// It just calls Ship::init().
/////////////////////////////////////////////////
void Ship::reset() {
  init();
}

/////////////////////////////////////////////////
/// @brief Resets ship's position.
///
/// Resets the ship's positions to it's original
/// default position.
/////////////////////////////////////////////////
void Ship::resetPosition() {
  shape_.setPosition(kShipDefaultPosition);
}
