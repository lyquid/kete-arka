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
      case sf::Event::KeyPressed:
        if (in_menu_) {
          switch (event_.key.code) {
            case sf::Keyboard::Escape:
              quit_ = true;
              break;
            case sf::Keyboard::Num1:
              in_menu_ = false;
              paused_ = false;
              ball_.reset();
              break;
          }
        } else { // not in menu
          switch (event_.key.code) {
            case sf::Keyboard::Escape:
              paused_ = true;
              in_menu_ = true;
              break;
            case sf::Keyboard::Space:
              paused_ = !paused_;
              break;
          }
        }
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
  if (in_menu_) {
    menu_.drawMenu(&window_);
  } else {
    if (paused_) {
      menu_.drawPause(&window_);
    }
    window_.draw(ball_.getShape()); //TODO: look for a better solution
    window_.draw(ship_.getShape());
  }
  window_.display();
}

void Game::update() {
  float delta_time = clock_.restart().asSeconds();
  if (!paused_) {
    ball_.move(delta_time);
  }
}
