#include "ball.h"

/* Ball default settings */
const sf::Vector2f Ball::kBallDefaultPosition_ = sf::Vector2f(k::kScreenWidth / 2.f, k::kScreenHeight * 0.75f);
const sf::Color    Ball::kBallDefaultColor_ = sf::Color::White;
/* Disruption power-up */
const unsigned int           Ball::kDisruptionMaxBalls_ = 3u;
std::vector<Ball::BallShape> Ball::balls_(kDisruptionMaxBalls_);
unsigned int                 Ball::active_balls_;
/* Catch power-up */
const float Ball::kCatchMinTime_ = 1.50f;
const float Ball::kCatchMaxTime_ = 3.00f;
sf::Clock   Ball::catch_clk_;
float       Ball::time_to_release_;
bool        Ball::catched_;
float       Ball::offset_;

void Ball::activateDisruption() {
  unsigned int current_ball;
  for (auto i = 0u; i < kDisruptionMaxBalls_; ++i) {
    if (balls_[i].active) {
      current_ball = i;
    } else {
      ++active_balls_;
      balls_[i].active = true;
      randomizeBounceAngle(balls_[i], Collisions::TopShip);
    }
  }
  for (auto i = 0u; i < kDisruptionMaxBalls_; ++i) {
    if (i != current_ball) {
      balls_[i].last_position = balls_[current_ball].shape.getPosition();
      balls_[i].shape.setPosition(balls_[current_ball].shape.getPosition());
    }
  }
}

bool Ball::checkBrickCollision(BallShape& ball, k::Brick bricks[][k::kLevelMaxColumns]) {
  bool collision = false;
  for (auto i = 0u; i < k::kLevelMaxRows; ++i) {
    for (auto j = 0u; j < k::kLevelMaxColumns; ++j) {
      if (bricks[i][j].active && bricks[i][j].shape.getGlobalBounds().intersects(ball.shape.getGlobalBounds())) {
        const auto current_radius = ball.shape.getRadius();
        const auto ball_x = ball.shape.getPosition().x;
        const auto ball_y = ball.shape.getPosition().y;
        const auto brick_x = bricks[i][j].shape.getPosition().x;
        const auto brick_y = bricks[i][j].shape.getPosition().y;
        const auto brick_x_size = bricks[i][j].shape.getSize().x;
        const auto brick_y_size = bricks[i][j].shape.getSize().y;
        collision = true;
        level_->decreaseResistance({i, j});
        if (ball.last_position.x < brick_x) {
          // left hit
          randomizeBounceAngle(ball, Collisions::LeftBrick);
          ball.shape.setPosition(brick_x - current_radius - 1.f, ball_y);
        } else if (ball.last_position.x > brick_x + brick_x_size) {
          // right hit
          randomizeBounceAngle(ball, Collisions::RightBrick);
          ball.shape.setPosition(brick_x + brick_x_size + current_radius + 1.f, ball_y);
        } else if (ball.last_position.y < brick_y) {
          // top hit
          randomizeBounceAngle(ball, Collisions::TopBrick);
          ball.shape.setPosition(ball_x, brick_y - current_radius - 1.f);
        } else {
          // bottom hit
          randomizeBounceAngle(ball, Collisions::BottomBrick);
          ball.shape.setPosition(ball_x, brick_y + brick_y_size + current_radius + 1.f);
        }
      }
    }
  }
  return collision;
}

bool Ball::checkBorderCollision(BallShape& ball) {
  const auto current_radius = ball.shape.getRadius();
  bool collision = false;
  // left collision
  if (ball.shape.getPosition().x - current_radius <= k::kGUIBorderThickness) {
    randomizeBounceAngle(ball, Collisions::Left);
    ball.shape.setPosition(k::kGUIBorderThickness + current_radius + 0.1f, ball.shape.getPosition().y);
    collision = true;
  // right collision
  } else if (ball.shape.getPosition().x + current_radius >= k::kScreenWidth - k::kGUIBorderThickness) {
    randomizeBounceAngle(ball, Collisions::Right);
    ball.shape.setPosition(k::kScreenWidth - k::kGUIBorderThickness - current_radius - 0.1f, ball.shape.getPosition().y); 
    collision = true;
  // top collision
  } else if (ball.shape.getPosition().y - current_radius <= k::kGUIBorderThickness) {
    randomizeBounceAngle(ball, Collisions::Top);
    ball.shape.setPosition(ball.shape.getPosition().x, current_radius + k::kGUIBorderThickness + 0.1f);
    collision = true;
  // bottom "collision"
  } else if (ball.shape.getPosition().y + current_radius >= k::kScreenHeight) {
    ball.active = false;
    --active_balls_;
    if (!active_balls_ ) {
      player_->decreaseLives();
      player_->resetVaus();
      if (player_->isPowerUpActive()) player_->deactivatePowerUp();
      if (level_->isPowerUpActive()) level_->deactivatePowerUp();
      if (isPowerUpActive()) deactivatePowerUp();
      reset();
    }
  }
  return collision;
}

