#include "ball.h"

void Ball::draw(sf::RenderWindow& window) {
  window.draw(shape_);
}

bool Ball::checkBorderCollision() {
  bool collision = false;
  float current_radius = shape_.getRadius();
  if (shape_.getPosition().x - current_radius <= 0) {
    // left collision
    randomizeBounceAngle(Left);
    shape_.setPosition(current_radius + 0.1f, shape_.getPosition().y); 
    collision = true;
  } else if (shape_.getPosition().x + current_radius >= kScreenWidth) {
    // right collision
    randomizeBounceAngle(Right);
    shape_.setPosition(kScreenWidth - current_radius - 0.1f, shape_.getPosition().y); 
    collision = true;
  } else if (shape_.getPosition().y - current_radius <= 0) {
    // top collision
    randomizeBounceAngle(Top);
    shape_.setPosition(shape_.getPosition().x, current_radius + 0.1f);
    collision = true;
  } else if (shape_.getPosition().y + current_radius >= kScreenHeight) {
    // bottom collision
    randomizeBounceAngle(Bottom);
    shape_.setPosition(shape_.getPosition().x, kScreenHeight - current_radius - 0.1f);
    collision = true;
  }
  return collision;
}

bool Ball::checkMachineWins() {
  // TODO: check if ball goes beyond kScreenHeight
  return false;
}

bool Ball::checkShipCollision(Ship ship) {
  bool collision = false;
  float ball_radius = shape_.getRadius();
  float ball_y = shape_.getPosition().y;
  float ship_x = ship.getShipShape().getPosition().x;
  float ship_x_size = ship.getShipSize().x;
  // ship collision checking
  if (ship.getShipShape().getGlobalBounds().intersects(shape_.getGlobalBounds())) {
    collision = true;
    if (last_position_.x < ship_x) {
      // left hit
      direction_.x = -direction_.x;
      shape_.setPosition(ship_x - ball_radius - 0.1f, ball_y);
    } else if (last_position_.x > ship_x + ship_x_size) {
      // right hit
      direction_.x = -direction_.x;
      shape_.setPosition(ship_x + ship_x_size + ball_radius + 0.1f, ball_y);
    } else {
      // front/rear hit
      direction_.y = -direction_.y;
    }
  }
  return collision; // not doing anything with this right now
}

void Ball::move(const float delta_time, Ship ship) {
  float factor = speed_ * delta_time;
  if (checkMachineWins()) {
    // todo: check if ball touches the bottom of the screen
  } else if (checkBorderCollision()) {
    // boundary collision
  } else if (checkShipCollision(ship)) {
    // ship collision
  }
  last_position_ = shape_.getPosition();
  shape_.move(direction_.x * factor, direction_.y * factor);
}

void Ball::randomizeBounceAngle(const Borders border) {
  float displ = 0.f;
  std::string collision_with = "";
  float random_angle_variation = (std::rand() % 21 - 10) / 100.f;  // rnd -0.10 to 0.10
  // todo: There's a bug here. Sometimes disp exceeds 1.41
  switch(border) {
    case Top:
      collision_with = "T";
      direction_.y = -direction_.y + random_angle_variation;
      if (direction_.x < 0) {
        direction_.x = direction_.x + random_angle_variation;
      } else {
        direction_.x = direction_.x - random_angle_variation;
      }
      break;
    case Bottom:
      collision_with = "B";
      direction_.y = -direction_.y + random_angle_variation;
      if (direction_.x < 0) {
        direction_.x = direction_.x - random_angle_variation;
      } else {
        direction_.x = direction_.x + random_angle_variation;
      }
      break;
    case Left:
    collision_with = "L";
      direction_.x = -direction_.x + random_angle_variation;
      if (direction_.y < 0) {
        direction_.y = direction_.y + random_angle_variation;
      } else {
        direction_.y = direction_.y - random_angle_variation;
      }
      break;
    case Right:
    collision_with = "R";
      direction_.x = -direction_.x + random_angle_variation;
      if (direction_.y < 0) {
        direction_.y = direction_.y - random_angle_variation;
      } else {
        direction_.y = direction_.y + random_angle_variation;
      }
      break;
  }
  displ = std::abs(direction_.x) + std::abs(direction_.y);
  switch (kExecutionMode) {
    case LogFile:
      // logs to log file
      Logger::write("(" + collision_with + ")"
                  + "\tx = " + toString(direction_.x)
                  + "\ty = " + toString(direction_.y)
                  + "\trnd = " + toString(random_angle_variation)
                  + "\tdsp = " + toString(displ)); 
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
  // Take the random number and divide it to make it between -1.0, -0.9, -0.8, ... to 1.0
  random_x_direction = random_x_direction / 10.f;
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
}

template <typename T> std::string toString(const T& t) { 
  std::ostringstream oss; 
  oss << t; 
  return oss.str();
}