#include "ball.h"

sf::Vector2f Ball::getPosition(){
  return circle_shape_.getPosition();
}

sf::CircleShape Ball::getShape() {
  return circle_shape_;
}

void Ball::move(float delta_time) {
  float factor = speed_ * delta_time;
  circle_shape_.move(cos(angle_) * factor, sin(angle_) * factor);
}

void Ball::reset() {
  speed_ = kBallDefaultSpeed;
  circle_shape_.setRadius(kBallDefaultRadius);
  circle_shape_.setFillColor(kBallDefaultColor);
  circle_shape_.setOrigin(kBallDefaultRadius, kBallDefaultRadius);
  circle_shape_.setPosition(kBallDefaultPosition);
  /* do {
    angle_ = (std::rand() % 360) * 2 * kPI / 360.f;               
  } while (abs(cos(angle_)) < 0.7f); */
}
