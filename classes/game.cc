#include "game.h"

void Game::clean() {
  window_.close();
  logger_.write("Successfully closed display window.");
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
        /* New game start */
        case sf::Keyboard::Num1:
          player_.reset();
          player_.resetVaus();
          ball_.reset();
          gui_.reset();
          if (loadLevel(1u)) {
            state_ = Playing;
            logger_.write("Successfully loaded level 1.");
          } else {
            logger_.write("ERROR: Failed loading level 1.");
          }
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
            state_ = Playing;
            logger_.write("Successfully loaded level " + GUI::toString(lvl_num) + ".");
          } else {
            logger_.write("ERROR: Failed loading level " + GUI::toString(lvl_num) + ".");
          }
          break;
      }
      break;
    case Playing:
      switch (key_event.key.code) {
        case sf::Keyboard::C:
          if (kExecutionMode != Normal) {
            current_level_->complete(); // cheat!
          }
          break;
        case sf::Keyboard::Escape:
        case sf::Keyboard::P:
        case sf::Keyboard::Pause:
          state_ = Paused;
          gui_.setRenderFlashingTextFlag(true);
          break;
      }
      break;
    case Paused:
      switch (key_event.key.code) {
        case sf::Keyboard::Q: /// @todo: press Q to exit
          state_ = Menu;
          break;
        default:
          state_ = Playing;
          break;
      }
      break;
    case LevelCompleted: {
      switch (key_event.key.code) {
        case sf::Keyboard::Escape:
          state_ = Menu;
          break;
        /* Next level */
        case sf::Keyboard::Space:
          const auto next_lvl = current_level_->getNumber() + 1u;
          if (next_lvl > kMaxLevels) {
            state_ = GameCompleted;
          } else  {
            ball_.reset();
            player_.resetVaus();
            if (loadLevel(next_lvl)) {
              state_ = Playing;
              logger_.write("Successfully loaded level " + GUI::toString(next_lvl) + ".");
              } else {
              logger_.write("ERROR: Failed loading level " + GUI::toString(next_lvl) + ".");
            }
          }
      }
      break;
    }
    case GameCompleted:
      // any key goes to main menu
      state_ = Menu;
      break;
    case GameOver:
      // any key goes to Menu
      state_ = Menu;
      break;
    case Quit:
      break;
  }
}

void Game::handlePowerUps() {
  const PowerUpTypes pwrup = current_level_->getCatchedPowerUp();
  current_level_->eraseCatchedPowerUp();
  if (ball_.isPowerUpActive() && pwrup != PowerUpTypes::Slow) ball_.deactivatePowerUp();
  if (current_level_->isPowerUpActive()) current_level_->deactivatePowerUp();
  if (player_.isPowerUpActive()) player_.deactivatePowerUp();
  // switch (PowerUpTypes::Catch) { /* QoL purposes */
  switch (pwrup) {
    case PowerUpTypes::Break:
      current_level_->setPowerUp(PowerUpTypes::Break);
      break;
    case PowerUpTypes::Catch:
      ball_.setPowerUp(PowerUpTypes::Catch);
      break;
    case PowerUpTypes::Disruption:
      ball_.setPowerUp(PowerUpTypes::Disruption);
      break;
    case PowerUpTypes::Enlarge:
      player_.setPowerUp(PowerUpTypes::Enlarge);
      break;
    case PowerUpTypes::Laser:
      current_level_->setPowerUp(PowerUpTypes::Laser);
      break;
    case PowerUpTypes::Player:
      player_.increaseLives();
      break;
    case PowerUpTypes::Slow:
      if (ball_.isPowerUpActive() && ball_.getPowerUp() != PowerUpTypes::Slow) ball_.deactivatePowerUp();
      ball_.setPowerUp(PowerUpTypes::Slow);
      break;
    case PowerUpTypes::Nil:
    default:
      printf("This SHOULDN'T be seen.\n");
      break;
  }
}
 
