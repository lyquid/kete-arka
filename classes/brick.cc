#include "brick.h"

/////////////////////////////////////////////////
/// @brief Drecreases the resistance of the brick by the amount specified.
///
/// @param decrease_by The amount to be decreased by.
///
/// Decreases the resistance of the brick by the amount specified. 
/// If no amount is specified, decreases the resistance by 1. 
/// If resistance equals 0, sets the brick inactive.
/// Note that resistance cannot be decreased below 0.
/////////////////////////////////////////////////
void Brick::decreaseResistance(int decrease_by) {
  resistance_ = (resistance_ - decrease_by < 0) ? 0 : resistance_ - decrease_by;
  if (!resistance_) {
    setActive(false);
  }
}

/////////////////////////////////////////////////
/// @brief Draws the brick to the specified RenderWindow.
///
/// @param window The RenderWindow to draw the brick on.
///
/// Draws the brick to the specified RenderWindow.
/////////////////////////////////////////////////
void Brick::draw(sf::RenderWindow& window) {
  window.draw(shape_);
}

/////////////////////////////////////////////////
/// @brief Returns the brick's position.
///
/// @return A sf::Vector2f representing the brick's position.
///
/// Returns a sf::Vector2f representing the brick's current position.
/////////////////////////////////////////////////
sf::Vector2f Brick::getPosition() {
  return shape_.getPosition();
}

/////////////////////////////////////////////////
/// @brief Returns the brick's resistance.
///
/// @return An integer corresponding to the brick's resistance.
///
/// Returns an integer corresponding to the brick's current resistance.
/////////////////////////////////////////////////
int Brick::getResistance() {
  return resistance_;
}

/////////////////////////////////////////////////
/// @brief Returns the brick's shape.
///
/// @return A RectangleShape representing the brick's shape.
///
/// Returns a RectangleShape representing the brick's current shape.
/////////////////////////////////////////////////
sf::RectangleShape Brick::getShape() {
  return shape_;
}

/////////////////////////////////////////////////
/// @brief Returns the brick's size.
///
/// @return A Vector2f representing the brick's size.
///
/// Returns a Vector2f representing the brick's current size.
/////////////////////////////////////////////////
sf::Vector2f Brick::getSize() {
  return shape_.getSize();
}

/////////////////////////////////////////////////
/// @brief Initializes the brick's properties.
///
/// Sets the fill color, outline thickness, outline color and size to their 
/// default values. The resistance is set to 1 and activates the brick.
/////////////////////////////////////////////////
void Brick::init() {
  shape_.setFillColor(sf::Color::White);
  shape_.setOutlineThickness(-1);
  shape_.setOutlineColor(kBrickDefaultOutlineColor);
  shape_.setSize(kBrickDefaultSize);
  setResistance(1);
  setActive(true);
}

/////////////////////////////////////////////////
/// @brief Returns true if the brick is active.
///
/// @return A boolean representing the brick's active status.
///
/// Returns true if the brick is active. False otherwise.
/////////////////////////////////////////////////
bool Brick::isActive() {
  return active_;
}

/////////////////////////////////////////////////
/// @brief Sets the active status of the brick.
///
/// @param status A boolean to set the desired active status.
///
/// Sets the active flag of the brick to the desired status (true/false).
/////////////////////////////////////////////////
void Brick::setActive(bool status) {
  active_ = status;
}

/////////////////////////////////////////////////
/// @brief Sets the position of the brick.
///
/// @param position The position to be set.
///
/// Sets the position of the brick to the desired position.
/////////////////////////////////////////////////
void Brick::setPosition(sf::Vector2f position) {
  shape_.setPosition(position.x, position.y);
}

/////////////////////////////////////////////////
/// @brief Sets the resistance of the brick.
///
/// @param resistance The resistance to be set.
///
/// Sets the resistance of the brick. If < 0,
/// resistance is set to 0.
/// If resistance equals 0, sets the brick inactive.
/////////////////////////////////////////////////
void Brick::setResistance(int resistance) {
  resistance_ = (resistance < 0) ? 0 : resistance;
  if (!resistance_) {
    setActive(false);
  }
}
