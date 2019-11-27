#include "game.h"

void Game::clean() {
  window_.close();
  logger_.write("Successfully closed window.");
}

GameStates Game::getGameState() {
  return state_;
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

void Game::handleEvents() {
  while (window_.pollEvent(event_)) {
    switch (event_.type) {
      case sf::Event::Closed:
        state_ = Quit;
        break;
      case sf::Event::KeyPressed:
        handleKeyEvents(event_);
        break;
    }
  }
}

void Game::handleKeyEvents(sf::Event key_event) {
  switch (state_) {
    case Title:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = Quit;
          break;
        case sf::Keyboard::Num1:
          player_.reset();
          ball_.reset();
          ship_.reset();
          gui_.reset();
          initBricks();
          state_ = Playing;
          break;
      }
      break;
    case Playing:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = Title;
          gui_.setRenderFlashingTextFlag(true);
          break;
        case sf::Keyboard::P:
        case sf::Keyboard::Pause:
        case sf::Keyboard::Space:
          state_ = Paused;
          gui_.setRenderFlashingTextFlag(true);
          break;
      }
      break;
    case Paused:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = Title;
          gui_.setRenderFlashingTextFlag(true);
          break;
        case sf::Keyboard::P:
        case sf::Keyboard::Pause:
        case sf::Keyboard::Space:
          state_ = Playing;
          gui_.setRenderFlashingTextFlag(true);
          break;
      }
      break;
    case GameOver:
      state_ = Title;
      gui_.setRenderFlashingTextFlag(true);
      break;
    case Quit:
      break;
  }
}

void Game::init() {
  state_ = Title;
  title_ = kAppName + " - v" + kAppVersion;
  logger_.start();
  logger_.write("Logger started.");
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
  float start_y = kBrickDefaultStart;
  for (i = 0; i < kBrickDefaultRows; ++i) {
    for (j = 0; j < kBrickDefaultColumns; ++j) {
      bricks_[i][j].setActive(true);
      bricks_[i][j].setPosition(sf::Vector2f(bricks_[i][j].getSize().x * j, start_y));
      bricks_[i][j].setPlayer(&player_);
    }
    start_y = start_y + bricks_[i][j].getSize().y;
  }
}

void Game::render() {
  window_.clear();
  switch (state_) {
    case Title:
      gui_.drawTitleScreen(window_);
      break;
    case Paused:
      gui_.drawPauseScreen(window_);
      [[fallthrough]];
    case Playing:
      gui_.drawInGameGUI(window_);
      ball_.draw(window_);
      ship_.draw(window_);
      drawBricks();
      break;
    case GameOver:
      gui_.drawGameOverScreen(window_);
      break;
    case Quit:
      break;
  }
  window_.display();
}

void Game::update() {
  float delta_time = clock_.restart().asSeconds();
  switch (state_) {
    case Title:
      break;
    case Playing:
      if (player_.isDead()) {
        gui_.setFinalScoreText();
        state_ = GameOver;
      } else {
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
      break;
    case Paused:
      break;
    case GameOver:
      break;
    case Quit:
      break;
  }
}