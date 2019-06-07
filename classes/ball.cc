#include "ball.h"

//sf::Vector2f Ball::getPosition(){
//  return circle_shape_.getPosition();
//}

sf::CircleShape Ball::getShape() {
  return ball_shape_;
}

bool Ball::checkBoundaryCollision() {
  bool collision = false;
  float current_radius = ball_shape_.getRadius();
  // check for lateral collisions with the screen boundaries
  if (ball_shape_.getPosition().x - current_radius <= 0) {
    // left collision
    direction_.x = -direction_.x;
    ball_shape_.setPosition(0.1f + current_radius, ball_shape_.getPosition().y);
    // TODO: play sound
    collision = true;
  } else if (ball_shape_.getPosition().x + current_radius >= kScreenWidth) {
    // right collision
    direction_.x = -direction_.x;
    ball_shape_.setPosition(kScreenWidth - current_radius - 0.1f, ball_shape_.getPosition().y);
    // TODO: play sound
    collision = true;
  }
  // check for vertical collisions with the screen boundaries
  if (ball_shape_.getPosition().y - current_radius <= 0) {
    // top collision
    direction_.y = -direction_.y;
    ball_shape_.setPosition(ball_shape_.getPosition().x, 0.1f + current_radius);
    // TODO: play sound
    collision = true;
  } else if (ball_shape_.getPosition().y + current_radius >= kScreenHeight) {
    // bottom collision
    direction_.y = -direction_.y;
    ball_shape_.setPosition(ball_shape_.getPosition().x, kScreenHeight - current_radius - 0.1f);
    // TODO: play sound
    collision = true;
  }
  return collision;
}

bool Ball::checkMachineWins() {
  // TODO: check if ball goes beyond kScreenHeight
  return false;
}

void Ball::move(float delta_time) {
  float factor = speed_ * delta_time;
  ball_shape_.move(direction_.x * factor, direction_.y * factor);

  if (checkMachineWins()){
    // GAME OVER, MACHINE WINS
  } else {
    checkBoundaryCollision();
  }
}

void Ball::reset() {
  // Ball direction_ vector randomization
  float random_x_direction = 0.f;
  do { // get a number between -10 and 10, not including 0.
    random_x_direction = std::rand() % 21 - 10;
  } while (random_x_direction == 0.f);
  // take the random number and divide it to make it between -1.0, -0.9, -0.8, ... to 1.0
  random_x_direction = random_x_direction / 10.f;
  direction_ = sf::Vector2f(random_x_direction, 1.f);
  // Ball's speed_ initialization
  speed_ = kBallDefaultSpeed;
  // Ball "physical" properties
  ball_shape_.setRadius(kBallDefaultRadius);
  ball_shape_.setFillColor(kBallDefaultColor);
  ball_shape_.setOrigin(kBallDefaultRadius, kBallDefaultRadius);
  ball_shape_.setPosition(kBallDefaultPosition);
}
