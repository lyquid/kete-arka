#include "brick.h"

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
/// @brief Returns the brick's shape.
///
/// @return A RectangleShape representing the brick's shape.
///
/// Returns a RectangleShape representing the brick's 
/// current shape.
/////////////////////////////////////////////////
sf::RectangleShape Brick::getBrickShape() {
  return shape_;
}

/////////////////////////////////////////////////
/// @brief Returns the brick's size.
///
/// @return A Vector2f representing the brick's size.
///
/// Returns a Vector2f representing the brick's 
/// current size.
/////////////////////////////////////////////////
sf::Vector2f Brick::getBrickSize() {
  return shape_.getSize();
}

/////////////////////////////////////////////////
/// @brief Initializes the brick's properties.
///
/// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
/////////////////////////////////////////////////
void Brick::init() {
  shape_.setFillColor(sf::Color::White);
  shape_.setSize(kBrickDefaultSize);
  shape_.setPosition(250.f, 100.f);
}
