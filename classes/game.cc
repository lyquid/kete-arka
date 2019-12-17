#include "game.h"

void Game::clean() {
  window_.close();
  logger_.write("Successfully closed display window.");
}

GameStates Game::getGameState() {
  return state_;
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

void Game::handleKeyEvents(const sf::Event key_event) {
  switch (state_) {
    case Title:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = Quit;
          break;
        default:
          state_ = Menu;
          break;
      }
      break;
    case Menu:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
          state_ = Quit;
          break;
        case sf::Keyboard::Num1:
          state_ = Playing;
          player_.reset();
          ball_.reset();
          ship_.reset();
          gui_.reset();
          loadLevel(1) ? logger_.write("Successfully loaded level 1.")
                       : logger_.write("ERROR: Failed loading level number 1.");
          break;
        case sf::Keyboard::Num2:
          state_ = LevelSelection;
      }
      break;
    case LevelSelection:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
          state_ = Menu;
          break;
      }
      break;
    case Playing:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = Menu;
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
        case sf::Keyboard::Q:
          state_ = Menu;
          break;
        case sf::Keyboard::P:
        case sf::Keyboard::Pause:
        case sf::Keyboard::Space:
          state_ = Playing;
          break;
      }
      break;
    case GameOver:
      state_ = Menu;
      break;
    case Quit:
      break;
  }
}

void Game::init() {
  state_ = Title;
  logger_.start();
  title_ = kAppName + " v" + kAppVersion;
  logger_.write(title_ + " started.");
  window_.create(sf::VideoMode(kScreenWidth, kScreenHeight, 32), title_, sf::Style::Titlebar | sf::Style::Close);
  logger_.write("Successfully created display window.");
  window_.setVerticalSyncEnabled(true);
  if (!font_.loadFromFile("assets/PressStart2P.ttf")) {
    logger_.write("ERROR: Failed loading font.");
    exit(EXIT_FAILURE);
  } else {
    current_level_ = NULL;
    initLevelsMenu();
    logger_.write("Successfully initialized levels menu.");
    gui_.init(font_);
    logger_.write("Successfully initialized GUI.");
    ball_.init(&player_, &ship_);
    logger_.write("Successfully initialized ball.");
    player_.init(&gui_);
    logger_.write("Successfully initialized player.");
  }
}

void Game::initLevelsMenu() {
  for (int i = 0; i < kTotalLevels; ++i) {
    game_levels_[i].setLevelNumber(i + 1);
    game_levels_[i].setLevelName("prueba_lvl_" + toString(game_levels_[i].getLevelNumber()));
    if (game_levels_[i].getLevelNumber() < 10) {
      gui_.setLevelStrings(i, "0" + toString(game_levels_[i].getLevelNumber()) + " - " + game_levels_[i].getLevelName());
    } else {
      gui_.setLevelStrings(i, toString(game_levels_[i].getLevelNumber()) + " - " + game_levels_[i].getLevelName());
    }
  }
}

bool Game::loadLevel(const int num_lvl) {
  bool found = false;
  for (int i = 0; i < kTotalLevels && !found; ++i) {
    if (game_levels_[i].getLevelNumber() == num_lvl) {
      found = true;
      current_level_ = &game_levels_[i];
      current_level_->init(&player_);
    }
  }
  return found;
}

void Game::render() {
  window_.clear();
  switch (state_) {
    case Title:
      gui_.drawTitleScreen(window_);
      break;
    case Menu:
      gui_.drawMenu(window_);
      break;
    case LevelSelection:
      gui_.drawLevelSelection(window_);
      break;
    case Paused:
      gui_.drawPauseScreen(window_);
      [[fallthrough]];
    case Playing:
      gui_.drawInGameGUI(window_);
      ball_.draw(window_, state_);
      ship_.draw(window_);
      current_level_->draw(window_);
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
    case Playing:
      if (player_.isDead()) {
        state_ = GameOver;
        gui_.setRenderFlashingTextFlag(true);
        gui_.setFinalScoreText();
      } else {
        ball_.move(delta_time, ship_, current_level_->getBricks());
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
  }
}