void Game::init() {
  state_ = Title;
  title_ = kAppName + " v" + kAppVersion;
  /* Logger */
  logger_.start();
  logger_.write(title_ + " started.");
  /* Display window */ 
  window_.create(sf::VideoMode(kScreenWidth, kScreenHeight), title_, sf::Style::Titlebar | sf::Style::Close);
  logger_.write("Successfully created display window.");
  window_.setVerticalSyncEnabled(true);
  /* Font */
  if (!font_.loadFromFile("assets/PressStart2P.ttf")) {
    logger_.write("ERROR: Failed loading font.");
    exit(EXIT_FAILURE);
  }
  /* Proto levels, graphics and level selection menu */
  current_level_ = NULL;
  Level::initProtoLevels(game_levels_);
  logger_.write("Successfully initialized protolevels.");
  Level::initGraphics();
  logger_.write("Successfully initialized levels' graphics.");
  initLevelsMenu();
  logger_.write("Successfully initialized levels menu.");
  /* GUI */
  gui_.init(font_);
  logger_.write("Successfully initialized GUI.");
  /* Ball */ 
  ball_.init(&player_);
  logger_.write("Successfully initialized ball.");
  /* Player */
  player_.linkGUI(&gui_);
  logger_.write("Successfully initialized player.");
}

void Game::initLevelsMenu() {
  for (auto i = 0u; i < kMaxLevels; ++i) {
    game_levels_[i].setNumber(i + 1u);
    gui_.setLevelInfo(i, game_levels_[i].getNumber(), game_levels_[i].getName());
  }
}

bool Game::loadLevel(unsigned int lvl_num) {
  bool found = false;
  for (auto i = 0u; i < kMaxLevels && !found; ++i) {
    if (game_levels_[i].getNumber() == lvl_num) {
      found = true;
      current_level_ = &game_levels_[i];
      current_level_->init(&player_);
      ball_.setLevel(current_level_);
      if (current_level_->getNumber() >= kMaxLevels) {
        gui_.update(current_level_->getNumber(), current_level_->getName());
      } else {
        gui_.update(current_level_->getNumber(), current_level_->getName(), game_levels_[i + 1u].getName());
      }
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
      current_level_->draw(window_);
      gui_.drawPauseScreen(window_);
      gui_.drawInGameGUI(window_);
      ball_.draw(window_, state_);
      player_.drawVaus(window_);
      break;
    case Playing:
      current_level_->draw(window_);
      gui_.drawInGameGUI(window_);
      ball_.draw(window_, state_);
      player_.drawVaus(window_);
      break;
    case LevelCompleted:
      current_level_->draw(window_);
      gui_.drawLevelCompletedScreen(window_);
      break;
    case GameCompleted:
      gui_.drawGameCompleted(window_);
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
  const float delta_time = clock_.restart().asSeconds();
  switch (state_) {
    case Playing:
      if (player_.isDead()) {
        state_ = GameOver;
        gui_.setRenderFlashingTextFlag(true);
        gui_.setFinalScoreText(player_.getScore());
      } else if (current_level_->isCompleted()) {
        state_ = LevelCompleted;
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
          const bool crash = !player_.moveVaus(sf::Vector2f(delta_time * player_.getVausSpeed(), 0.f));
          if (crash && current_level_->isBreakActive()) current_level_->complete();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          /* Laser firing */
          if (current_level_->isLaserActive()) current_level_->fireLaser();
          /* Release the ball from the Vaus */
          if (ball_.isCatched()) ball_.release();
        }
        /* Catch new power-ups */
        if (current_level_->catchedPowerUp()) handlePowerUps();
        /* Ball stuff */
        if (ball_.isPowerUpActive()) ball_.updatePowerUps();
        if (ball_.isCatched()) {
          ball_.followVaus(player_.getVaus());
        } else {
          ball_.move(delta_time, player_.getVaus(), current_level_->getBricks());
        }
        /* Level */
        current_level_->update(delta_time);
      }
      break;
  }
}