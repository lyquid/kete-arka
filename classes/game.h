#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "ball.h"
#include "brick.h"
#include "logger.h"
#include "menu.h"
#include "player.h"
#include "ship.h"

class Game {
 public:
  Game() {
    in_title_screen_ = true;
    paused_ = true;
    quit_ = false;
    title_ = kAppName + " - v" + kAppVersion;
  }
  ~Game() {}
  void clean();
  void handleEvents();
  void init();
  bool isPaused();
  bool quit();
  void render();
  void update();

 private:
  void drawBricks();
  void initBricks();
  Ball ball_;
  Brick bricks_[kBrickDefaultRows][kBrickDefaultColumns];
  sf::Clock clock_;
  sf::Event event_;
  sf::Font font_;
  bool in_title_screen_;
  Logger logger_;
  Menu menu_;
  bool paused_;
  Player player_;
  bool quit_;
  Ship ship_;
  sf::String title_;
  sf::RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
