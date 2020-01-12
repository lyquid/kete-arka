#include "level.h"

/////////////////////////////////////////////////
/// @brief Decreases the resistance of a brick.
///
/// @param i j - The brick  to be decreased.
///
/// Decreases the resistance of a brick and sets inactive if needed.
/// Also updates the score  of the player accordingly.
/////////////////////////////////////////////////
void Level::decreaseResistance(int i, int j) {
  if (bricks_[i][j].resistance  - 1 <= 0) {
    bricks_[i][j].resistance = 0;
    bricks_[i][j].active = false;
    bricks_remaining_--;
    player_->increaseScore(50);
    if (!bricks_remaining_)  {
      completed_ = true;
    }
  }  else {
    bricks_[i][j].resistance--;
  }
}

/////////////////////////////////////////////////
/// @brief Draws the level to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the level on.
///
/// Draws the level to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void Level::draw(sf::RenderWindow &window) {
  for (int i = 0; i < kLevelMaxRows; ++i) {
    for (int j = 0; j < kLevelMaxColumns; ++j) {
      if (bricks_[i][j].active) {
        window.draw(bricks_[i][j].shape);
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
Brick (*Level::getBricks())[kLevelMaxColumns] {
  return bricks_;
}

/////////////////////////////////////////////////
/// @brief Returns the level's name.
///
/// @return - A std::string representing the level's name.
///
/// A sf::String representing the level's name.
/////////////////////////////////////////////////
std::string Level::getName() {
  return name_;
}

/////////////////////////////////////////////////
/// @brief Returns the level's number.
///
/// @return - An integer representing the level's number.
///
/// An integer representing the level's number.
/////////////////////////////////////////////////
int Level::getNumber() {
  return number_;
}

/////////////////////////////////////////////////
/// @brief Initializates a level object.
///
/// @param ptp - A pointer to the player.
///
/// Sets the completed flag to false, the bricks remaining
/// to 0 and initializes each brick.
/////////////////////////////////////////////////
void Level::init(Player *ptp) {
  player_ = ptp;
  completed_ = false;
  bricks_remaining_ = 0;
  initBricks();
}

/////////////////////////////////////////////////
/// @brief Initializates the bricks of a level.
///
/// Initializates the bricks of a level by reading a 
/// layout and positions them.
/////////////////////////////////////////////////
void Level::initBricks() {
  int i, j;
  float start_y = kBrickDefaultStart;
  for (i = 0; i < kLevelMaxRows; ++i) {
    for (j = 0; j < kLevelMaxColumns; ++j) {
      bricks_[i][j].shape.setFillColor(kBrickDefaultColor);
      bricks_[i][j].shape.setOutlineThickness(-1);
      bricks_[i][j].shape.setOutlineColor(kBrickDefaultOutlineColor);
      bricks_[i][j].shape.setSize(kBrickDefaultSize);
      bricks_[i][j].resistance = 1;
      if (layout_[i * kLevelMaxColumns + j] == 1) {
        bricks_[i][j].active = true;
        bricks_remaining_++;
      } else {
        bricks_[i][j].active = false;
      } 
      bricks_[i][j].shape.setPosition(sf::Vector2f(bricks_[i][j].shape.getSize().x * j, start_y));
    }
    start_y = start_y + bricks_[i][j - 1].shape.getSize().y;
  }
}

/////////////////////////////////////////////////
/// @brief Initializates the layouts and names of the levels.
///
/// @param ptl - A pointer to the array of levels.
///
/// Initializates the layouts and names of the levels.
/////////////////////////////////////////////////
void Level::initProtoLevels(Level *ptl) {
  for (int i = 0; i < kMaxLevels; ++i) {
    ptl[i].setName(kProtoLevels[i].name);
    ptl[i].setLayout(kProtoLevels[i].layout);
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
/// @brief Sets the layout of a level.
///
/// @param new_layout - A pointer to the array representing the layout.
///
/// Sets the layout of a level.
/////////////////////////////////////////////////
void Level::setLayout(const int *new_layout) {
  for (int i = 0; i < kLevelMaxRows * kLevelMaxColumns; ++i) {
    layout_[i] = new_layout[i];
  }
}

/////////////////////////////////////////////////
/// @brief Sets the level's name.
///
/// @param name - An std::string to be set as the level name.
///
/// Sets the level's name.
/////////////////////////////////////////////////
void Level::setName(std::string name) {
  name_ = name;
}

/////////////////////////////////////////////////
/// @brief Sets the level's number.
///
/// @param lvl_num - An integer to be set as the level number.
///
/// Sets the level's number.
/////////////////////////////////////////////////
void Level::setNumber(int lvl_num) {
  number_ = lvl_num;
}
