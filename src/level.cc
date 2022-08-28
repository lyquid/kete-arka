#include "level.h"

/* Bricks' default settings */
const sf::Vector2f Level::kBrickDefaultSize_ = sf::Vector2f(56.f, 28.f);
/* Bricks' colors */
const sf::Color Level::kBrickDefaultColor_        = sf::Color::White;
const sf::Color Level::kBrickDefaultOutlineColor_ = sf::Color::Black;
const sf::Color Level::kBrickWhite_               = sf::Color(252, 252, 252);
const sf::Color Level::kBrickOrange_              = sf::Color(252, 116,  96);
const sf::Color Level::kBrickLighBlue_            = sf::Color( 60, 188, 252);
const sf::Color Level::kBrickGreen_               = sf::Color(128, 208,  16);
const sf::Color Level::kBrickRed_                 = sf::Color(216,  40,   0);
const sf::Color Level::kBrickBlue_                = sf::Color(  0, 112, 236);
const sf::Color Level::kBrickPink_                = sf::Color(252, 116, 180);
const sf::Color Level::kBrickYellow_              = sf::Color(252, 152,  56);
const sf::Color Level::kBrickSilver_              = sf::Color(188, 188, 188);
const sf::Color Level::kBrickGold_                = sf::Color(240, 188,  60);
/* Borders VertexArrays and Textures */
sf::VertexArray Level::border_left_;
sf::Texture     Level::border_left_tx_;
sf::VertexArray Level::border_right_;
sf::Texture     Level::border_right_tx_;
sf::VertexArray Level::border_top_;
sf::Texture     Level::border_top_tx_;
/* Power-up generation stuff */
const sf::Vector2f Level::kPowerUpSize_ = sf::Vector2f(50.f, 25.f);
k::PowerUp Level::power_up_;
k::PowerUpTypes Level::catched_pwrup_ = k::PowerUpTypes::Nil;
std::vector<sf::Texture> Level::break_tx_(kPowerUpFrames_);
std::vector<sf::Texture> Level::catch_tx_(kPowerUpFrames_);
std::vector<sf::Texture> Level::disruption_tx_(kPowerUpFrames_);
std::vector<sf::Texture> Level::enlarge_tx_(kPowerUpFrames_);
std::vector<sf::Texture> Level::laser_tx_(kPowerUpFrames_);
std::vector<sf::Texture> Level::player_tx_(kPowerUpFrames_);
std::vector<sf::Texture> Level::slow_tx_(kPowerUpFrames_);
std::vector<sf::Texture>::iterator Level::pwrup_tx_it_;
std::vector<sf::Texture>* Level::ptx_;
sf::Clock Level::pwrup_anim_clk_;
unsigned int Level::pwrup_anim_frame_;
/* Break power-up */
const sf::Vector2f Level::kBreakSize_     = sf::Vector2f(28.f, 56.f);
const sf::Vector2f Level::kBreakPosition_ = sf::Vector2f(k::kScreenWidth - kBreakSize_.x, k::kScreenHeight * 0.9f);
sf::RectangleShape Level::break_shape_;
std::vector<sf::Texture> Level::break_effect_tx_(kBreakAnimFrames_);
sf::Clock Level::break_anim_clk_;
unsigned int Level::break_anim_frame_;
/* Laser power-up */
const sf::Vector2f        Level::kLaserSize_ = sf::Vector2f(4.f, 18.f);
sf::Texture               Level::laser_effect_tx_;
std::vector<Level::Laser> Level::lasers_(kMaxLasersOnScreen_);
sf::Clock                 Level::laser_fire_clk_;

bool Level::checkLaserCollisions(const Laser& laser) {
  for (auto i = 0u; i < k::kLevelMaxRows; ++i) {
    for (auto j = 0u; j < k::kLevelMaxColumns; ++j) {
      if (bricks_[i][j].active
      && laser.shape.getGlobalBounds().intersects(bricks_[i][j].shape.getGlobalBounds())) {
        decreaseResistance({i, j});
        return true;
      }
    }
  }
  return false;
}

