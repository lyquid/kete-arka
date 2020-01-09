#include "ball.h"

bool Ball::checkBrickCollision(Brick bricks[][kLevelMaxColumns]) {
  bool collision = false;
  for (int i = 0; i < kLevelMaxRows; ++i) {
    for (int j = 0; j < kLevelMaxColumns; ++j) {
      if (bricks[i][j].isActive() && bricks[i][j].getShape().getGlobalBounds().intersects(shape_.getGlobalBounds())) {
        float ball_x = shape_.getPosition().x;
        float ball_y = shape_.getPosition().y;
        float brick_x = bricks[i][j].getShape().getPosition().x;
        float brick_x_size = bricks[i][j].getSize().x;
        float brick_y = bricks[i][j].getShape().getPosition().y;
        float brick_y_size = bricks[i][j].getSize().y;
        collision = true;
        bricks[i][j].decreaseResistance();
        if (last_position_.x < brick_x) {
          // left hit
          randomizeBounceAngle(LeftBrick);
          shape_.setPosition(brick_x - current_radius_, ball_y);
        } else if (last_position_.x > brick_x + brick_x_size) {
          // right hit
          randomizeBounceAngle(RightBrick);
          shape_.setPosition(brick_x + brick_x_size + current_radius_, ball_y);
        } else if (last_position_.y < brick_y) {
          // top hit
          randomizeBounceAngle(TopBrick);
          shape_.setPosition(ball_x, brick_y - current_radius_);
        } else {
          // bottom hit
          randomizeBounceAngle(BottomBrick);
          shape_.setPosition(ball_x, brick_y + brick_y_size + current_radius_);
        }
      }
    }
  }
  return collision;
}

bool Ball::checkBorderCollision() {
  bool collision = false;
  if (shape_.getPosition().x - current_radius_ <= 0.f) {
    // left collision
    randomizeBounceAngle(Left);
    shape_.setPosition(current_radius_ + 0.1f, shape_.getPosition().y); 
    collision = true;
  } else if (shape_.getPosition().x + current_radius_ >= kScreenWidth) {
    // right collision
    randomizeBounceAngle(Right);
    shape_.setPosition(kScreenWidth - current_radius_ - 0.1f, shape_.getPosition().y); 
    collision = true;
  } else if (shape_.getPosition().y - current_radius_ <= kGUIDefaultHeight) {
    // top collision
    randomizeBounceAngle(Top);
    shape_.setPosition(shape_.getPosition().x, current_radius_ + kGUIDefaultHeight + 0.1f);
    collision = true;
  } else if (shape_.getPosition().y + current_radius_ >= kScreenHeight) {
    // bottom "collision"
    player_->decreaseLives();
    ship_->reset();
    reset();
  }
  return collision;
}

bool Ball::checkShipCollision(Ship ship) {
  bool collision = false;
  float ball_x = shape_.getPosition().x;
  float ball_y = shape_.getPosition().y;
  float ship_x = ship.getShape().getPosition().x;
  float ship_x_size = ship.getSize().x;
  float ship_y = ship.getShape().getPosition().y;
  if (ship.getShape().getGlobalBounds().intersects(shape_.getGlobalBounds())) {
    collision = true;
    if (last_position_.x < ship_x) {
      // left hit
      randomizeBounceAngle(LeftShip);
      shape_.setPosition(ship_x - current_radius_ - 0.1f, ball_y);
    } else if (last_position_.x > ship_x + ship_x_size) {
      // right hit
      randomizeBounceAngle(RightShip);
      shape_.setPosition(ship_x + ship_x_size + current_radius_ + 0.1f, ball_y);
    } else {
      // front/rear hit (rear hit should be imposible!)
      randomizeBounceAngle(TopShip);
      shape_.setPosition(ball_x, ship_y - current_radius_ - 0.1f);
    }
  }
  return collision; // not doing anything with this right now
}

void Ball::draw(sf::RenderWindow &window, GameStates state) {
  if (!moving_flag_) {
    if (state == Playing) {
      updateFlashFlag();
    }
    if (ball_flash_flag_) {
      window.draw(shape_);
    }
  } else {
    window.draw(shape_);
  }
}

void Ball::init(Player *ptp, Ship *pts) {
  player_ = ptp;
  ship_ = pts;
  reset();
}

void Ball::invertHorizontalDirection(const float variation) {
  direction_.x = -direction_.x + variation;
}

void Ball::invertVerticalDirection(const float variation) {
  direction_.y = -direction_.y + variation;
}

