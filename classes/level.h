#ifndef KETE_ARKA_CLASSES_LEVEL_H_
#define KETE_ARKA_CLASSES_LEVEL_H_

#include <chrono>
#include <random>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../config.h"
#include "../levels.h"
#include "player.h"

class Level {
 public:
  Level():
    completed_(false),
    bricks_remaining_(0u),
    new_pwrup_(false),
    pwrup_active_(false),
    pwrup_type_(k::PowerUpTypes::Nil),
    break_active_(false),
    laser_flip_(true),
    lasers_on_screen_(0u),
    disruption_in_effect_(false) {}
  ~Level() {}
  /* Setters & getters */
  void complete() { completed_ = true; };
  void setNumber(unsigned int lvl_num) { number_ = lvl_num; };
  k::Brick (*getBricks())[k::kLevelMaxColumns] { return bricks_; };
  std::string getName() const { return name_; };
  unsigned int getNumber() const { return number_; };
  bool isCompleted() const { return completed_; };
  /* Initializers */
  void init(Player* ptp);
  static void initGraphics();
  static void setLevels(std::vector<Level>& levels);
  /* Others */
  void decreaseResistance(sf::Vector2u pos);
  void draw(sf::RenderWindow& window);
  void drawBorders(sf::RenderWindow& window);
  void update(float delta_time);
  /* Power-up generation stuff */
  bool catchedPowerUp() const { return new_pwrup_; };
  k::PowerUpTypes getCatchedPowerUp() const { return catched_pwrup_; };
  void eraseCatchedPowerUp();
  /* Power-up effects */
  void deactivatePowerUp();
  k::PowerUpTypes getPowerUp() const { return pwrup_type_; };
  bool isPowerUpActive() const { return pwrup_active_; };
  void setPowerUp(k::PowerUpTypes type);
  /* Break power-up */
  bool isBreakActive() const { return break_active_; };
  /* Laser power-up */
  bool fireLaser();
  bool isLaserActive();
  /* Disruption related */
  void setDisruptionStatus(bool status) { disruption_in_effect_ = status; };

 private:
  struct Laser {
    bool               active;
    sf::RectangleShape shape;
  };
  /* Basic */
  bool completed_;
  std::string name_;
  unsigned int number_;
  Player* player_;
  /* Bricks */
  void initBricks();
  void setBevel(sf::Vector2f position, sf::Vector2u brick);
  k::Brick bricks_[k::kLevelMaxRows][k::kLevelMaxColumns];
  unsigned int bricks_remaining_;
  k::BrickTypes layout_[k::kLevelMaxRows * k::kLevelMaxColumns];
  /* Background and borders */
  void initBackground();
  k::Background background_;
  sf::VertexArray background_va_;
  sf::Texture background_tx_;
  static sf::VertexArray border_left_;
  static sf::Texture border_left_tx_;
  static sf::VertexArray border_right_;
  static sf::Texture border_right_tx_;
  static sf::VertexArray border_top_;
  static sf::Texture border_top_tx_;
  /* Power-up generation stuff */
  bool checkPowerUpSpawn();
  void deactivatePowerUpFall();
  void generatePowerUpSequence(unsigned int surprise_bricks);
  void spawnPowerUp(const sf::Vector2f& where);
  void updatePowerUpFall(float delta_time);
  static k::PowerUp power_up_;
  static k::PowerUpTypes catched_pwrup_;
  bool new_pwrup_;
  static const sf::Vector2f kPowerUpSize_;
  static constexpr float        kPowerUpSpeed_     = 150.f;
  static constexpr float        kPowerUpAnimSpeed_ = 0.15f;
  static constexpr unsigned int kPowerUpFrames_    = 8u;
  static std::vector<sf::Texture> break_tx_;
  static std::vector<sf::Texture> catch_tx_;
  static std::vector<sf::Texture> disruption_tx_;
  static std::vector<sf::Texture> enlarge_tx_;
  static std::vector<sf::Texture> laser_tx_;
  static std::vector<sf::Texture> player_tx_;
  static std::vector<sf::Texture> slow_tx_;
  static std::vector<sf::Texture>::iterator pwrup_tx_it_;
  static std::vector<sf::Texture>* ptx_;
  static sf::Clock pwrup_anim_clk_;
  static unsigned int pwrup_anim_frame_;
  std::vector<unsigned int> pwrup_sequence_;
  std::vector<unsigned int>::const_iterator seq_it_;
  unsigned int bricks_to_pwrup_;
  /* Power-up effects */
  bool pwrup_active_;
  k::PowerUpTypes pwrup_type_;
  /* Break power-up */
  void loadBreakTx();
  void updateBreakAnim();
  bool break_active_;
  static const sf::Vector2f kBreakSize_;
  static const sf::Vector2f kBreakPosition_;
  static constexpr unsigned int kBreakAnimFrames_ = 8u;;
  static constexpr float kBreakAnimSpeed_ = 0.04f;
  static sf::RectangleShape break_shape_;
  static std::vector<sf::Texture> break_effect_tx_;
  static sf::Clock break_anim_clk_;
  static unsigned int break_anim_frame_;
  /* Laser power-up */
  bool checkLaserCollisions(const Laser& laser);
  void loadLaserTx();
  void updateLasers(float delta_time);
  static const sf::Vector2f kLaserSize_;
  // static constexpr float kLaserDuration_ = 5.f;
  static constexpr float kLaserSpeed_ = 700.f;
  static constexpr float kLaserFireRate_ = 0.1f;
  static constexpr unsigned int kMaxLasersOnScreen_ = 500u;
  static sf::Texture laser_effect_tx_;
  static std::vector<Level::Laser> lasers_;
  static sf::Clock laser_fire_clk_;
  bool laser_flip_;
  unsigned int lasers_on_screen_;
  /* Disruption related */
  bool disruption_in_effect_;
  /* Bricks' default settings */
  static constexpr float kBrickDefaultStart_   = 0.f;
  static constexpr float kBrickDefaultOutline_ = -1.5f;
  static constexpr float kBrickDefaultBevel_   = 5.f; 
  static const sf::Vector2f kBrickDefaultSize_;
  /* Bricks' colors */
  static const sf::Color kBrickDefaultColor_;
  static const sf::Color kBrickDefaultOutlineColor_;
  static const sf::Color kBrickWhite_;
  static const sf::Color kBrickOrange_;
  static const sf::Color kBrickLighBlue_;
  static const sf::Color kBrickGreen_;
  static const sf::Color kBrickRed_;
  static const sf::Color kBrickBlue_;
  static const sf::Color kBrickPink_;
  static const sf::Color kBrickYellow_;
  static const sf::Color kBrickSilver_;
  static const sf::Color kBrickGold_;
};

#endif // KETE_ARKA_CLASSES_LEVEL_H_