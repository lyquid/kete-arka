#include "game.h"

void Game::clean() {
  window_.close();
}

void Game::handleEvents() {
  while (window_.pollEvent(event_)) {
    switch (event_.type) {
      case sf::Event::Closed:
        quit_ = true;
        break;
    }
  }
}

void Game::init() {
  window_.create(sf::VideoMode(kScreenWidth, kScreenHeight, 32), title_, sf::Style::Titlebar | sf::Style::Close);
  window_.setVerticalSyncEnabled(true);
  if (!font_.loadFromFile("assets/PressStart2P.ttf")) {
    exit(EXIT_FAILURE);
  } else {
    menu_.init(&font_);
  }
}

bool Game::quit() {
  return quit_;
}

void Game::render() {
  window_.clear();
  // window.draw(shape);
  menu_.draw(&window_);
  window_.display();
}

void Game::update() {}
