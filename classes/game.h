#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include <SFML/Graphics.hpp>

#include "../config.h"

using namespace sf;

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
  Event event_;
  bool paused_ = true;
  bool redraw_ = true;
  bool running_ = false;
  String title_ = kAppName + " - v" + kAppVersion;
  RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
