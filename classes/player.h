#ifndef KETE_ARKA_CLASSES_PLAYER_H_
#define KETE_ARKA_CLASSES_PLAYER_H_

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "gui.h"
#include "powerups.h"

struct Vaus {
  sf::RectangleShape shape;
  float speed;
};

class Player {
 public:
  Player():
    dead_(false),
    lives_(kPlayerDefaultLives_),
    score_(0u),
    pwrup_active_(false),
    growth_(0.f),
    pwrup_type_(PowerUpTypes::Nil) {
      vaus_.shape.setFillColor(kVausDefaultColor_);
      vaus_.shape.setSize(kVausDefaultSize_);
      vaus_.shape.setPosition(kVausDefaultPosition_);
      vaus_.speed = kVausDefaultSpeed_;
    }
  ~Player() {}
  void decreaseLives(unsigned int decrease_by = 1u);
  unsigned int getLives() { return lives_; };
  unsigned long long getScore() { return score_; };
  void increaseLives(unsigned int increase_by = 1u);
  void increaseScore(unsigned long long increase_by);
  void linkGUI(GUI* ptg) { gui_ = ptg; };
  bool isDead() { return dead_; };
  void reset();
  /* Vaus stuff */
  void drawVaus(sf::RenderWindow& window);
  const Vaus& getVaus() { return vaus_; };
  sf::Vector2f getVausSize() { return vaus_.shape.getSize(); };
  sf::Vector2f getVausPosition() { return vaus_.shape.getPosition(); };
  float getVausSpeed() { return vaus_.speed; };
  bool moveVaus(const sf::Vector2f& offset);
  void resetVaus();
  /* Power-ups stuff */
  void deactivatePowerUp();
  PowerUpTypes getPowerUp() { return pwrup_type_; };
  bool isPowerUpActive() { return pwrup_active_; };
  void setPowerUp(PowerUpTypes type);
  void resizeVaus();
  bool isVausResizing();
  
 private:
  static const unsigned int kPlayerDefaultLives_;
  bool dead_;
  GUI* gui_;
  unsigned int lives_;
  unsigned long long score_;
  /* Vaus stuff */
  static Vaus vaus_;
  static const sf::Vector2f kVausDefaultSize_;
  static const sf::Vector2f kVausDefaultPosition_;
  static const float kVausDefaultSpeed_;
  static const float kVausMaxLength_;
  static const float kVausGrowth_;
  static const sf::Color kVausDefaultColor_; // to delete some day
  /* Power-ups stuff */
  void enlargeVaus();
  void shortenVaus();
  bool pwrup_active_;
  float growth_;
  PowerUpTypes pwrup_type_;
};

#endif // KETE_ARKA_CLASSES_PLAYER_H_
