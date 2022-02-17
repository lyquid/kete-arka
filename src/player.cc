#include "player.h"

/* Vaus stuff */
k::Vaus Player::vaus_;
const sf::Vector2f Player::kVausDefaultSize_          = sf::Vector2f(95.f, 28.f);
const sf::Vector2f Player::kVausDefaultCollisionRect_ = sf::Vector2f(kVausDefaultSize_.x - 10.f, kVausDefaultSize_.y);
const sf::Vector2f Player::kVausDefaultPosition_      = sf::Vector2f((k::kScreenWidth - kVausDefaultCollisionRect_.x) / 2.f, k::kScreenHeight * 0.9f);
const float        Player::kVausMaxLength_            = kVausDefaultSize_.x * 1.66f;
unsigned int       Player::vaus_anim_frame_;
sf::Clock          Player::vaus_anim_clk_;
bool               Player::show_collision_rect_;
/* Laser Vaus */
unsigned int       Player::vaus_laser_anim_frame_;

void Player::deactivatePowerUp() {
  switch (pwrup_type_) {
    case k::PowerUpTypes::Enlarge:
      growth_ = -kVausGrowth_;
      break;
    case k::PowerUpTypes::Laser:
      deactivateLaserVaus();
      break;
    case k::PowerUpTypes::Nil:
    case k::PowerUpTypes::Break:
    case k::PowerUpTypes::Catch:
    case k::PowerUpTypes::Disruption:
    case k::PowerUpTypes::Player:
    case k::PowerUpTypes::Slow:
    default:
      // print something horrible to the logger
      break;
  }
  pwrup_type_ = k::PowerUpTypes::Nil;
  pwrup_active_ = false;
}

/////////////////////////////////////////////////
/// @brief Decreases the lives of the player by the amount specified.
///
/// @param decrease_by The amount to decrease the lives by.
///
/// Decreases the lives of the player by the amount specified. 
/// If no amount is specified, decreases the lives by 1. 
/// If lives equals 0, sets the player dead.
/// Note that lives cannot be decreased below 0.
/////////////////////////////////////////////////
void Player::decreaseLives(unsigned int decrease_by) {
  if (lives_ - decrease_by <= 0u) {
    lives_ = 0u;
    dead_ = true;
  } else {
    lives_ -= decrease_by;
  }
  gui_->setLivesText(lives_);
}

/////////////////////////////////////////////////
/// @brief Draws the ship to the specified RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the ship on.
///
/// Draws the ship to the specified RenderWindow.
/////////////////////////////////////////////////
void Player::drawVaus(sf::RenderWindow& window) {
  window.draw(vaus_.shape);
  if (show_collision_rect_) window.draw(vaus_.collision_rect);
}

void Player::enlargeVaus() {
  const auto vaus_shapx = vaus_.shape.getSize().x;
  const auto vaus_colx = vaus_.collision_rect.getSize().x;
  if (vaus_colx >= kVausMaxLength_) {
    growth_ = 0.f;
    return;
  } else {
    const auto displ = growth_ / 2.f;
    auto new_x = displ;
    if (vaus_.collision_rect.getPosition().x - displ < k::kGUIBorderThickness) {
      new_x = 0.f;
    }
    if (vaus_.collision_rect.getPosition().x + vaus_colx - displ > k::kScreenWidth - k::kGUIBorderThickness) {
      new_x = growth_;
    }
    vaus_.collision_rect.move(-new_x, 0.f);
    vaus_.shape.move(-new_x, 0.f);

    vaus_.collision_rect.setSize(sf::Vector2f(
      vaus_colx + growth_,
      vaus_.collision_rect.getSize().y
    ));
    vaus_.shape.setSize(sf::Vector2f(
      vaus_shapx + growth_,
      vaus_.shape.getSize().y
    ));
  }
}

///
void Player::increaseLives(unsigned int increase_by) {
  lives_ += increase_by;
  gui_->setLivesText(lives_);
}

/////////////////////////////////////////////////
/// @brief Increases the score of the player by the amount specified.
///
/// @param increase_by The amount to increase the score by.
///
/// Increases the score of the player by the amount specified. 
/////////////////////////////////////////////////
void Player::increaseScore(unsigned long long increase_by) {
  score_ += increase_by;
  gui_->setScoreText(score_);
}

bool Player::isVausResizing() {
  if (growth_ != 0.f) return true;
  return false;
}

/////////////////////////////////////////////////
/// @brief Moves the ship in a valid way.
///
/// @param offset - The sf::Vector2f to be added to the current position.
///
/// Checks if we want to move the ship right or left and 
/// keeps the ship within the screen boundaries.
/////////////////////////////////////////////////
bool Player::moveVaus(const sf::Vector2f& offset) {
  bool lateral_hit = false;
  vaus_.collision_rect.move(offset);
  /* Left hit */
  if (vaus_.collision_rect.getPosition().x < k::kGUIBorderThickness) {
    vaus_.collision_rect.setPosition(k::kGUIBorderThickness, vaus_.collision_rect.getPosition().y);
    lateral_hit = true;
  /* Right hit */
  } else if (vaus_.collision_rect.getPosition().x + vaus_.collision_rect.getSize().x > k::kScreenWidth - k::kGUIBorderThickness) {
    vaus_.collision_rect.setPosition(k::kScreenWidth - k::kGUIBorderThickness - vaus_.collision_rect.getSize().x, vaus_.collision_rect.getPosition().y);
    lateral_hit = true;
  }
  vaus_.shape.setPosition(vaus_.collision_rect.getPosition());
  return lateral_hit;
}

