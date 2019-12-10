#include "level.h"

/////////////////////////////////////////////////
/// @brief Draws the level to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the level on.
///
/// Draws the level to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void Level::draw(sf::RenderWindow &window) {
  for (int i = 0; i < kBrickDefaultRows; ++i) {
    for (int j = 0; j < kBrickDefaultColumns; ++j) {
      if (bricks_[i][j].isActive()) {
        bricks_[i][j].draw(window);
      }
    }
  }
}

/////////////////////////////////////////////////
/// @brief Returns the level's bricks.
///
/// @return - A multidimensional array with the bricks of the level.
///
/// A multidimensional array with the bricks of the level.
/////////////////////////////////////////////////
Brick (*Level::getBricks())[kBrickDefaultColumns] {
  return bricks_;
}

/////////////////////////////////////////////////
/// @brief Returns the level's number.
///
/// @return - An integer representing the level's number.
///
/// An integer representing the level's number.
/////////////////////////////////////////////////
int Level::getLevelNumber() {
  return lvl_number_;
}

/////////////////////////////////////////////////
/// @brief Initializates a level object.
///
/// @param ptp - A pointer to the player.
/// 
/// Sets the compelted flag to false, the bricks remaining 
/// to 0 and initializes each brick.
/////////////////////////////////////////////////
void Level::init(Player *ptp) {
  completed_ = false;
  bricks_remaining_ = 0;
  initBricks(ptp);
}

/////////////////////////////////////////////////
/// @brief Initializates the bricks of a level.
///
/// @param ptp - A pointer to the player.
///
/// TODO: This will require some work.
/////////////////////////////////////////////////
void Level::initBricks(Player *ptp) {
  int i, j;
  float start_y = kBrickDefaultStart;
  for (i = 0; i < kBrickDefaultRows; ++i) {
    for (j = 0; j < kBrickDefaultColumns; ++j) {
      bricks_[i][j].setActive(true);
      bricks_remaining_++;
      bricks_[i][j].setPosition(sf::Vector2f(bricks_[i][j].getSize().x * j, start_y));
      bricks_[i][j].setPlayer(ptp);
    }
    start_y = start_y + bricks_[i][j].getSize().y;
  } 
}

/////////////////////////////////////////////////
/// @brief Returns true if the level is completed.
///
/// @return - True if the level is completed.
///
/// True if the level is completed (no brick remains).
/////////////////////////////////////////////////
bool Level::isCompleted() {
  return completed_;
}

/////////////////////////////////////////////////
/// @brief Sets the level's number.
///
/// @param num_lvl - An integer to be set as the level number.
///
/// @return The integer supplied.
/// Sets the level's number.
/////////////////////////////////////////////////
int Level::setLevelNumber(const int num_lvl) {
  lvl_number_ = num_lvl;
  return lvl_number_;
}

/////////////////////////////////////////////////
/// @brief Set the level number for all levels.
///
/// @param ptl - A pointer to the array of levels.
///
/// TODO: a lot of things
/////////////////////////////////////////////////
void Level::setLevelsNumbers(Level *ptl) {
  for (int i = 0; i < kTotalLevels; ++i) {
    ptl[i].setLevelNumber(i + 1);
  } 
}
