#include "game.h"

void Game::clean() {
  window_.close();
  logger_.write("Successfully closed display window.");
}

void Game::handleEvents() {
  while (window_.pollEvent(event_)) {
    switch (event_.type) {
      case sf::Event::Closed:
        state_ = k::GameStates::Quit;
        break;
      case sf::Event::KeyPressed:
        handleKeyEvents(event_);
        break;
    }
  }
}

void Game::handleKeyEvents(const sf::Event& key_event) {
  switch (state_) {
    case k::GameStates::Title:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = k::GameStates::Quit;
          break;
        default:
          state_ = k::GameStates::Menu;
          break;
      }
      break;
    case k::GameStates::Menu:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
          state_ = k::GameStates::Quit;
          break;
        /* New game start */
        case sf::Keyboard::Num1:
          player_.reset();
          player_.resetVaus();
          ball_.reset();
          gui_.reset();
          if (loadLevel(1u)) {
            state_ = k::GameStates::Playing;
            logger_.write("Successfully loaded level 1.");
          } else {
            logger_.write("ERROR: Failed loading level 1.");
          }
          break;
        case sf::Keyboard::Num2:
          state_ = k::GameStates::LevelSelection;
      }
      break;
    case k::GameStates::LevelSelection:
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
          state_ = k::GameStates::Menu;
          break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
          gui_.selectPreviousLevel();
          break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
          gui_.selectNextLevel();
          break;
        /* Level selection start */
        case sf::Keyboard::Enter:
        case sf::Keyboard::Space:
          const auto lvl_num = gui_.getLevelSelectedNumber();
          player_.reset();
          player_.resetVaus();
          ball_.reset();
          gui_.reset();
          if (loadLevel(lvl_num)) {
            state_ = k::GameStates::Playing;
            logger_.write("Successfully loaded level " + std::to_string(lvl_num) + ".");
          } else {
            logger_.write("ERROR: Failed loading level " + std::to_string(lvl_num) + ".");
          }
          break;
      }
      break;
    case k::GameStates::Playing:
      switch (key_event.key.code) {
        case sf::Keyboard::C:
          if (k::kExecutionMode != k::ExecutionModes::Normal) {
            level_->complete(); // cheat!
          }
          break;
        case sf::Keyboard::V:
          if (k::kExecutionMode != k::ExecutionModes::Normal) {
            player_.toggleCollisionRect();
          }
          break;
        case sf::Keyboard::Escape:
        case sf::Keyboard::P:
        case sf::Keyboard::Pause:
          state_ = k::GameStates::Paused;
          gui_.setRenderFlashingTextFlag(true);
          break;
      }
      break;
    case k::GameStates::Paused:
      switch (key_event.key.code) {
        case sf::Keyboard::Q: /// @todo: press Q to exit
          state_ = k::GameStates::Menu;
          break;
        default:
          state_ = k::GameStates::Playing;
          break;
      }
      break;
    case k::GameStates::LevelCompleted: {
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = k::GameStates::Menu;
          break;
        /* Next level */
        case sf::Keyboard::Space:
          const auto next_lvl = level_->getNumber() + 1u;
          if (next_lvl > k::kMaxLevels) {
            state_ = k::GameStates::GameCompleted;
          } else  {
            ball_.reset();
            player_.resetVaus();
            if (loadLevel(next_lvl)) {
              state_ = k::GameStates::Playing;
              logger_.write("Successfully loaded level " + std::to_string(next_lvl) + ".");
              } else {
              logger_.write("ERROR: Failed loading level " + std::to_string(next_lvl) + ".");
            }
          }
      }
      break;
    }
    case k::GameStates::GameCompleted:
      // any key goes to main menu
      state_ = k::GameStates::Menu;
      break;
    case k::GameStates::GameOver:
      // any key goes to Menu
      state_ = k::GameStates::Menu;
      break;
    case k::GameStates::Quit:
      break;
  }
}

void Game::handlePowerUps() {
  const k::PowerUpTypes pwrup = level_->getCatchedPowerUp();
  level_->eraseCatchedPowerUp();
  if (ball_.isPowerUpActive() && pwrup != k::PowerUpTypes::Slow) ball_.deactivatePowerUp();
  if (level_->isPowerUpActive()) level_->deactivatePowerUp();
  if (player_.isPowerUpActive()) player_.deactivatePowerUp();
  // switch (k::PowerUpTypes::Laser) { /* QoL purposes */
  switch (pwrup) {
    case k::PowerUpTypes::Break:
      level_->setPowerUp(k::PowerUpTypes::Break);
      break;
    case k::PowerUpTypes::Catch:
      ball_.setPowerUp(k::PowerUpTypes::Catch);
      break;
    case k::PowerUpTypes::Disruption:
      ball_.setPowerUp(k::PowerUpTypes::Disruption);
      break;
    case k::PowerUpTypes::Enlarge:
      player_.setPowerUp(k::PowerUpTypes::Enlarge);
      break;
    case k::PowerUpTypes::Laser:
      level_->setPowerUp(k::PowerUpTypes::Laser);
      player_.setPowerUp(k::PowerUpTypes::Laser);
      break;
    case k::PowerUpTypes::Player:
      player_.increaseLives();
      break;
    case k::PowerUpTypes::Slow:
      if (ball_.isPowerUpActive() && ball_.getPowerUp() != k::PowerUpTypes::Slow) ball_.deactivatePowerUp();
      ball_.setPowerUp(k::PowerUpTypes::Slow);
      break;
    case k::PowerUpTypes::Nil:
    default:
      printf("This SHOULDN'T be seen.\n");
      break;
  }
}

