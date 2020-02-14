#include "ball.h"

const unsigned int Ball::kDisruptionMaxBalls_ = 3u;
std::vector<BallShape> Ball::balls_(kDisruptionMaxBalls_);
unsigned int Ball::active_balls_;

void Ball::activateDisruption() {
  unsigned int current_ball;
  for (auto i = 0u; i < kDisruptionMaxBalls_; ++i) {
    if (balls_[i].active) {
      current_ball = i;
    } else {
      ++active_balls_;
      balls_[i].active = true;
      randomizeBounceAngle(balls_[i], TopShip);
    }
  }
  for (auto i = 0u; i < kDisruptionMaxBalls_; ++i) {
    if (i != current_ball) {
      balls_[i].last_position = balls_[current_ball].shape.getPosition();
      balls_[i].shape.setPosition(balls_[current_ball].shape.getPosition());
    }
  }
}

bool Ball::checkBrickCollision(BallShape& ball, Brick bricks[][kLevelMaxColumns]) {
  bool collision = false;
  for (auto i = 0u; i < kLevelMaxRows; ++i) {
    for (auto j = 0u; j < kLevelMaxColumns; ++j) {
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
          randomizeBounceAngle(ball, LeftBrick);
          ball.shape.setPosition(brick_x - current_radius - 1.f, ball_y);
        } else if (ball.last_position.x > brick_x + brick_x_size) {
          // right hit
          randomizeBounceAngle(ball, RightBrick);
          ball.shape.setPosition(brick_x + brick_x_size + current_radius + 1.f, ball_y);
        } else if (ball.last_position.y < brick_y) {
          // top hit
          randomizeBounceAngle(ball, TopBrick);
          ball.shape.setPosition(ball_x, brick_y - current_radius - 1.f);
        } else {
          // bottom hit
          randomizeBounceAngle(ball, BottomBrick);
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
  if (ball.shape.getPosition().x - current_radius <= kGUIBorderThickness) {
    randomizeBounceAngle(ball, Left);
    ball.shape.setPosition(kGUIBorderThickness + current_radius + 0.1f, ball.shape.getPosition().y);
    collision = true;
  // right collision
  } else if (ball.shape.getPosition().x + current_radius >= kScreenWidth - kGUIBorderThickness) {
    randomizeBounceAngle(ball, Right);
    ball.shape.setPosition(kScreenWidth - kGUIBorderThickness - current_radius - 0.1f, ball.shape.getPosition().y); 
    collision = true;
  // top collision
  } else if (ball.shape.getPosition().y - current_radius <= kGUIBorderThickness) {
    randomizeBounceAngle(ball, Top);
    ball.shape.setPosition(ball.shape.getPosition().x, current_radius + kGUIBorderThickness + 0.1f);
    collision = true;
  // bottom "collision"
  } else if (ball.shape.getPosition().y + current_radius >= kScreenHeight) {
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

bool Ball::checkVausCollision(BallShape& ball, const Vaus& vaus) {
  bool collision = false;
  if (vaus.shape.getGlobalBounds().intersects(ball.shape.getGlobalBounds())) {
    const auto current_radius = ball.shape.getRadius();
    const auto ball_x = ball.shape.getPosition().x;
    const auto ball_y = ball.shape.getPosition().y;
    const auto vaus_x = vaus.shape.getPosition().x;
    const auto vaus_y = vaus.shape.getPosition().y;
    const auto vaus_x_size = vaus.shape.getSize().x;
    collision = true;
    if (ball.last_position.x < vaus_x) {
      // left hit
      randomizeBounceAngle(ball, LeftShip);
      ball.shape.setPosition(vaus_x - current_radius - 0.1f, ball_y);
    } else if (ball.last_position.x > vaus_x + vaus_x_size) {
      // right hit
      randomizeBounceAngle(ball, RightShip);
      ball.shape.setPosition(vaus_x + vaus_x_size + current_radius + 0.1f, ball_y);
    } else {
      // front/rear hit (rear hit should be imposible!)
      randomizeBounceAngle(ball, TopShip);
      ball.shape.setPosition(ball_x, vaus_y - current_radius - 0.1f);
    }
  }
  return collision;
}

void Ball::deactivatePowerUp() {
  switch (pwrup_type_) {
    case PowerUpTypes::Catch:
      printf("todoooooooooooooooooooooo\n");
      break;
    case PowerUpTypes::Disruption:
      pwrup_type_ = PowerUpTypes::Nil;
      pwrup_active_ = false;
      level_->setDisruptionStatus(false);
      break;
    case PowerUpTypes::Slow:
      speed_ = kBallDefaultSpeed;
      pwrup_type_ = PowerUpTypes::Nil;
      pwrup_active_ = false;
      break;
    case PowerUpTypes::Nil:
    case PowerUpTypes::Break:
    case PowerUpTypes::Enlarge:
    case PowerUpTypes::Laser:  
    case PowerUpTypes::Player:
    default:
      // print something horrible to the logger
      break;
  }
}

void Ball::draw(sf::RenderWindow& window, GameStates state) {
  if (!moving_flag_) {
    if (state == Playing) {
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

void Ball::move(float delta_time, const Vaus& vaus, Brick bricks[][kLevelMaxColumns]) {
  // bool collision = false;
  if (moving_flag_) {
    for (auto& ball: balls_) {
      if (ball.active) {
        const auto factor = speed_ * delta_time;
        ball.last_position = ball.shape.getPosition();
        /* This simple checking sometimes makes the ball to go through some bricks. Especially golden bricks. */
        if (checkBrickCollision(ball, bricks) && pwrup_type_ == PowerUpTypes::Slow) speedUp();
        if (checkBorderCollision(ball) && pwrup_type_ == PowerUpTypes::Slow) speedUp();
        if (checkVausCollision(ball, vaus) && pwrup_type_ == PowerUpTypes::Slow) speedUp();

        /* This "do while" method sometimes gets stuck infinitely. */
        /* do { } while (checkBrickCollision(bricks));
        do { } while (checkBorderCollision());
        do { } while (checkShipCollision(ship)); */

        /* This also gets stuck to infinity. */
        /* do {
          collision = checkBrickCollision(bricks) || checkBorderCollision() || checkShipCollision(ship);
        } while (collision == true); */

        ball.shape.move(ball.direction.x * factor, ball.direction.y * factor);
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
    case BottomBrick:
      collision_with = "BB";
      [[fallthrough]];
    case BottomShip:
      if (collision_with == "") { collision_with = "BS"; }
      [[fallthrough]];
    case Top:
      if (collision_with == "") { collision_with = "T"; }
      invertVerticalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement) {
        ball.direction.y = kBallDefaultDisplacement - std::abs(ball.direction.x);
        random_angle_variation = 0.f;
      }
      if (ball.direction.x < 0.f) {
        ball.direction.x = ball.direction.x + random_angle_variation;
      } else {
        ball.direction.x = ball.direction.x - random_angle_variation;
      }
      break;
    case TopBrick:
      collision_with = "TB";
      [[fallthrough]];
    case TopShip:
      if (collision_with == "") { collision_with = "TS"; }
      [[fallthrough]];
    case Bottom:
      if (collision_with == "") { collision_with = "B"; }
      invertVerticalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement) {
        ball.direction.y = -kBallDefaultDisplacement + std::abs(ball.direction.x);
        random_angle_variation = 0.f;
      }
      if (ball.direction.x < 0.f) {
        ball.direction.x = ball.direction.x - random_angle_variation;
      } else {
        ball.direction.x = ball.direction.x + random_angle_variation;
      }
      break;
    case RightBrick:
      collision_with = "RB";
      [[fallthrough]];
    case RightShip:
      if (collision_with == "") { collision_with = "RS"; }
      [[fallthrough]];
    case Left:
      if (collision_with == "") { collision_with ="L"; }
      invertHorizontalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement) {
        ball.direction.x = kBallDefaultDisplacement - std::abs(ball.direction.y);
        random_angle_variation = 0.f;
      }
      if (ball.direction.y < 0.f) {
        ball.direction.y = ball.direction.y + random_angle_variation;
      } else {
        ball.direction.y = ball.direction.y - random_angle_variation;
      }
      break;
    case LeftBrick:
      collision_with = "LB";
      [[fallthrough]];
    case LeftShip:
      if (collision_with == "") { collision_with = "LS"; }
      [[fallthrough]];
    case Right:
      if (collision_with == "") { collision_with = "R"; }
      invertHorizontalDirection(ball, random_angle_variation);
      if (sumAbs(ball.direction.x, ball.direction.y) > kBallDefaultDisplacement) {
        ball.direction.x = -kBallDefaultDisplacement + std::abs(ball.direction.y);
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
  switch (kExecutionMode) {
    case Normal:
      // do nothing
      break;
    case LogFile:
      // logs to the log file and then fallthrough to Debug case
      Logger::write("(" + collision_with + ")"
                  + "\tx = " + GUI::toString(ball.direction.x)
                  + "\ty = " + GUI::toString(ball.direction.y)
                  + "\trnd = " + GUI::toString(random_angle_variation)
                  + "\tdsp = " + GUI::toString(displ)); 
      [[fallthrough]];
    case Debug:
      // logs to console
      std::cout.precision(3);
      std::cout << "(" << collision_with << ")";
      std::cout << "\tx = " << std::fixed << ball.direction.x;
      std::cout << "\ty = " << std::fixed << ball.direction.y;
      std::cout << "\trnd = " << std::fixed << random_angle_variation;
      std::cout << "\tdsp = " << std::fixed << displ << std::endl;
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
    ball.shape.setRadius(kBallDefaultRadius);
    ball.shape.setFillColor(kBallDefaultColor);
    ball.shape.setOrigin(kBallDefaultRadius, kBallDefaultRadius);
    ball.shape.setPosition(kBallDefaultPosition);
    /* We use this displacement to make sure speed is always the same regarding angle */
    ball.direction = sf::Vector2f(random_x_direction, kBallDefaultDisplacement - std::abs(random_x_direction));
    ball.last_position = ball.shape.getPosition();
  }
  balls_.front().active = true;
  /* Ball's speed_ initialization */
  speed_ = kBallDefaultSpeed;
  /* Ball start and flash clocks */
  start_clock_.restart();
  flash_clock_.restart();
  ball_flash_flag_ = true;
  moving_flag_ = false;
  /* Power-ups */
  pwrup_active_ = false;
  pwrup_type_ = PowerUpTypes::Nil;
}

void Ball::setPowerUp(PowerUpTypes type) {
  pwrup_type_ = type;
  pwrup_active_ = true;
  switch (type) {
    case PowerUpTypes::Catch:
      printf("todoooooooooooooooooooooo\n");
      break;
    case PowerUpTypes::Disruption:
      level_->setDisruptionStatus(true);
      activateDisruption();
      break;
    case PowerUpTypes::Slow:
      slowPowerUp();
      break;
    case PowerUpTypes::Nil:
    case PowerUpTypes::Break:
    case PowerUpTypes::Enlarge:
    case PowerUpTypes::Laser:  
    case PowerUpTypes::Player:
    default:
      // print something horrible to the logger
      break;
  }
}

void Ball::slowPowerUp() {
  const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<float> distribution(10.0f , 30.0f);
  slow_timer_ = distribution(generator);
  const float kDecrement = 2.f;
  speed_ /= kDecrement;
  slow_clk_.restart();
}

void Ball::speedUp() {
  const float kIncrement = 10.f;
  if (speed_ + kIncrement >= kBallDefaultSpeed) deactivatePowerUp();
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
    case PowerUpTypes::Catch:
      printf("todoooooooooooooooooooooo\n");
      break;
    case PowerUpTypes::Disruption:
      if (active_balls_ == 1u) deactivatePowerUp();
      break;
    case PowerUpTypes::Slow:
      if (slow_clk_.getElapsedTime().asSeconds() >= slow_timer_) deactivatePowerUp();
      break;
    case PowerUpTypes::Nil:
    case PowerUpTypes::Break:
    case PowerUpTypes::Enlarge:
    case PowerUpTypes::Laser:  
    case PowerUpTypes::Player:
    default:
      // print something horrible to the logger
      break;
  }
}
