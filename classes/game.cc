#include "game.h"

void Game::clean() {
  window_.close();
}

void Game::handleEvents() {
  while (window_.pollEvent(event_)) {
    switch (event_.type) {
      case Event::Closed:
        running_ = false;
    }
  }
}

void Game::init() {
  window_.create(VideoMode(kScreenWidth, kScreenHeight, 32), title_, Style::Titlebar | Style::Close);
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
