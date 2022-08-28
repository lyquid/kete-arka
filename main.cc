#include "src/game.h"

Game *game;

int main(int argc, char *argv[]) {
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  game = new Game();

  while (game->getGameState() != k::GameStates::Quit) {
    game->handleEvents();
    game->update();
    game->render();
  }

  delete game;
  return EXIT_SUCCESS;
}