bool Ball::checkVausCollision(BallShape& ball, const k::Vaus& vaus) {
  bool collision = false;
  if (vaus.collision_rect.getGlobalBounds().intersects(ball.shape.getGlobalBounds())) {
    const auto current_radius = ball.shape.getRadius();
    const auto ball_x = ball.shape.getPosition().x;
    const auto ball_y = ball.shape.getPosition().y;
    const auto vaus_x = vaus.collision_rect.getPosition().x;
    const auto vaus_y = vaus.collision_rect.getPosition().y;
    const auto vaus_x_size = vaus.collision_rect.getSize().x;
    collision = true;
    if (ball.last_position.x < vaus_x) {
      /* left hit */
      randomizeBounceAngle(ball, Collisions::LeftShip);
      ball.shape.setPosition(vaus_x - current_radius - 0.1f, ball_y);
    } else if (ball.last_position.x > vaus_x + vaus_x_size) {
      /* right hit */
      randomizeBounceAngle(ball, Collisions::RightShip);
      ball.shape.setPosition(vaus_x + vaus_x_size + current_radius + 0.1f, ball_y);
    } else {
      /* front/rear hit (rear hit should be imposible!) */
      randomizeBounceAngle(ball, Collisions::TopShip);
      if (pwrup_type_ == k::PowerUpTypes::Catch) {
        catched_ = true;
        time_to_release_ = generateRandomTime(kCatchMinTime_, kCatchMaxTime_);
        offset_ = ball_x - vaus_x;
        catch_clk_.restart();
      }
      ball.shape.setPosition(ball_x, vaus_y - current_radius - 0.1f);
    }
  }
  return collision;
}

void Ball::deactivatePowerUp() {
  switch (pwrup_type_) {
    case k::PowerUpTypes::Catch:
      catched_ = false;
      break;
    case k::PowerUpTypes::Disruption:
      level_->setDisruptionStatus(false);
      break;
    case k::PowerUpTypes::Slow:
      speed_ = kBallDefaultSpeed_;
      break;
    case k::PowerUpTypes::Nil:
    case k::PowerUpTypes::Break:
    case k::PowerUpTypes::Enlarge:
    case k::PowerUpTypes::Laser:  
    case k::PowerUpTypes::Player:
    default:
      // print something horrible to the logger
      break;
  }
  pwrup_type_ = k::PowerUpTypes::Nil;
  pwrup_active_ = false;
}

void Ball::draw(sf::RenderWindow& window, k::GameStates state) {
  if (!moving_flag_) {
    if (state == k::GameStates::Playing) {
      updateFlashFlag();
    }
    if (ball_flash_flag_) {
      window.draw(balls_.front().shape);
    }
  } else {
    for (const auto& ball: balls_) {
      if (ball.active) window.draw(ball.shape); 
    }
  }
}

void Ball::followVaus(const k::Vaus& vaus) {
  for (auto& ball: balls_) {
    if (ball.active) {
      ball.shape.setPosition(vaus.shape.getPosition().x + offset_ , ball.shape.getPosition().y);
      return;
    }
  }
}

float Ball::generateRandomTime(float min, float max) {
  const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<float> distribution(min, max);
  return distribution(generator);
}

void Ball::init(Player* ptp) {
  player_ = ptp;
  reset();
}

void Ball::invertHorizontalDirection(BallShape& ball, float variation) {
  ball.direction.x = -ball.direction.x + variation;
}

void Ball::invertVerticalDirection(BallShape& ball, float variation) {
  ball.direction.y = -ball.direction.y + variation;
}

