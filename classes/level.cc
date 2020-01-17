#include "level.h"

/////////////////////////////////////////////////
/// @brief Completes the level.
///
/// Completes the level. Mainly used for cheating.
/////////////////////////////////////////////////
void Level::complete() {
  completed_ = true;
}

/////////////////////////////////////////////////
/// @brief Decreases the resistance of a brick.
///
/// @param i j - The brick  to be decreased.
///
/// Decreases the resistance of a brick and sets inactive if needed.
/// Also updates the score  of the player accordingly.
/////////////////////////////////////////////////
void Level::decreaseResistance(int i, int j) {
  if (bricks_[i][j].type != A) {
    if (bricks_[i][j].resistance  - 1 <= 0) {
      bricks_[i][j].resistance = 0;
      bricks_[i][j].active = false;
      bricks_remaining_--;
      player_->increaseScore(bricks_[i][j].points);
      if (!bricks_remaining_)  {
        completed_ = true;
      }
    }  else {
      bricks_[i][j].resistance--;
    }
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
  window.draw(background_va_, &background_texture_);
  for (unsigned int i = 0; i < kLevelMaxRows; ++i) {
    for (unsigned int j = 0; j < kLevelMaxColumns; ++j) {
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
  initBackground();
  initBricks();
}

///
void Level::initBackground() {
  const std::string path = "assets/img/";
  switch (background_) {
    case Background::Moai:
      if (!background_texture_.loadFromFile(path + "bg_moai.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::RedCircuit:
      if (!background_texture_.loadFromFile(path + "bg_circuit_red.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::BlueCircuit:
      if (!background_texture_.loadFromFile(path + "bg_circuit_blue.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::Green:
      if (!background_texture_.loadFromFile(path + "bg_green.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::Blue:
      [[fallthrough]];
    default:
      if (!background_texture_.loadFromFile(path + "bg_blue.png")) {
        exit(EXIT_FAILURE);
      }
      break;
  }
  background_texture_.setRepeated(true);
  background_va_.resize(4);
  background_va_.setPrimitiveType(sf::Quads);
  background_va_[0] = sf::Vector2f(         0.f,           0.f);
  background_va_[1] = sf::Vector2f(kScreenWidth,           0.f);
  background_va_[2] = sf::Vector2f(kScreenWidth, kScreenHeight);
  background_va_[3] = sf::Vector2f(         0.f, kScreenHeight);
  background_va_[0].texCoords = sf::Vector2f(         0.f,           0.f);
  background_va_[1].texCoords = sf::Vector2f(kScreenWidth,           0.f);
  background_va_[2].texCoords = sf::Vector2f(kScreenWidth, kScreenHeight);
  background_va_[3].texCoords = sf::Vector2f(         0.f, kScreenHeight);
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
      bricks_[i][j].shape.setSize(kBrickDefaultSize);
      bricks_[i][j].shape.setOutlineThickness(-1);
      bricks_[i][j].shape.setOutlineColor(kBrickDefaultOutlineColor);
      switch(layout_[i * kLevelMaxColumns + j])  {
        case W:
          bricks_[i][j].type = W;
          bricks_[i][j].shape.setFillColor(kBrickWhite);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 50;
          bricks_remaining_++;
          break;
        case O:
          bricks_[i][j].type = O;
          bricks_[i][j].shape.setFillColor(kBrickOrange);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 60;
          bricks_remaining_++;
          break;
        case L:
          bricks_[i][j].type = L;
          bricks_[i][j].shape.setFillColor(kBrickLighBlue);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 70;
          bricks_remaining_++;
          break;
        case G:
          bricks_[i][j].type = G;
          bricks_[i][j].shape.setFillColor(kBrickGreen);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 80;
          bricks_remaining_++;
          break;
        case R:
          bricks_[i][j].type = R;
          bricks_[i][j].shape.setFillColor(kBrickRed);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 90;
          bricks_remaining_++;
          break;
        case B:
          bricks_[i][j].type = B;
          bricks_[i][j].shape.setFillColor(kBrickBlue);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 100;
          bricks_remaining_++;
          break;
        case P:
          bricks_[i][j].type = P;
          bricks_[i][j].shape.setFillColor(kBrickPink);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 110;
          bricks_remaining_++;
          break;
        case Y:
          bricks_[i][j].type = Y;
          bricks_[i][j].shape.setFillColor(kBrickYellow);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 1;
          bricks_[i][j].points = 120;
          bricks_remaining_++;
          break;
        case S:
          bricks_[i][j].type = S;
          bricks_[i][j].shape.setFillColor(kBrickSilver);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 2;
          bricks_[i][j].points = 50 * number_;
          bricks_remaining_++;
          break;
        case A:
          bricks_[i][j].type = A;
          bricks_[i][j].shape.setFillColor(kBrickGold);
          bricks_[i][j].active = true;
          bricks_[i][j].resistance = 0;
          bricks_[i][j].points = 0;
          break;
        case _:
        default:
          bricks_[i][j].type = _;
          bricks_[i][j].active = false;
          bricks_[i][j].resistance = 0;
          bricks_[i][j].points = 0;
          break;
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
  for (unsigned int i = 0; i < kMaxLevels; ++i) {
    ptl[i].name_ = kProtoLevels[i].name;
    ptl[i].background_ = kProtoLevels[i].background;
    for (unsigned int j = 0; j < kLevelMaxRows * kLevelMaxColumns; ++j) {
      ptl[i].layout_[j] = kProtoLevels[i].layout[j];
    }
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
/// @param lvl_num - An integer to be set as the level number.
///
/// Sets the level's number.
/////////////////////////////////////////////////
void Level::setNumber(int lvl_num) {
  number_ = lvl_num;
}
