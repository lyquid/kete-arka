#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "../config.h"

class Game {
 public:
  Game() {}
  ~Game() {}

  void clean();
  void handleEvents();
  void init();
  bool isPaused();
  bool isRunning();
  void render();
  void update();

 private:
  sf::Event event_;
  bool paused_ = true;
  bool redraw_ = true;
  bool running_ = false;
  sf::String title_ = kAppName + " - v" + kAppVersion;
  sf::RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
