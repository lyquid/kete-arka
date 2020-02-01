#include "level.h"

/* Image path */
const std::string Level::kImagePath_ = "assets/img/";
/* Borders VertexArrays and Textures */
sf::VertexArray Level::border_left_;         
sf::Texture Level::border_left_tx_;
sf::VertexArray Level::border_right_;
sf::Texture Level::border_right_tx_;
sf::VertexArray Level::border_top_;
sf::Texture Level::border_top_tx_;
/* Power up constants */
const sf::Vector2f Level::kPowerUpSize_ = sf::Vector2f(30.f, 15.f);
const float Level::kPowerUpSpeed_ = 200.f;

///
bool Level::checkPowerUpSpawn() {
  if (!pwrup_on_screen_) {
    --bricks_to_pwup_;
    if (!bricks_to_pwup_) {
      return true;
    }
  }
  return false;
}

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
/// @param brick - The brick  to be decreased.
///
/// Decreases the resistance of a brick and sets inactive if needed.
/// Also updates the score  of the player accordingly.
/////////////////////////////////////////////////
void Level::decreaseResistance(sf::Vector2u brick) {
  if (bricks_[brick.x][brick.y].type != A) {
    if (bricks_[brick.x][brick.y].resistance - 1 <= 0) {
      bricks_[brick.x][brick.y].resistance = 0u;
      bricks_[brick.x][brick.y].active = false;
      --bricks_remaining_;
      player_->increaseScore(bricks_[brick.x][brick.y].points);
      if (!bricks_remaining_)  {
        completed_ = true;
        return;
      }
      if (bricks_[brick.x][brick.y].type != S && checkPowerUpSpawn()) {
        spawnPowerUp(bricks_[brick.x][brick.y].shape.getPosition());
      }
    } else {
      --bricks_[brick.x][brick.y].resistance;
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
  window.draw(background_va_, &background_tx_);
  window.draw(border_left_, &border_left_tx_);
  window.draw(border_right_, &border_right_tx_);
  window.draw(border_top_, &border_top_tx_);
  for (unsigned int i = 0; i < kLevelMaxRows; ++i) {
    for (unsigned int j = 0; j < kLevelMaxColumns; ++j) {
      if (bricks_[i][j].active) {
        window.draw(bricks_[i][j].shape);
        if (bricks_[i][j].beveled) {
          window.draw(bricks_[i][j].bevel);
        }
      }
    }
  }
  if (power_up_.active) {
    window.draw(power_up_.shape);
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
/// A std::string representing the level's name.
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
void Level::init(Player* ptp) {
  player_ = ptp;
  completed_ = false;
  bricks_remaining_ = 0;
  pwrup_on_screen_ = false;
  power_up_.active = false;
  power_up_.shape.setSize(kPowerUpSize_);
  initBackground();
  initBricks();
}

///
void Level::initBackground() {
  switch (background_) {
    case Background::Moai:
      if (!background_tx_.loadFromFile(kImagePath_ + "bg_moai.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::RedCircuit:
      if (!background_tx_.loadFromFile(kImagePath_ + "bg_circuit_red.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::BlueCircuit:
      if (!background_tx_.loadFromFile(kImagePath_ + "bg_circuit_blue.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::Green:
      if (!background_tx_.loadFromFile(kImagePath_ + "bg_green.png")) {
        exit(EXIT_FAILURE);
      }
      break;
    case Background::Blue:
      [[fallthrough]];
    default:
      if (!background_tx_.loadFromFile(kImagePath_ + "bg_blue.png")) {
        exit(EXIT_FAILURE);
      }
      break;
  }
  background_tx_.setRepeated(true);
  background_va_.resize(4);
  background_va_.setPrimitiveType(sf::Quads);
  background_va_[0] = sf::Vector2f(               kGUIBorderThickness, kGUIBorderThickness);
  background_va_[1] = sf::Vector2f(kScreenWidth - kGUIBorderThickness, kGUIBorderThickness);
  background_va_[2] = sf::Vector2f(kScreenWidth - kGUIBorderThickness,       kScreenHeight);
  background_va_[3] = sf::Vector2f(               kGUIBorderThickness,       kScreenHeight);

  background_va_[0].texCoords = sf::Vector2f(                                     0.f,                                 0.f);
  background_va_[1].texCoords = sf::Vector2f(kScreenWidth - (kGUIBorderThickness * 2),                                 0.f);
  background_va_[2].texCoords = sf::Vector2f(kScreenWidth - (kGUIBorderThickness * 2), kScreenHeight - kGUIBorderThickness);
  background_va_[3].texCoords = sf::Vector2f(                                     0.f, kScreenHeight - kGUIBorderThickness);
}

///
void Level::initBorderGraphics() {
  /* left border */
  if (!border_left_tx_.loadFromFile(kImagePath_ + "border_left.png")) {
    exit(EXIT_FAILURE);
  }
  border_left_.resize(4);
  border_left_.setPrimitiveType(sf::Quads);
  border_left_[0] = sf::Vector2f(                0.f,           0.f);
  border_left_[1] = sf::Vector2f(kGUIBorderThickness,           0.f);
  border_left_[2] = sf::Vector2f(kGUIBorderThickness, kScreenHeight);
  border_left_[3] = sf::Vector2f(                0.f, kScreenHeight);
  border_left_[0].texCoords = sf::Vector2f(                0.f,           0.f);
  border_left_[1].texCoords = sf::Vector2f(kGUIBorderThickness,           0.f);
  border_left_[2].texCoords = sf::Vector2f(kGUIBorderThickness, kScreenHeight);
  border_left_[3].texCoords = sf::Vector2f(                0.f, kScreenHeight);
  /* right border */
  if (!border_right_tx_.loadFromFile(kImagePath_ + "border_right.png")) {
    exit(EXIT_FAILURE);
  }
  border_right_.resize(4);
  border_right_.setPrimitiveType(sf::Quads);
  border_right_[0] = sf::Vector2f(kScreenWidth - kGUIBorderThickness,           0.f);
  border_right_[1] = sf::Vector2f(                      kScreenWidth,           0.f);
  border_right_[2] = sf::Vector2f(                      kScreenWidth, kScreenHeight);
  border_right_[3] = sf::Vector2f(kScreenWidth - kGUIBorderThickness, kScreenHeight);
  border_right_[0].texCoords = sf::Vector2f(                0.f,           0.f);
  border_right_[1].texCoords = sf::Vector2f(kGUIBorderThickness,           0.f);
  border_right_[2].texCoords = sf::Vector2f(kGUIBorderThickness, kScreenHeight);
  border_right_[3].texCoords = sf::Vector2f(                0.f, kScreenHeight);
  /* top border */
  if (!border_top_tx_.loadFromFile(kImagePath_ + "border_top.png")) {
    exit(EXIT_FAILURE);
  }
  border_top_.resize(4);
  border_top_.setPrimitiveType(sf::Quads);
  border_top_[0] = sf::Vector2f(         0.f,                 0.f);
  border_top_[1] = sf::Vector2f(kScreenWidth,                 0.f);
  border_top_[2] = sf::Vector2f(kScreenWidth, kGUIBorderThickness);
  border_top_[3] = sf::Vector2f(         0.f, kGUIBorderThickness);
  border_top_[0].texCoords = sf::Vector2f(         0.f,                 0.f);
  border_top_[1].texCoords = sf::Vector2f(kScreenWidth,                 0.f);
  border_top_[2].texCoords = sf::Vector2f(kScreenWidth, kGUIBorderThickness);
  border_top_[3].texCoords = sf::Vector2f(         0.f, kGUIBorderThickness);
}

/////////////////////////////////////////////////
/// @brief Initializates the bricks of a level.
///
/// Initializates the bricks of a level by reading a 
/// layout and positions them.
/////////////////////////////////////////////////
void Level::initBricks() {
  unsigned int i, j, surprise_bricks = 0u;
  sf::Vector2f position;
  float start_y = kBrickDefaultStart + kGUIBorderThickness;
  for (i = 0u; i < kLevelMaxRows; ++i) {
    for (j = 0u; j < kLevelMaxColumns; ++j) {
      bricks_[i][j].shape.setSize(kBrickDefaultSize);
      bricks_[i][j].shape.setOutlineThickness(kBrickDefaultOutline);
      bricks_[i][j].shape.setOutlineColor(kBrickDefaultOutlineColor);
      position = sf::Vector2f(bricks_[i][j].shape.getSize().x * j + kGUIBorderThickness, start_y);
      bricks_[i][j].shape.setPosition(position);
      bricks_[i][j].active = true;
      bricks_[i][j].beveled = false;
      switch(layout_[i * kLevelMaxColumns + j])  {
        case W:
          bricks_[i][j].type = W;
          bricks_[i][j].shape.setFillColor(kBrickWhite);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 50u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case O:
          bricks_[i][j].type = O;
          bricks_[i][j].shape.setFillColor(kBrickOrange);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 60u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case L:
          bricks_[i][j].type = L;
          bricks_[i][j].shape.setFillColor(kBrickLighBlue);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 70u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case G:
          bricks_[i][j].type = G;
          bricks_[i][j].shape.setFillColor(kBrickGreen);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 80u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case R:
          bricks_[i][j].type = R;
          bricks_[i][j].shape.setFillColor(kBrickRed);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 90u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case B:
          bricks_[i][j].type = B;
          bricks_[i][j].shape.setFillColor(kBrickBlue);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 100u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case P:
          bricks_[i][j].type = P;
          bricks_[i][j].shape.setFillColor(kBrickPink);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 110u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case Y:
          bricks_[i][j].type = Y;
          bricks_[i][j].shape.setFillColor(kBrickYellow);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 120u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case S:
          bricks_[i][j].type = S;
          bricks_[i][j].shape.setFillColor(kBrickSilver);
          bricks_[i][j].resistance = 2u;
          bricks_[i][j].points = 50u * number_;
          ++bricks_remaining_;
          bricks_[i][j].beveled = true;
          setBevel(position, {i, j});
          break;
        case A:
          bricks_[i][j].type = A;
          bricks_[i][j].shape.setFillColor(kBrickGold);
          bricks_[i][j].resistance = 0u;
          bricks_[i][j].points = 0u;
          bricks_[i][j].beveled = true;
          setBevel(position, {i, j});
          break;
        case _:
        default:
          bricks_[i][j].type = _;
          bricks_[i][j].active = false;
          bricks_[i][j].resistance = 0u;
          bricks_[i][j].points = 0u;
          break;
      }
    }
    start_y = start_y + bricks_[i][j - 1u].shape.getSize().y;
  }
  generatePowerUpSequence(surprise_bricks);
}

/////////////////////////////////////////////////
/// @brief Initializates the layouts and names of the levels.
///
/// @param ptl - A pointer to the array of levels.
///
/// Initializates the layouts and names of the levels.
/////////////////////////////////////////////////
void Level::initProtoLevels(Level* ptl) {
  for (unsigned int i = 0u; i < kMaxLevels; ++i) {
    ptl[i].name_ = kProtoLevels[i].name;
    ptl[i].background_ = kProtoLevels[i].background;
    for (unsigned int j = 0u; j < kLevelMaxRows * kLevelMaxColumns; ++j) {
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

///
void Level::generatePowerUpSequence(unsigned int surprise_bricks) {
  if (!surprise_bricks || surprise_bricks <= 0u) {
    // seq_it_ = nullptr;
    // bricks_to_pwup_ =  
    /* we should do something with this */
    return;
  }
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);
  std::uniform_int_distribution<unsigned int> distribution(1u, surprise_bricks / 7u);
  pwrup_sequence_.clear();
  pwrup_sequence_.resize(surprise_bricks);
  printf("surprise_bricks = %d\n", surprise_bricks);
  for (auto& x : pwrup_sequence_) {
    x = distribution(generator);
    printf("bricks to pwup = %d\n", x);
  }
  seq_it_ = pwrup_sequence_.cbegin();
  bricks_to_pwup_ = *seq_it_;
}

///
void Level::setBevel(sf::Vector2f position, sf::Vector2u brick) {
  sf::VertexArray new_bevel(sf::TriangleStrip, 6);
  new_bevel[0].color = sf::Color::Black;
  new_bevel[1].color = sf::Color::Black;
  new_bevel[2].color = sf::Color::Black;
  new_bevel[3].color = sf::Color::Black;
  new_bevel[4].color = sf::Color::Black;
  new_bevel[5].color = sf::Color::Black;
  new_bevel[0].position = sf::Vector2f(position.x + kBrickDefaultBevel, position.y + kBrickDefaultSize.y);
  new_bevel[1].position = sf::Vector2f(position.x + kBrickDefaultBevel, position.y + kBrickDefaultSize.y - kBrickDefaultBevel);
  new_bevel[2].position = sf::Vector2f(position.x + kBrickDefaultSize.x, position.y + kBrickDefaultSize.y);
  new_bevel[3].position = sf::Vector2f(position.x + kBrickDefaultSize.x - kBrickDefaultBevel, position.y + kBrickDefaultSize.y - kBrickDefaultBevel);
  new_bevel[4].position = sf::Vector2f(position.x + kBrickDefaultSize.x, position.y + kBrickDefaultBevel);
  new_bevel[5].position = sf::Vector2f(position.x + kBrickDefaultSize.x - kBrickDefaultBevel, position.y + kBrickDefaultBevel);
  bricks_[brick.x][brick.y].bevel = new_bevel; 
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

///
void Level::spawnPowerUp(const sf::Vector2f &where) {
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<unsigned int> distribution(0u , static_cast<unsigned int>(PowerUpTypes::count) - 1u);
  auto type = static_cast<PowerUpTypes>(distribution(generator));
  switch (type) {
    case PowerUpTypes::Bounce:
      power_up_.shape.setFillColor(sf::Color::Magenta);
      break;
    case PowerUpTypes::Catch:
      power_up_.shape.setFillColor(sf::Color::Green);
      break;
    case PowerUpTypes::Duplicate:
      power_up_.shape.setFillColor(sf::Color::Cyan);
      break;
    case PowerUpTypes::Enlarge:
      power_up_.shape.setFillColor(sf::Color::Blue);
      break;
    case PowerUpTypes::Laser:
      power_up_.shape.setFillColor(sf::Color::Red);
      break;
    case PowerUpTypes::Pitufo:
      power_up_.shape.setFillColor(sf::Color::Yellow);
      break;
    case PowerUpTypes::SpeedDown:
    default:
      power_up_.shape.setFillColor(sf::Color::White);
      break;
  }
  power_up_.type = type;
  pwrup_on_screen_ = true;
  ++seq_it_;
  bricks_to_pwup_ = *seq_it_;
  power_up_.shape.setPosition(where);
  power_up_.active = true;
}

void Level::updatePowerUp(float delta_time) {
  float factor = kPowerUpSpeed_ * delta_time;
  if (power_up_.shape.getPosition().y < kScreenHeight) {
    power_up_.shape.move(0.f, factor);
  } else {
    power_up_.active = false;
    pwrup_on_screen_ = false;
  }
}