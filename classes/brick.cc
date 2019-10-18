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
/// @brief Initializes ship's properties.
///
/// Sets the color to the default ship's color, the size 
/// to the default ship's size and the position to the 
/// default ship's position.
/////////////////////////////////////////////////
void Brick::init() {
  shape_.setFillColor(sf::Color::White);
  shape_.setSize(kBrickDefaultSize);
  shape_.setPosition(50.f, 10.f);
}
