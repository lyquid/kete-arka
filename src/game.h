#ifndef KETE_ARKA_CLASSES_GAME_H_
#define KETE_ARKA_CLASSES_GAME_H_

#include <iterator>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../config.h"
#include "ball.h"
#include "gui.h"
#include "level.h"
#include "logger.h"
#include "player.h"

class Game {
 public:
  Game();
  ~Game() { clean(); }
  k::GameStates getGameState() const { return state_; }
  void handleEvents();
  void render();
  void update();

 private:
  void clean();
  void handleKeyEvents(const sf::Event& key_event);
  void handlePowerUps();
  void initLevelsMenu();
  bool loadLevel(unsigned int lvl_num);
  Ball ball_;
  sf::Clock clock_;
  sf::Event event_;
  GUI gui_;
  std::vector<Level> levels_;
  std::vector<Level>::iterator level_ {};
  Logger logger_;
  Player player_;
  k::GameStates state_;
  std::string title_;
  sf::RenderWindow window_;
};

#endif  // KETE_ARKA_CLASSES_GAME_H_