Player::Player():
  dead_(false),
  lives_(kPlayerDefaultLives_),
  score_(0u),
  pwrup_active_(false),
  growth_(0.f),
  pwrup_type_(k::PowerUpTypes::Nil) {
    vaus_.textures.resize(kVausAnimFrames_);
    const auto path = k::kImagePath + std::string("vaus/");
    for (auto i = 0u; i < kVausAnimFrames_; ++i) {
      if (!vaus_.textures.at(i).loadFromFile(path + std::to_string(i) + k::kImageExt)) {
        exit(EXIT_FAILURE);
      }
    }
    vaus_.laser_textures.resize(kVausLaserAnimFrames_);
    const auto laser_path = k::kImagePath + std::string("vaus/laser/");
    for (auto i = 0u; i < kVausLaserAnimFrames_; ++i) {
      if (!vaus_.laser_textures.at(i).loadFromFile(laser_path + std::to_string(i) + k::kImageExt)) {
        exit(EXIT_FAILURE);
      }
    }
    show_collision_rect_ = false;
    vaus_.shape.setTexture(&vaus_.textures.front());
    vaus_.collision_rect.setFillColor(sf::Color::Transparent);
    vaus_.collision_rect.setOutlineColor(sf::Color::Green);
    vaus_.collision_rect.setOutlineThickness(-1.f);
  }

////////////////////////////////////////////////
void Player::reset() {
  dead_ = false;
  lives_ = kPlayerDefaultLives_;
  gui_->setLivesText(lives_);
  score_ = 0u;
  deactivatePowerUp();
}

void Player::resetVaus() {
  vaus_.shape.setSize(kVausDefaultSize_);
  vaus_.shape.setPosition(kVausDefaultPosition_);
  vaus_.speed = kVausDefaultSpeed_;
  vaus_.collision_rect.setSize(kVausDefaultCollisionRect_);
  vaus_.collision_rect.setPosition(kVausDefaultPosition_);
  vaus_anim_frame_ = 0u;
  vaus_laser_anim_frame_ = 0u;
  deactivatePowerUp();
}

void Player::resizeVaus() {
  if (growth_ > 0.f) enlargeVaus();
  else shortenVaus();
}

void Player::setPowerUp(const k::PowerUpTypes& type) {
  switch (type) {
    case k::PowerUpTypes::Enlarge: {
      growth_ = kVausGrowth_;
      pwrup_type_ = type;
      pwrup_active_ = true;
      break;
    }
    case k::PowerUpTypes::Laser:
      pwrup_type_ = type;
      pwrup_active_ = true;
      activateLaserVaus();
      break;
    case k::PowerUpTypes::Nil:
    case k::PowerUpTypes::Break:
    case k::PowerUpTypes::Catch:
    case k::PowerUpTypes::Disruption:
    case k::PowerUpTypes::Player:
    case k::PowerUpTypes::Slow:
    default:
      // print something horrible to the logger
      break;
  }
}

void Player::shortenVaus() {
  if (vaus_.collision_rect.getSize().x > kVausDefaultCollisionRect_.x) {
    vaus_.collision_rect.move(-growth_ / 2.f, 0.f);
    vaus_.shape.move(-growth_ / 2.f, 0.f);
    vaus_.collision_rect.setSize(sf::Vector2f(
      vaus_.collision_rect.getSize().x + growth_,
      vaus_.collision_rect.getSize().y
    ));
    vaus_.shape.setSize(sf::Vector2f(
      vaus_.shape.getSize().x + growth_,
      vaus_.shape.getSize().y
    ));
  } else {
    growth_ = 0.f;
  }
}

void Player::updateVausAnim() {
  switch (pwrup_type_) {
    case k::PowerUpTypes::Laser:
      // THIS IS PROVISIONAL
      if (vaus_anim_clk_.getElapsedTime().asSeconds() >= kVausLaserAnimSpeed_) {
        vaus_anim_clk_.restart();
        vaus_laser_anim_frame_ < kVausLaserAnimFrames_ - 1u ? ++vaus_laser_anim_frame_ : vaus_laser_anim_frame_ = 0u;
        vaus_.shape.setTexture(&vaus_.laser_textures.at(vaus_laser_anim_frame_));
      }
    break;
    default:
      if (vaus_anim_clk_.getElapsedTime().asSeconds() >= kVausAnimSpeed_) {
        vaus_anim_clk_.restart();
        vaus_anim_frame_ < kVausAnimFrames_ - 1u ? ++vaus_anim_frame_ : vaus_anim_frame_ = 0u;
        vaus_.shape.setTexture(&vaus_.textures.at(vaus_anim_frame_));
      }
    break;
  }
}

void Player::activateLaserVaus() {
  vaus_.shape.setTexture(&vaus_.laser_textures.front());
}

void Player::deactivateLaserVaus() {
  vaus_.shape.setTexture(&vaus_.textures.front());
}