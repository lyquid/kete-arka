#include "game.h"

void Game::clean() {
  window_.close();
  logger_.write("Successfully closed window.");
}

void Game::drawBricks() {
  for (int i = 0; i < kBrickDefaultRows; ++i) {
    for (int j = 0; j < kBrickDefaultColumns; ++j) {
      if (bricks_[i][j].isActive()) {
        bricks_[i][j].draw(window_);
      }
    }
  }
}

void Game::goToTitle() {
  paused_ = true;
  in_title_screen_ = true;
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
              player_.reset();
              ball_.reset();
              ship_.reset();
              gui_.reset();
              initBricks();
              break;
          }
        } else { // not in menu
          switch (event_.key.code) {
            case sf::Keyboard::Escape:
              goToTitle();
              gui_.setRenderFlashingTextFlag(true);
              break;
            case sf::Keyboard::Space:
              paused_ = !paused_;
              gui_.setRenderFlashingTextFlag(true);
              break;
          }
        }
        break;
    }
  }
}

void Game::init() {
  logger_.start();
  window_.create(sf::VideoMode(kScreenWidth, kScreenHeight, 32), title_, sf::Style::Titlebar | sf::Style::Close);
  logger_.write("Successfully created display.");
  window_.setVerticalSyncEnabled(true);
  if (!font_.loadFromFile("assets/PressStart2P.ttf")) {
    logger_.write("ERROR: Failed loading font.");
    exit(EXIT_FAILURE);
  } else {
    gui_.init(font_);
    logger_.write("Successfully initialized GUI.");
    ball_.init(&player_);
    logger_.write("Successfully initialized ball.");
    player_.init(&gui_);
    logger_.write("Successfully initialized player.");
  }
}

void Game::initBricks() {
  int i, j;
  float start_y = 50.f; // UGLY!
  for (i = 0; i < kBrickDefaultRows; ++i) {
    for (j = 0; j < kBrickDefaultColumns; ++j) {
      bricks_[i][j].setActive(true);
      bricks_[i][j].setPosition(sf::Vector2f(bricks_[i][j].getSize().x * j, start_y));
      bricks_[i][j].setPlayer(&player_);
    }
    start_y = start_y + bricks_[i][j].getSize().y;
  }
}

bool Game::quit() {
  return quit_;
}

void Game::render() {
  window_.clear();
  if (in_title_screen_) {
    gui_.drawTitleScreen(window_);
  } else {
    if (paused_) {
      gui_.drawPauseScreen(window_);
    }
    gui_.drawInGameGUI(window_);
    ball_.draw(window_);
    ship_.draw(window_);
    drawBricks();
  }
  window_.display();
}

void Game::update() {
  float delta_time = clock_.restart().asSeconds();
  if(player_.isDead() && !in_title_screen_) {
    goToTitle();
  } 
  if (!paused_) {
    ball_.move(delta_time, ship_, bricks_);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
     || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      ship_.move(sf::Vector2f(delta_time * -kShipDefaultSpeed, 0.f));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
     || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      ship_.move(sf::Vector2f(delta_time * kShipDefaultSpeed, 0.f));
    }
  }
}