#ifndef KETE_ARKA_CLASSES_PLAYER_H_
#define KETE_ARKA_CLASSES_PLAYER_H_

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "gui.h"

class Player {
 public:
  Player();
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
  const k::Vaus& getVaus() { return vaus_; };
  sf::Vector2f getVausSize() { return vaus_.shape.getSize(); };
  sf::Vector2f getVausPosition() { return vaus_.shape.getPosition(); };
  float getVausSpeed() { return vaus_.speed; };
  bool moveVaus(const sf::Vector2f& offset);
  void resetVaus();
  void toggleCollisionRect() { show_collision_rect_ = !show_collision_rect_; };
  void updateVausAnim();
  /* Power-ups stuff */
  void deactivatePowerUp();
  k::PowerUpTypes getPowerUp() { return pwrup_type_; };
  bool isPowerUpActive() { return pwrup_active_; };
  void setPowerUp(const k::PowerUpTypes& type);
  void resizeVaus();
  bool isVausResizing();

 private:
  static constexpr unsigned int kPlayerDefaultLives_ = 3u;
  bool dead_;
  GUI* gui_;
  unsigned int lives_;
  unsigned long long score_;
  /* Vaus stuff */
  static k::Vaus vaus_;
  static const sf::Vector2f kVausDefaultSize_;
  static const sf::Vector2f kVausDefaultPosition_;
  static const sf::Vector2f kVausDefaultCollisionRect_;
  static constexpr float        kVausDefaultSpeed_ = 500.f;
  static constexpr float        kVausAnimSpeed_    = 0.10f;
  static constexpr unsigned int kVausAnimFrames_   = 6u;
  static           unsigned int vaus_anim_frame_;
  static           sf::Clock    vaus_anim_clk_;
  static           bool         show_collision_rect_;
  /* Enlarge Vaus */
  static constexpr float kVausGrowth_ = 0.5f;
  static const     float kVausMaxLength_;
  void enlargeVaus();
  void shortenVaus();
  float growth_;
  /* Laser Vaus */
  void activateLaserVaus();
  void deactivateLaserVaus();
  static constexpr unsigned int kVausLaserAnimFrames_ = 6u;
  static constexpr float        kVausLaserAnimSpeed_  = 0.20f;
  static           unsigned int vaus_laser_anim_frame_;
  /* Power-ups stuff */
  bool pwrup_active_;
  k::PowerUpTypes pwrup_type_;
};

#endif // KETE_ARKA_CLASSES_PLAYER_H_
