#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include "../config.h"
#include "ball.h"
#include "brick.h"
#include "gui.h"
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
  void drawBricks();
  void handleKeyEvents(sf::Event key_event);
  void initBricks();
  bool isPaused();
  Ball ball_;
  Brick bricks_[kBrickDefaultRows][kBrickDefaultColumns];
  sf::Clock clock_;
  sf::Event event_;
  sf::Font font_;
  GUI gui_;
  Logger logger_;
  Player player_;
  Ship ship_;
  GameStates state_;
  sf::String title_;
  sf::RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
