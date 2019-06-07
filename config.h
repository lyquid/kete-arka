#ifndef KETE_ARKA_CONFIG_H_
#define KETE_ARKA_CONFIG_H_

// app default settings
const sf::String kAppName = "kete-arka";
const sf::String kAppVersion = "0.0";
const sf::String kGameTitle = kAppName;
const sf::String kGameTitleJ = "ケテアルカ";
// const float kPI = 3.14159f;
const int kScreenHeight = 768;
const int kScreenWidth = 672;

// ball default settings
const sf::Color kBallDefaultColor = sf::Color::White;
const sf::Vector2f kBallDefaultPosition = sf::Vector2f(kScreenWidth / 2.f, kScreenHeight - (kScreenHeight * 0.3f));
const float kBallDefaultRadius = 5.f;
const float kBallDefaultSpeed = 150.f;

// ship default setting
const sf::Color kShipDefaultColor = sf::Color::White;
const float kShipDefaultLength = 20.f;
const sf::Vector2f kShipDefaultPosition = sf::Vector2f(kScreenWidth / 2.f, kScreenHeight - (kScreenHeight * 0.1f));
const float kShipDefaultSpeed = 150.f;
const float kShipDefaultThickness = 5.f;

#endif  // KETE_ARKA_CONFIG_H_
