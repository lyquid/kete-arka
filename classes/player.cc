#include "player.h"

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
void Player::decreaseLives(const int decrease_by) {
  if (lives_ - decrease_by <= 0) {
    lives_ = 0;
    dead_ = true;
  } else {
    lives_ -= decrease_by;
  }
  gui_->setLivesText(lives_);
}

/////////////////////////////////////////////////
/// @brief Increases the score of the player by the amount specified.
///
/// @param increase_by The amount to increase the score by.
///
/// Increases the score of the player by the amount specified. 
/////////////////////////////////////////////////
void Player::increaseScore(const int increase_by) {
  score_ += increase_by;
  gui_->setScoreText(score_);
}

/////////////////////////////////////////////////
/// @brief Returns true if the player is dead.
///
/// @return A boolean representing the players's dead status.
///
/// Returns true if the player is dead. False otherwise.
/////////////////////////////////////////////////
bool Player::isDead() {
  return dead_;
}

/////////////////////////////////////////////////
/// @brief Initializes the player's properties.
///
/// Sets the dead status to false, the lives to the default 
/// starting lives and the score to zero.
/////////////////////////////////////////////////
void Player::init(GUI *ptg) {
  gui_ = ptg;
  reset();
}

/////////////////////////////////////////////////
/// @brief Returns the players's lives.
///
/// @return An integer representing the player's lives.
///
/// An integer representing the player's current lives.
/////////////////////////////////////////////////
int Player::getLives() {
  return lives_;
}

/////////////////////////////////////////////////
/// @brief Returns the players's score.
///
/// @return An integer representing the player's score.
///
/// An integer representing the player's current score.
/////////////////////////////////////////////////
int Player::getScore() {
  return score_;
}

////////////////////////////////////////////////
void Player::reset() {
  dead_ = false;
  lives_ = kPlayerDefaultLives;
  score_ = 0;
}