bool Level::checkPowerUpSpawn() {
  if (!power_up_.active && !disruption_in_effect_) {
    --bricks_to_pwrup_;
    if (!bricks_to_pwrup_) return true;
  }
  return false;
}

void Level::deactivatePowerUp() {
  switch (pwrup_type_) {
    case k::PowerUpTypes::Break:
      break_active_ = false;
      pwrup_active_ = false;
      pwrup_type_ = k::PowerUpTypes::Nil;
      break;
    case k::PowerUpTypes::Laser:
      pwrup_active_ = false;
      pwrup_type_ = k::PowerUpTypes::Nil;
      break;
    case k::PowerUpTypes::Nil:
    case k::PowerUpTypes::Catch:
    case k::PowerUpTypes::Disruption:
    case k::PowerUpTypes::Enlarge:
    case k::PowerUpTypes::Player:
    case k::PowerUpTypes::Slow:
    default:
      // print something horrible to the logger
      break;
  }
}

void Level::deactivatePowerUpFall() {
  power_up_.active = false;
  pwrup_anim_frame_ = 0u;
}

/////////////////////////////////////////////////
/// @brief Decreases the resistance of a brick.
///
/// @param pos - The position of the brick to be decreased.
///
/// Decreases the resistance of a brick and sets inactive if needed.
/// Also updates the score  of the player accordingly.
/////////////////////////////////////////////////
void Level::decreaseResistance(sf::Vector2u pos) {
  if (bricks_[pos.x][pos.y].type != k::BrickTypes::A) {
    if (bricks_[pos.x][pos.y].resistance - 1u <= 0u) {
      bricks_[pos.x][pos.y].resistance = 0u;
      bricks_[pos.x][pos.y].active = false;
      --bricks_remaining_;
      player_->increaseScore(bricks_[pos.x][pos.y].points);
      if (!bricks_remaining_)  {
        completed_ = true;
        return;
      }
      if (bricks_[pos.x][pos.y].type != k::BrickTypes::S && checkPowerUpSpawn()) {
        spawnPowerUp(sf::Vector2f(
          bricks_[pos.x][pos.y].shape.getPosition().x + (kBrickDefaultSize_.x / 2.f) + 1.5f,
          bricks_[pos.x][pos.y].shape.getPosition().y
        ));
      }
    } else {
      --bricks_[pos.x][pos.y].resistance;
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
void Level::draw(sf::RenderWindow& window) {
  window.draw(background_va_, &background_tx_);
  for (auto i = 0u; i < k::kLevelMaxRows; ++i) {
    for (auto j = 0u; j < k::kLevelMaxColumns; ++j) {
      if (bricks_[i][j].active) {
        window.draw(bricks_[i][j].shape);
        if (bricks_[i][j].beveled) {
          window.draw(bricks_[i][j].bevel);
        }
      }
    }
  }
  if (power_up_.active) window.draw(power_up_.shape);
  for (const auto& laser: lasers_) {
    if (laser.active) window.draw(laser.shape);
  }
}

void Level::drawBorders(sf::RenderWindow& window) {
  window.draw(border_left_, &border_left_tx_);
  window.draw(border_right_, &border_right_tx_);
  window.draw(border_top_, &border_top_tx_);
  if (break_active_) window.draw(break_shape_);
}

void Level::eraseCatchedPowerUp() {
  catched_pwrup_ = k::PowerUpTypes::Nil;
  new_pwrup_ = false;
}

bool Level::fireLaser() {
  if (laser_fire_clk_.getElapsedTime().asSeconds() >= kLaserFireRate_
  && lasers_on_screen_ < kMaxLasersOnScreen_) {
    for (auto& laser: lasers_) {
      if (!laser.active) {
        constexpr float offset_left = 11.f;
        constexpr float offset_right = 16.f;
        sf::Vector2f pos;
        pos.y = player_->getVausPosition().y;
        if (laser_flip_) {
          pos.x = player_->getVausPosition().x + offset_left;
        } else {
          pos.x = player_->getVausPosition().x + player_->getVausSize().x - kLaserSize_.x - offset_right;
        }
        laser.shape.setPosition(pos);
        laser.active = true;
        ++lasers_on_screen_;
        laser_fire_clk_.restart();
        laser_flip_ = !laser_flip_;
        return true;
      }
    }
  }
  return false;
}

void Level::init(Player* ptp) {
  /* Basic */
  bricks_remaining_ = 0u;
  completed_ = false;
  player_ = ptp;
  /* Power-ups statics */
  pwrup_anim_frame_ = 0u;
  power_up_.active = false;
  power_up_.shape.setSize(kPowerUpSize_);
  power_up_.shape.setOrigin(kPowerUpSize_.x / 2.f, 0.f);
  /* Power-up effects */
  pwrup_active_ = false;
  pwrup_type_ = k::PowerUpTypes::Nil;
  /* Break power-up */
  break_active_ = false;
  break_anim_frame_ = 0u;
  loadBreakTx();
  /* Laser power-up */
  lasers_on_screen_ = 0u;
  laser_flip_ = true;
  loadLaserTx();
  /* Disruption related */
  disruption_in_effect_ = false;
  /* Background and brick layout */
  initBackground();
  initBricks();
}

void Level::initBackground() {
  switch (background_) {
    case k::Background::Moai:
      if (!background_tx_.loadFromFile(k::kImagePath + std::string("backgrounds/bg_moai.png"))) {
        exit(EXIT_FAILURE);
      }
      break;
    case k::Background::RedCircuit:
      if (!background_tx_.loadFromFile(k::kImagePath + std::string("backgrounds/bg_circuit_red.png"))) {
        exit(EXIT_FAILURE);
      }
      break;
    case k::Background::BlueCircuit:
      if (!background_tx_.loadFromFile(k::kImagePath + std::string("backgrounds/bg_circuit_blue.png"))) {
        exit(EXIT_FAILURE);
      }
      break;
    case k::Background::Green:
      if (!background_tx_.loadFromFile(k::kImagePath + std::string("backgrounds/bg_green.png"))) {
        exit(EXIT_FAILURE);
      }
      break;
    case k::Background::Blue:
      [[fallthrough]];
    default:
      if (!background_tx_.loadFromFile(k::kImagePath + std::string("backgrounds/bg_blue.png"))) {
        exit(EXIT_FAILURE);
      }
      break;
  }
  background_tx_.setRepeated(true);
  background_va_.resize(4);
  background_va_.setPrimitiveType(sf::Quads);
  background_va_[0] = sf::Vector2f(                  k::kGUIBorderThickness, k::kGUIBorderThickness);
  background_va_[1] = sf::Vector2f(k::kScreenWidth - k::kGUIBorderThickness, k::kGUIBorderThickness);
  background_va_[2] = sf::Vector2f(k::kScreenWidth - k::kGUIBorderThickness,       k::kScreenHeight);
  background_va_[3] = sf::Vector2f(                  k::kGUIBorderThickness,       k::kScreenHeight);

  background_va_[0].texCoords = sf::Vector2f(                                           0.f,                                    0.f);
  background_va_[1].texCoords = sf::Vector2f(k::kScreenWidth - (k::kGUIBorderThickness * 2),                                    0.f);
  background_va_[2].texCoords = sf::Vector2f(k::kScreenWidth - (k::kGUIBorderThickness * 2), k::kScreenHeight - k::kGUIBorderThickness);
  background_va_[3].texCoords = sf::Vector2f(                                           0.f, k::kScreenHeight - k::kGUIBorderThickness);
}

void Level::initGraphics() {
  /* Left border */
  if (!border_left_tx_.loadFromFile(k::kImagePath + std::string("borders/border_left.png"))) {
    exit(EXIT_FAILURE);
  }
  border_left_.resize(4);
  border_left_.setPrimitiveType(sf::Quads);
  border_left_[0] = sf::Vector2f(                   0.f,              0.f);
  border_left_[1] = sf::Vector2f(k::kGUIBorderThickness,              0.f);
  border_left_[2] = sf::Vector2f(k::kGUIBorderThickness, k::kScreenHeight);
  border_left_[3] = sf::Vector2f(                   0.f, k::kScreenHeight);
  border_left_[0].texCoords = sf::Vector2f(                   0.f,              0.f);
  border_left_[1].texCoords = sf::Vector2f(k::kGUIBorderThickness,              0.f);
  border_left_[2].texCoords = sf::Vector2f(k::kGUIBorderThickness, k::kScreenHeight);
  border_left_[3].texCoords = sf::Vector2f(                   0.f, k::kScreenHeight);
  /* Right border */
  if (!border_right_tx_.loadFromFile(k::kImagePath + std::string("borders/border_right.png"))) {
    exit(EXIT_FAILURE);
  }
  border_right_.resize(4);
  border_right_.setPrimitiveType(sf::Quads);
  border_right_[0] = sf::Vector2f(k::kScreenWidth - k::kGUIBorderThickness,              0.f);
  border_right_[1] = sf::Vector2f(                         k::kScreenWidth,              0.f);
  border_right_[2] = sf::Vector2f(                         k::kScreenWidth, k::kScreenHeight);
  border_right_[3] = sf::Vector2f(k::kScreenWidth - k::kGUIBorderThickness, k::kScreenHeight);
  border_right_[0].texCoords = sf::Vector2f(                   0.f,              0.f);
  border_right_[1].texCoords = sf::Vector2f(k::kGUIBorderThickness,              0.f);
  border_right_[2].texCoords = sf::Vector2f(k::kGUIBorderThickness, k::kScreenHeight);
  border_right_[3].texCoords = sf::Vector2f(                   0.f, k::kScreenHeight);
  /* Top border */
  if (!border_top_tx_.loadFromFile(k::kImagePath + std::string("borders/border_top.png"))) {
    exit(EXIT_FAILURE);
  }
  border_top_.resize(4);
  border_top_.setPrimitiveType(sf::Quads);
  border_top_[0] = sf::Vector2f(            0.f,                    0.f);
  border_top_[1] = sf::Vector2f(k::kScreenWidth,                    0.f);
  border_top_[2] = sf::Vector2f(k::kScreenWidth, k::kGUIBorderThickness);
  border_top_[3] = sf::Vector2f(            0.f, k::kGUIBorderThickness);
  border_top_[0].texCoords = sf::Vector2f(            0.f,                    0.f);
  border_top_[1].texCoords = sf::Vector2f(k::kScreenWidth,                    0.f);
  border_top_[2].texCoords = sf::Vector2f(k::kScreenWidth, k::kGUIBorderThickness);
  border_top_[3].texCoords = sf::Vector2f(            0.f, k::kGUIBorderThickness);
  /* Power Ups */
  const auto pwr_path = k::kImagePath + std::string("powerups/");
  for (unsigned int i = 0; i < kPowerUpFrames_; ++i) {
    if (!break_tx_.at(i).loadFromFile(pwr_path + "break/" + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
    if (!catch_tx_.at(i).loadFromFile(pwr_path + "catch/" + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
    if (!disruption_tx_.at(i).loadFromFile(pwr_path + "disruption/" + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
    if (!enlarge_tx_.at(i).loadFromFile(pwr_path + "enlarge/" + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
    if (!laser_tx_.at(i).loadFromFile(pwr_path + "laser/" + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
    if (!player_tx_.at(i).loadFromFile(pwr_path + "player/" + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
    if (!slow_tx_.at(i).loadFromFile(pwr_path + "slow/" + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
  }
  /* Laser power-up */
}

/////////////////////////////////////////////////
/// @brief Initializates the bricks of a level.
///
/// Initializates the bricks of a level by reading a
/// layout and positions them.
/////////////////////////////////////////////////
void Level::initBricks() {
  const unsigned int silver_hits = 2u + number_ / 8u;
  unsigned int i, j, surprise_bricks = 0u;
  sf::Vector2f position;
  auto start_y = kBrickDefaultStart_ + k::kGUIBorderThickness;
  for (i = 0u; i < k::kLevelMaxRows; ++i) {
    for (j = 0u; j < k::kLevelMaxColumns; ++j) {
      bricks_[i][j].shape.setSize(kBrickDefaultSize_);
      bricks_[i][j].shape.setOutlineThickness(kBrickDefaultOutline_);
      bricks_[i][j].shape.setOutlineColor(kBrickDefaultOutlineColor_);
      position = sf::Vector2f(bricks_[i][j].shape.getSize().x * j + k::kGUIBorderThickness, start_y);
      bricks_[i][j].shape.setPosition(position);
      bricks_[i][j].active = true;
      bricks_[i][j].beveled = false;
      switch(layout_[i * k::kLevelMaxColumns + j]) {
        case k::BrickTypes::W:
          bricks_[i][j].type = k::BrickTypes::W;
          bricks_[i][j].shape.setFillColor(kBrickWhite_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 50u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::O:
          bricks_[i][j].type = k::BrickTypes::O;
          bricks_[i][j].shape.setFillColor(kBrickOrange_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 60u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::L:
          bricks_[i][j].type = k::BrickTypes::L;
          bricks_[i][j].shape.setFillColor(kBrickLighBlue_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 70u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::G:
          bricks_[i][j].type = k::BrickTypes::G;
          bricks_[i][j].shape.setFillColor(kBrickGreen_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 80u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::R:
          bricks_[i][j].type = k::BrickTypes::R;
          bricks_[i][j].shape.setFillColor(kBrickRed_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 90u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::B:
          bricks_[i][j].type = k::BrickTypes::B;
          bricks_[i][j].shape.setFillColor(kBrickBlue_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 100u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::P:
          bricks_[i][j].type = k::BrickTypes::P;
          bricks_[i][j].shape.setFillColor(kBrickPink_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 110u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::Y:
          bricks_[i][j].type = k::BrickTypes::Y;
          bricks_[i][j].shape.setFillColor(kBrickYellow_);
          bricks_[i][j].resistance = 1u;
          bricks_[i][j].points = 120u;
          ++bricks_remaining_;
          ++surprise_bricks;
          break;
        case k::BrickTypes::S:
          bricks_[i][j].type = k::BrickTypes::S;
          bricks_[i][j].shape.setFillColor(kBrickSilver_);
          bricks_[i][j].resistance = silver_hits;
          bricks_[i][j].points = 50u * number_;
          ++bricks_remaining_;
          bricks_[i][j].beveled = true;
          setBevel(position, {i, j});
          break;
        case k::BrickTypes::A:
          bricks_[i][j].type = k::BrickTypes::A;
          bricks_[i][j].shape.setFillColor(kBrickGold_);
          bricks_[i][j].resistance = 0u;
          bricks_[i][j].points = 0u;
          bricks_[i][j].beveled = true;
          setBevel(position, {i, j});
          break;
        case k::BrickTypes::_:
        default:
          bricks_[i][j].type = k::BrickTypes::_;
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

void Level::setLevels(std::vector<Level>& levels) {
  unsigned int index = 0u;
  for (auto& level: levels) {
    level.number_ = index + 1u;
    level.name_ = k::kProtoLevels[index].name;
    level.background_ = k::kProtoLevels[index].background;
    for (auto i = 0u; i < k::kLevelMaxRows * k::kLevelMaxColumns; ++i) {
      level.layout_[i] = k::kProtoLevels[index].layout[i];
    }
    ++index;
  }
}

bool Level::isLaserActive() {
  if (pwrup_type_ == k::PowerUpTypes::Laser) return true;
  return false;
}

void Level::generatePowerUpSequence(unsigned int surprise_bricks) {
  if (!surprise_bricks || surprise_bricks <= 0u) return;
  const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);
  std::uniform_int_distribution<unsigned int> distribution(1u, surprise_bricks / 7u);
  pwrup_sequence_.clear();
  pwrup_sequence_.resize(surprise_bricks);
  for (auto& x: pwrup_sequence_) { x = distribution(generator); }
  seq_it_ = pwrup_sequence_.cbegin();
  bricks_to_pwrup_ = *seq_it_;
}

void Level::loadBreakTx() {
  break_shape_.setSize(kBreakSize_);
  break_shape_.setOrigin(0.f, break_shape_.getSize().y / 2.f);
  break_shape_.setPosition(kBreakPosition_);
  const auto path = k::kImagePath + std::string("effects/break/");
  for (auto i = 0u; i < kBreakAnimFrames_; ++i) {
    if (!break_effect_tx_.at(i).loadFromFile(path + std::to_string(i) + k::kImageExt)) {
      exit(EXIT_FAILURE);
    }
  }
  break_shape_.setTexture(&break_effect_tx_.front());
}

void Level::loadLaserTx() {
  const auto path = k::kImagePath + std::string("effects/laser/laser.png");
  if (!laser_effect_tx_.loadFromFile(path)) {
    exit(EXIT_FAILURE);
  }
  for (auto& laser: lasers_) {
    laser.active = false;
    laser.shape.setSize(kLaserSize_);
    laser.shape.setTexture(&laser_effect_tx_);
  }
}

void Level::setBevel(sf::Vector2f position, sf::Vector2u brick) {
  const auto bevel_color = sf::Color::Black;
  sf::VertexArray new_bevel(sf::TriangleStrip, 6);
  new_bevel[0].color = bevel_color;
  new_bevel[1].color = bevel_color;
  new_bevel[2].color = bevel_color;
  new_bevel[3].color = bevel_color;
  new_bevel[4].color = bevel_color;
  new_bevel[5].color = bevel_color;
  new_bevel[0].position = sf::Vector2f(position.x + kBrickDefaultBevel_, position.y + kBrickDefaultSize_.y);
  new_bevel[1].position = sf::Vector2f(position.x + kBrickDefaultBevel_, position.y + kBrickDefaultSize_.y - kBrickDefaultBevel_);
  new_bevel[2].position = sf::Vector2f(position.x + kBrickDefaultSize_.x, position.y + kBrickDefaultSize_.y);
  new_bevel[3].position = sf::Vector2f(position.x + kBrickDefaultSize_.x - kBrickDefaultBevel_, position.y + kBrickDefaultSize_.y - kBrickDefaultBevel_);
  new_bevel[4].position = sf::Vector2f(position.x + kBrickDefaultSize_.x, position.y + kBrickDefaultBevel_);
  new_bevel[5].position = sf::Vector2f(position.x + kBrickDefaultSize_.x - kBrickDefaultBevel_, position.y + kBrickDefaultBevel_);
  bricks_[brick.x][brick.y].bevel = new_bevel;
}

void Level::setPowerUp(k::PowerUpTypes type) {
  switch (type) {
    case k::PowerUpTypes::Break:
      break_active_ = true;
      break_anim_frame_ = 0u;
      break_anim_clk_.restart();
      pwrup_active_ = true;
      pwrup_type_ = type;
      break;
    case k::PowerUpTypes::Laser:
      pwrup_active_ = true;
      pwrup_type_ = type;
      break;
    case k::PowerUpTypes::Nil:
    case k::PowerUpTypes::Catch:
    case k::PowerUpTypes::Disruption:
    case k::PowerUpTypes::Enlarge:
    case k::PowerUpTypes::Player:
    case k::PowerUpTypes::Slow:
    default:
      // print something horrible to the logger
      break;
  }
}

void Level::spawnPowerUp(const sf::Vector2f& where) {
  const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<unsigned int> distribution(1u , static_cast<unsigned int>(k::PowerUpTypes::count) - 1u);
  const auto type = static_cast<k::PowerUpTypes>(distribution(generator));
  switch (type) {
    case k::PowerUpTypes::Nil:
      return;
    case k::PowerUpTypes::Break:
      power_up_.shape.setTexture(&break_tx_.front());
      pwrup_tx_it_ = break_tx_.begin();
      ptx_ = &break_tx_;
      break;
    case k::PowerUpTypes::Catch:
      power_up_.shape.setTexture(&catch_tx_.front());
      pwrup_tx_it_ = catch_tx_.begin();
      ptx_ = &catch_tx_;
      break;
    case k::PowerUpTypes::Disruption:
      power_up_.shape.setTexture(&disruption_tx_.front());
      pwrup_tx_it_ = disruption_tx_.begin();
      ptx_ = &disruption_tx_;
      break;
    case k::PowerUpTypes::Enlarge:
      power_up_.shape.setTexture(&enlarge_tx_.front());
      pwrup_tx_it_ = enlarge_tx_.begin();
      ptx_ = &enlarge_tx_;
      break;
    case k::PowerUpTypes::Laser:
      power_up_.shape.setTexture(&laser_tx_.front());
      pwrup_tx_it_ = laser_tx_.begin();
      ptx_ = &laser_tx_;
      break;
    case k::PowerUpTypes::Player:
      power_up_.shape.setTexture(&player_tx_.front());
      pwrup_tx_it_ = player_tx_.begin();
      ptx_ = &player_tx_;
      break;
    case k::PowerUpTypes::Slow:
      power_up_.shape.setTexture(&slow_tx_.front());
      pwrup_tx_it_ = slow_tx_.begin();
      ptx_ = &slow_tx_;
      break;
    default:
      return;
  }
  power_up_.active = true;
  power_up_.shape.setPosition(where);
  power_up_.type = type;

  ++pwrup_anim_frame_;
  ++seq_it_;
  bricks_to_pwrup_ = *seq_it_;
}

void Level::update(float delta_time) {
  if (power_up_.active) updatePowerUpFall(delta_time);
  if (isBreakActive()) updateBreakAnim();
  if (lasers_on_screen_) updateLasers(delta_time);
}

void Level::updateBreakAnim() {
  if (break_anim_clk_.getElapsedTime().asSeconds() >= kBreakAnimSpeed_) {
    break_anim_clk_.restart();
    if (break_anim_frame_ >= kBreakAnimFrames_) break_anim_frame_ = 0u;
    break_shape_.setTexture(&break_effect_tx_.at(break_anim_frame_));
    ++break_anim_frame_;
  }
}

void Level::updateLasers(float delta_time) {
  const auto factor = kLaserSpeed_ * delta_time;
  for (auto& laser: lasers_) {
    if (laser.active) {
      if (laser.shape.getPosition().y <= k::kGUIBorderThickness
      || checkLaserCollisions(laser)) {
        laser.active = false;
        --lasers_on_screen_;
      } else {
        laser.shape.move(0.f, -factor);
      }
    }
  }
}

void Level::updatePowerUpFall(float delta_time) {
  /* Check player collision */
  if (player_->getVaus().shape.getGlobalBounds().intersects(power_up_.shape.getGlobalBounds())) {
    new_pwrup_ = true;
    catched_pwrup_ = power_up_.type;
    deactivatePowerUpFall();
    return;
  }
  /* Update position */
  if (power_up_.shape.getPosition().y < k::kScreenHeight) {
    const auto factor = kPowerUpSpeed_ * delta_time;
    power_up_.shape.move(0.f, factor);
  } else {
    deactivatePowerUpFall();
    return;
  }
  /* Update animation */
  if (pwrup_anim_clk_.getElapsedTime().asSeconds() >= kPowerUpAnimSpeed_) {
    pwrup_anim_clk_.restart();
    power_up_.shape.setTexture(&*pwrup_tx_it_);
    if (pwrup_anim_frame_ != kPowerUpFrames_ - 1u) {
      ++pwrup_anim_frame_;
      ++pwrup_tx_it_;
    } else {
      pwrup_anim_frame_ = 0u;
      pwrup_tx_it_ = ptx_->begin();
    }
  }
}
