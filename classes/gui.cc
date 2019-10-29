#include "gui.h"

/////////////////////////////////////////////////
/// @brief Draws the gui to the specified RenderWindow.
///
/// @param window The RenderWindow to draw the gui on.
///
/// Draws the gui to the specified RenderWindow.
/////////////////////////////////////////////////
void GUI::draw(sf::RenderWindow &window) {
  // score
  // lives
  window.draw(left_);
  window.draw(middle_);
  window.draw(right_);
}

/////////////////////////////////////////////////
/// @brief Initializes the GUI.
///
/// Sets everything that needs to be set.
/////////////////////////////////////////////////
void GUI::init() {
  left_.setSize(kGUIDefaultSize);
  left_.setPosition(0.f, 0.f);
  left_.setOutlineThickness(kGUIDefaultOutlineThickness);
  left_.setFillColor(kGUIDefaultFillColor); 
  left_.setOutlineColor(kGUIDefaultOutlineColor);
  middle_.setSize(sf::Vector2f(kGUIDefaultSize.x + 2.f, kGUIDefaultSize.y));
  middle_.setPosition(kGUIDefaultSize.x - 1.f, 0.f);
  middle_.setOutlineThickness(kGUIDefaultOutlineThickness);
  middle_.setFillColor(kGUIDefaultFillColor); 
  middle_.setOutlineColor(kGUIDefaultOutlineColor);
  right_.setSize(kGUIDefaultSize);
  right_.setPosition(kGUIDefaultSize.x * 2.f, 0.f);
  right_.setOutlineThickness(kGUIDefaultOutlineThickness);
  right_.setFillColor(kGUIDefaultFillColor); 
  right_.setOutlineColor(kGUIDefaultOutlineColor);
}
