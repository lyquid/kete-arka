#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "ball.h"
#include "menu.h"
#include "ship.h"

class Game {
 public:
  Game() {
    in_menu_ = true;
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
  Ball ball_;
  sf::Clock clock_;
  sf::Event event_;
  sf::Font font_;
  bool in_menu_;
  Menu menu_;
  bool paused_;
  bool quit_;
  Ship ship_;
  sf::String title_;
  sf::RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
