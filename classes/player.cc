#include "player.h"

const unsigned int Player::kPlayerDefaultLives_ = 3u;
/* Vaus consts */
const sf::Vector2f Player::kVausDefaultSize_ = sf::Vector2f(80.f, 15.f);
const sf::Vector2f Player::kVausDefaultPosition_ = sf::Vector2f((kScreenWidth - kVausDefaultSize_.x) / 2.f, kScreenHeight * 0.9f);
const float        Player::kVausDefaultSpeed_ = 500.f;
const sf::Color    Player::kVausDefaultColor_ = sf::Color::White;

void Player::deactivatePowerUp() {
  switch (pwrup_type_) {
    case PowerUpTypes::Enlarge:
      vaus_.shape.setSize(kVausDefaultSize_);
      pwrup_type_ = PowerUpTypes::Nil;
      pwrup_active_ = false;
      break;
    case PowerUpTypes::Nil:
    case PowerUpTypes::Break:
    case PowerUpTypes::Catch:
    case PowerUpTypes::Disruption:
    case PowerUpTypes::Laser:
    case PowerUpTypes::Player:
    case PowerUpTypes::Slow:
    default:
      // print something horrible to the logger
      break;
  }
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

/////////////////////////////////////////////////
/// @brief Moves the ship in a valid way.
///
/// @param offset - The sf::Vector2f to be added to the current position.
///
/// Checks if we want to move the ship right or left and 
/// keeps the ship within the screen boundaries.
/////////////////////////////////////////////////
bool Player::moveVaus(const sf::Vector2f& offset) {
  bool success = false;
  if (offset.x < 0 && vaus_.shape.getPosition().x + offset.x >= kGUIBorderThickness) {
    // wants to go left
    vaus_.shape.move(offset);
    success = true;
  } else if (offset.x > 0 && vaus_.shape.getPosition().x + vaus_.shape.getSize().x + offset.x <= kScreenWidth - kGUIBorderThickness) {
    // wants to go right
    vaus_.shape.move(offset);
    success = true;
  }
  return success;
}

////////////////////////////////////////////////
void Player::reset() {
  dead_ = false;
  lives_ = kPlayerDefaultLives_;
  gui_->setLivesText(lives_);
  score_ = 0u;
  pwrup_active_ = false;
  pwrup_type_ = PowerUpTypes::Nil;
}

void Player::resetVaus() {
  vaus_.shape.setFillColor(kVausDefaultColor_);
  vaus_.shape.setSize(kVausDefaultSize_);
  vaus_.shape.setPosition(kVausDefaultPosition_);
  vaus_.speed = kVausDefaultSpeed_;
}

void Player::setPowerUp(PowerUpTypes type) {
  switch (type) {
    case PowerUpTypes::Enlarge: {
      pwrup_type_ = type;
      pwrup_active_ = true;
      const auto enlargement = vaus_.shape.getSize().x * 1.66f;
      vaus_.shape.setSize(sf::Vector2f(enlargement, vaus_.shape.getSize().y));
      break;
    }
    case PowerUpTypes::Nil:
    case PowerUpTypes::Break:
    case PowerUpTypes::Catch:
    case PowerUpTypes::Disruption:
    case PowerUpTypes::Laser:
    case PowerUpTypes::Player:
    case PowerUpTypes::Slow:
    default:
      // print something horrible to the logger
      break;
  }
}