void Ball::move(const float delta_time, Ship ship, Brick bricks[][kLevelMaxColumns]) {
  float factor = speed_ * delta_time;
  last_position_ = shape_.getPosition();
  current_radius_ = shape_.getRadius();
  if (moving_flag_) {
    // todo: maybe check everything to prevent the ball bugging
    if (checkBorderCollision()) {
      // boundary collision
    } else if (checkShipCollision(ship)) {
      // ship collision
    } else if (checkBrickCollision(bricks)) {
      // brick collision
    }
    shape_.move(direction_.x * factor, direction_.y * factor);
  } else if (start_clock_.getElapsedTime().asSeconds() > 1.5f) {
    moving_flag_ = true;
  }
}

void Ball::randomizeBounceAngle(const Collisions collision) {
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
      invertVerticalDirection(random_angle_variation);
      if (sumAbs(direction_.x, direction_.y) > kBallDefaultDisplacement) {
        direction_.y = kBallDefaultDisplacement - std::abs(direction_.x);
        random_angle_variation = 0.f;
      }
      if (direction_.x < 0.f) {
        direction_.x = direction_.x + random_angle_variation;
      } else {
        direction_.x = direction_.x - random_angle_variation;
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
      invertVerticalDirection(random_angle_variation);
      if (sumAbs(direction_.x, direction_.y) > kBallDefaultDisplacement) {
        direction_.y = -kBallDefaultDisplacement + std::abs(direction_.x);
        random_angle_variation = 0.f;
      }
      if (direction_.x < 0.f) {
        direction_.x = direction_.x - random_angle_variation;
      } else {
        direction_.x = direction_.x + random_angle_variation;
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
      invertHorizontalDirection(random_angle_variation);
      if (sumAbs(direction_.x, direction_.y) > kBallDefaultDisplacement) {
        direction_.x = kBallDefaultDisplacement - std::abs(direction_.y);
        random_angle_variation = 0.f;
      }
      if (direction_.y < 0.f) {
        direction_.y = direction_.y + random_angle_variation;
      } else {
        direction_.y = direction_.y - random_angle_variation;
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
      invertHorizontalDirection(random_angle_variation);
      if (sumAbs(direction_.x, direction_.y) > kBallDefaultDisplacement) {
        direction_.x = -kBallDefaultDisplacement + std::abs(direction_.y);
        random_angle_variation = 0.f;
      }
      if (direction_.y < 0.f) {
        direction_.y = direction_.y - random_angle_variation;
      } else {
        direction_.y = direction_.y + random_angle_variation;
      }
      break;
  }
  displ = sumAbs(direction_.x, direction_.y);
  switch (kExecutionMode) {
    case Normal:
      // do nothing
      break;
    case LogFile:
      // logs to the log file and then fallthrough to Debug case
      Logger::write("(" + collision_with + ")"
                  + "\tx = " + GUI::toString(direction_.x)
                  + "\ty = " + GUI::toString(direction_.y)
                  + "\trnd = " + GUI::toString(random_angle_variation)
                  + "\tdsp = " + GUI::toString(displ)); 
      [[fallthrough]];
    case Debug:
      // logs to console
      std::cout.precision(3);
      std::cout << "(" << collision_with << ")";
      std::cout << "\tx = " << std::fixed << direction_.x;
      std::cout << "\ty = " << std::fixed << direction_.y;
      std::cout << "\trnd = " << std::fixed << random_angle_variation;
      std::cout << "\tdsp = " << std::fixed << displ << std::endl;
      break;
  }
}

void Ball::reset() {
  // Ball direction_ vector randomization
  float random_x_direction = 0.f;
  do {  // Get a number between -10 and 10, not including 0.
    random_x_direction = std::rand() % 21 - 10;
  } while (random_x_direction == 0.f);
  // Take the random number and divide it to make it between -0.10, -0.09, -0.08, ... to 0.10
  random_x_direction = random_x_direction / 100.f;
  // We use this displacement to make sure speed is always the same regarding angle
  direction_ = sf::Vector2f(random_x_direction, kBallDefaultDisplacement - std::abs(random_x_direction));
  // Ball's speed_ initialization
  speed_ = kBallDefaultSpeed;
  // Ball "physical" properties
  shape_.setRadius(kBallDefaultRadius);
  shape_.setFillColor(kBallDefaultColor);
  shape_.setOrigin(kBallDefaultRadius, kBallDefaultRadius);
  shape_.setPosition(kBallDefaultPosition);
  last_position_ = shape_.getPosition();
  current_radius_ = shape_.getRadius();
  // Ball start and flash clocks
  start_clock_.restart();
  flash_clock_.restart();
  ball_flash_flag_ = true;
  moving_flag_ = false;
}

float Ball::sumAbs(const float num1, const float num2) {
  return std::abs(num1) + std::abs(num2);
}

void Ball::updateFlashFlag() {
  if (flash_clock_.getElapsedTime().asSeconds() > 0.15f) {
    ball_flash_flag_ = !ball_flash_flag_;
    flash_clock_.restart();
  }
}
