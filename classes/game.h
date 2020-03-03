#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include <string>
#include <SFML/Graphics.hpp>

#include "../config.h"
#include "ball.h"
#include "gui.h"
#include "level.h"
#include "logger.h"
#include "player.h"

class Game {
 public:
  Game() {}
  ~Game() {}
  void clean();
  k::GameStates getGameState() { return state_; };
  void handleEvents();
  void init();
  void render();
  void update();

 private:
  void handleKeyEvents(const sf::Event key_event);
  void handlePowerUps();
  void initLevelsMenu();
  bool isPaused();
  bool loadLevel(unsigned int lvl_num);
  Ball ball_;
  sf::Clock clock_;
  sf::Event event_;
  sf::Font font_;
  GUI gui_;
  Level game_levels_[k::kMaxLevels];
  Level* current_level_;
  Logger logger_;
  Player player_;
  k::GameStates state_;
  std::string title_;
  sf::RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
