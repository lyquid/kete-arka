#include <SFML/Graphics.hpp>

#include "config.h"

int main(int argc, char* argv[]) {

  sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight, 32), (kAppName + " " + kAppVersion));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
          window.close();
    }
    window.clear();
    // window.draw(shape);
    window.display();
  }
  return EXIT_SUCCESS;
}
