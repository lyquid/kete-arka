#include "classes/game.h"

Game *game;

int main(int argc, char *argv[]) {
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  game = new Game();
  game->init();

  while (game->getGameState() != Quit) {
    game->handleEvents();
    game->update();
    game->render();
  }
  game->clean();
  delete game;
  return EXIT_SUCCESS;
}