void Ball::move(float delta_time, const k::Vaus& vaus, k::Brick bricks[][k::kLevelMaxColumns]) {
  // bool collision = false;
  if (moving_flag_) {
    for (auto& ball: balls_) {
      if (ball.active) {
        const auto factor = speed_ * delta_time;
        ball.last_position = ball.shape.getPosition();
        /* This simple checking sometimes makes the ball to go through some bricks. Especially golden bricks. */
        if (checkBrickCollision(ball, bricks) && pwrup_type_ == k::PowerUpTypes::Slow) speedUp();
        if (checkBorderCollision(ball) && pwrup_type_ == k::PowerUpTypes::Slow) speedUp();
        if (checkVausCollision(ball, vaus) && pwrup_type_ == k::PowerUpTypes::Slow) speedUp();

        /* This "do while" method sometimes gets stuck infinitely. */
        /* do { } while (checkBrickCollision(bricks));
        do { } while (checkBorderCollision());
        do { } while (checkShipCollision(ship)); */

        /* This also gets stuck to infinity. */
        /* do {
          collision = checkBrickCollision(bricks) || checkBorderCollision() || checkShipCollision(ship);
        } while (collision == true); */
        if (!catched_) ball.shape.move(ball.direction.x * factor, ball.direction.y * factor);
      }
    }
  } else if (start_clock_.getElapsedTime().asSeconds() > 1.5f) {
    moving_flag_ = true;
  }
}

void Ball::randomizeBounceAngle(BallShape& ball, Collisions collision) {
  float displ = 0.f;
  std::string collision_with = "";
  float random_angle_variation = (std::rand() % 21 - 10) / 100.f;  // rnd -0.10 to 0.10
  switch(collision) {
    case Collisions::BottomBrick:
      collision_with = "BB";
      [[fallthrough]];
    case Collisions::BottomShip:
      if (collision_with == "") { collision_with = "BS"; }
      [[fallthrough]];
    case Collisions::Top:
      if (collision_with == "") { collision_with = "T"; }
      invertVerticalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement_) {
        ball.direction.y = kBallDefaultDisplacement_ - std::abs(ball.direction.x);
        random_angle_variation = 0.f;
      }
      if (ball.direction.x < 0.f) {
        ball.direction.x = ball.direction.x + random_angle_variation;
      } else {
        ball.direction.x = ball.direction.x - random_angle_variation;
      }
      break;
    case Collisions::TopBrick:
      collision_with = "TB";
      [[fallthrough]];
    case Collisions::TopShip:
      if (collision_with == "") { collision_with = "TS"; }
      [[fallthrough]];
    case Collisions::Bottom:
      if (collision_with == "") { collision_with = "B"; }
      invertVerticalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement_) {
        ball.direction.y = -kBallDefaultDisplacement_ + std::abs(ball.direction.x);
        random_angle_variation = 0.f;
      }
      if (ball.direction.x < 0.f) {
        ball.direction.x = ball.direction.x - random_angle_variation;
      } else {
        ball.direction.x = ball.direction.x + random_angle_variation;
      }
      break;
    case Collisions::RightBrick:
      collision_with = "RB";
      [[fallthrough]];
    case Collisions::RightShip:
      if (collision_with == "") { collision_with = "RS"; }
      [[fallthrough]];
    case Collisions::Left:
      if (collision_with == "") { collision_with ="L"; }
      invertHorizontalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement_) {
        ball.direction.x = kBallDefaultDisplacement_ - std::abs(ball.direction.y);
        random_angle_variation = 0.f;
      }
      if (ball.direction.y < 0.f) {
        ball.direction.y = ball.direction.y + random_angle_variation;
      } else {
        ball.direction.y = ball.direction.y - random_angle_variation;
      }
      break;
    case Collisions::LeftBrick:
      collision_with = "LB";
      [[fallthrough]];
    case Collisions::LeftShip:
      if (collision_with == "") { collision_with = "LS"; }
      [[fallthrough]];
    case Collisions::Right:
      if (collision_with == "") { collision_with = "R"; }
      invertHorizontalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement_) {
        ball.direction.x = -kBallDefaultDisplacement_ + std::abs(ball.direction.y);
        random_angle_variation = 0.f;
      }
      if (ball.direction.y < 0.f) {
        ball.direction.y = ball.direction.y - random_angle_variation;
      } else {
        ball.direction.y = ball.direction.y + random_angle_variation;
      }
      break;
  }
  displ = sumAbs(ball.direction.x, ball.direction.y);
  switch (k::kExecutionMode) {
    case k::ExecutionModes::Normal:
      // do nothing
      break;
    case k::ExecutionModes::LogFile:
      // logs to the log file and then fallthrough to Debug case
      Logger::write("(" + collision_with + ")"
                  + "\tx = " + std::to_string(ball.direction.x)
                  + "\ty = " + std::to_string(ball.direction.y)
                  + "\trnd = " + std::to_string(random_angle_variation)
                  + "\tdsp = " + std::to_string(displ));
      [[fallthrough]];
    case k::ExecutionModes::Debug:
      // logs to console
      std::cout.precision(3);
      std::cout << "(" << collision_with << ")";
      std::cout << "\tx = " << std::fixed << ball.direction.x;
      std::cout << "\ty = " << std::fixed << ball.direction.y;
      std::cout << "\trnd = " << std::fixed << random_angle_variation;
      std::cout << "\tdsp = " << std::fixed << displ << "\n";
      break;
  }
}

