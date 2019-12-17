#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include "../config.h"
#include "ball.h"
#include "gui.h"
#include "level.h"
#include "logger.h"
#include "player.h"
#include "ship.h"

class Game {
 public:
  Game() {}
  ~Game() {}
  void clean();
  GameStates getGameState();
  void handleEvents();
  void init();
  void render();
  void update();

 private:
  void handleKeyEvents(const sf::Event key_event);
  void initLevelsMenu();
  bool isPaused();
  bool loadLevel(const int num_lvl);
  Ball ball_;
  sf::Clock clock_;
  sf::Event event_;
  sf::Font font_;
  GUI gui_;
  Level game_levels_[kTotalLevels];
  Level *current_level_;
  Logger logger_;
  Player player_;
  Ship ship_;
  GameStates state_;
  sf::String title_;
  sf::RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