Game::Game():
  level_(nullptr),
  state_(k::GameStates::Title) {
    title_ = k::kAppName + std::string(" v") + k::kAppVersion;
    /* Logger */
    logger_.write(title_ + " started.");
    /* Display window */ 
    window_.create(sf::VideoMode(k::kScreenWidth, k::kScreenHeight), title_, sf::Style::Titlebar | sf::Style::Close);
    logger_.write("Successfully created display window.");
    window_.setVerticalSyncEnabled(true);
    /* Levels */
    levels_.resize(k::kMaxLevels);
    Level::setLevels(levels_);
    /* Graphics and level selection menu */
    Level::initGraphics();
    logger_.write("Successfully initialized levels' graphics.");
    initLevelsMenu();
    logger_.write("Successfully initialized levels menu.");
    /* GUI */
    gui_.init();
    logger_.write("Successfully initialized GUI.");
    /* Ball */ 
    ball_.init(&player_);
    logger_.write("Successfully initialized ball.");
    /* Player */
    player_.linkGUI(&gui_);
    logger_.write("Successfully initialized player.");
}

void Game::initLevelsMenu() {
  for (const auto& level: levels_)
    gui_.setLevelInfo(level.getNumber() - 1u, level.getNumber(), level.getName());
}

bool Game::loadLevel(unsigned int lvl_num) {
  for (auto it = levels_.begin(); it != levels_.end(); ++it) {
    if (it->getNumber() == lvl_num) {
      level_ = it;
      level_->init(&player_);
      ball_.setLevel(level_.base());
      if (level_->getNumber() == k::kMaxLevels) {
        gui_.update(level_->getNumber(), level_->getName());
      } else {
        gui_.update(level_->getNumber(), level_->getName(), std::next(it)->getName());
      }
      return true;
    }
  }
  return false;
}

void Game::render() {
  window_.clear();
  switch (state_) {
    case k::GameStates::Title:
      gui_.drawTitleScreen(window_);
      break;
    case k::GameStates::Menu:
      gui_.drawMenu(window_);
      break;
    case k::GameStates::LevelSelection:
      gui_.drawLevelSelection(window_);
      break;
    case k::GameStates::Paused:
      level_->draw(window_);
      gui_.drawPauseScreen(window_);
      gui_.drawInGameGUI(window_);
      ball_.draw(window_, state_);
      player_.drawVaus(window_);
      level_->drawBorders(window_);
      break;
    case k::GameStates::Playing:
      level_->draw(window_);
      gui_.drawInGameGUI(window_);
      ball_.draw(window_, state_);
      player_.drawVaus(window_);
      level_->drawBorders(window_);
      break;
    case k::GameStates::LevelCompleted:
      level_->draw(window_);
      level_->drawBorders(window_);
      gui_.drawLevelCompletedScreen(window_);
      break;
    case k::GameStates::GameCompleted:
      gui_.drawGameCompleted(window_);
      break;
    case k::GameStates::GameOver:
      gui_.drawGameOverScreen(window_);
      break;
    case k::GameStates::Quit:
      break;
  }
  window_.display();
}

void Game::update() {
  const float delta_time = clock_.restart().asSeconds();
  switch (state_) {
    case k::GameStates::Playing:
      if (player_.isDead()) {
        state_ = k::GameStates::GameOver;
        gui_.setRenderFlashingTextFlag(true);
        gui_.setFinalScoreText(player_.getScore());
      } else if (level_->isCompleted()) {
        state_ = k::GameStates::LevelCompleted;
        gui_.setRenderFlashingTextFlag(true);
        gui_.setFinalScoreText(player_.getScore());
      } else {
        if (player_.isVausResizing()) player_.resizeVaus();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
         || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
          player_.moveVaus(sf::Vector2f(delta_time * -player_.getVausSpeed(), 0.f));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
         || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
          const bool crash = player_.moveVaus(sf::Vector2f(delta_time * player_.getVausSpeed(), 0.f));
          if (crash && level_->isBreakActive()) level_->complete();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          /* Laser firing */
          if (level_->isLaserActive()) level_->fireLaser();
          /* Release the ball from the Vaus */
          if (ball_.isCatched()) ball_.release();
        }
        /* Catch new power-ups */
        if (level_->catchedPowerUp()) handlePowerUps();
        /* Ball stuff */
        if (ball_.isPowerUpActive()) ball_.updatePowerUps();
        if (ball_.isCatched()) {
          ball_.followVaus(player_.getVaus());
        } else {
          ball_.move(delta_time, player_.getVaus(), level_->getBricks());
        }
        /* Level */
        level_->update(delta_time);
        /* Vaus animation */
        player_.updateVausAnim();
      }
      break;
    default:
      break;
  }
}