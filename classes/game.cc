#include "game.h"

void Game::clean() {
  window_.close();
}

void Game::handleEvents() {
  while (window_.pollEvent(event_)) {
    switch (event_.type) {
      case sf::Event::Closed:
        running_ = false;
    }
  }
}

void Game::init() {
  window_.create(sf::VideoMode(kScreenWidth, kScreenHeight, 32), title_, sf::Style::Titlebar | sf::Style::Close);
  running_ = true;
}

bool Game::isRunning() {
  return running_;
}

void Game::render() {
  window_.clear();
  // window.draw(shape);
  window_.display();
}

void Game::update() {}