void Ball::reset() {
  active_balls_ = 1u;
  /* Ball direction_ vector randomization */
  float random_x_direction = 0.f;
  do {  /* Get a number between -10 and 10, not including 0. */
    random_x_direction = std::rand() % 21 - 10;
  } while (random_x_direction == 0.f);
  /* Take the random number and divide it to make it between -0.10, -0.09, -0.08, ... to 0.10 */
  random_x_direction = random_x_direction / 100.f;
  /* Ball's vector full initialization */
  for (auto& ball: balls_) {
    ball.active = false;
    ball.shape.setRadius(kBallDefaultRadius_);
    ball.shape.setFillColor(kBallDefaultColor_);
    ball.shape.setOrigin(kBallDefaultRadius_, kBallDefaultRadius_);
    ball.shape.setPosition(kBallDefaultPosition_);
    /* We use this displacement to make sure speed is always the same regarding angle */
    ball.direction = sf::Vector2f(random_x_direction, kBallDefaultDisplacement_ - std::abs(random_x_direction));
    ball.last_position = ball.shape.getPosition();
  }
  balls_.front().active = true;
  /* Ball's speed_ initialization */
  speed_ = kBallDefaultSpeed_;
  /* Ball start and flash clocks */
  start_clock_.restart();
  flash_clock_.restart();
  ball_flash_flag_ = true;
  moving_flag_ = false;
  /* Power-ups */
  pwrup_active_ = false;
  pwrup_type_ = k::PowerUpTypes::Nil;
  /* Catch power-up */
  catched_ = false;
}

void Ball::setPowerUp(k::PowerUpTypes type) {
  pwrup_type_ = type;
  pwrup_active_ = true;
  switch (type) {
    case k::PowerUpTypes::Catch:
      break;
    case k::PowerUpTypes::Disruption:
      level_->setDisruptionStatus(true);
      activateDisruption();
      break;
    case k::PowerUpTypes::Slow:
      slowPowerUp();
      break;
    case k::PowerUpTypes::Nil:
    case k::PowerUpTypes::Break:
    case k::PowerUpTypes::Enlarge:
    case k::PowerUpTypes::Laser:  
    case k::PowerUpTypes::Player:
    default:
      // print something horrible to the logger
      break;
  }
}

void Ball::slowPowerUp() {
  const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<float> distribution(10.0f, 30.0f);
  slow_timer_ = distribution(generator);
  const float kDecrement = 2.f;
  speed_ /= kDecrement;
  slow_clk_.restart();
}

void Ball::speedUp() {
  const float kIncrement = 10.f;
  if (speed_ + kIncrement >= kBallDefaultSpeed_) deactivatePowerUp();
  else speed_ += kIncrement;
}

float Ball::sumAbs(float num1, float num2) {
  return std::abs(num1) + std::abs(num2);
}

void Ball::updateFlashFlag() {
  if (flash_clock_.getElapsedTime().asSeconds() > 0.15f) {
    ball_flash_flag_ = !ball_flash_flag_;
    flash_clock_.restart();
  }
}

void Ball::updatePowerUps() {
  switch (pwrup_type_) {
    case k::PowerUpTypes::Catch:
      if (catch_clk_.getElapsedTime().asSeconds() >= time_to_release_) catched_ = false;
      break;
    case k::PowerUpTypes::Disruption:
      if (active_balls_ == 1u) deactivatePowerUp();
      break;
    case k::PowerUpTypes::Slow:
      if (slow_clk_.getElapsedTime().asSeconds() >= slow_timer_) deactivatePowerUp();
      break;
    case k::PowerUpTypes::Nil:
    case k::PowerUpTypes::Break:
    case k::PowerUpTypes::Enlarge:
    case k::PowerUpTypes::Laser:  
    case k::PowerUpTypes::Player:
    default:
      // print something horrible to the logger
      break;
  }
}
