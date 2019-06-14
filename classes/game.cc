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
        if (in_title_screen_) {
          switch (event_.key.code) {
            case sf::Keyboard::Escape:
              quit_ = true;
              break;
            case sf::Keyboard::Num1:
              in_title_screen_ = false;
              paused_ = false;
              ball_.reset();
              break;
          }
        } else { // not in menu
          switch (event_.key.code) {
            case sf::Keyboard::Escape:
              paused_ = true;
              in_title_screen_ = true;
              menu_.setRenderFlashingTextFlag(true);
              break;
            case sf::Keyboard::Space:
              paused_ = !paused_;
              menu_.setRenderFlashingTextFlag(true);
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
  if (in_title_screen_) {
    menu_.drawTitleScreen(&window_);
  } else {
    if (paused_) {
      menu_.drawPauseScreen(&window_);
    }
    ball_.draw(window_);
    ship_.draw(window_);
  }
  window_.display();
}

void Game::update() {
  float delta_time = clock_.restart().asSeconds();
  if (!paused_) {
    ball_.move(delta_time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
     || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      ship_.move(sf::Vector2f(-delta_time * kShipDefaultSpeed, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
     || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      ship_.move(sf::Vector2f(delta_time * kShipDefaultSpeed, 0));
    }
  }
}
