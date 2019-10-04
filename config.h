#ifndef KETE_ARKA_CONFIG_H_
#define KETE_ARKA_CONFIG_H_

// app default settings
const int kScreenHeight = 768;
const int kScreenWidth = 672;
const int kGameTitleFontSize = 60;
const int kPauseTextFontSize = 20;
const int kPressStartTextFontSize = 20;

// app default strings
const sf::String kAppName = "kete-arka";
const sf::String kAppVersion = "0.0";
const sf::String kGameTitle = kAppName;
const sf::String kGameTitleJ = "ケテアルカ";
const sf::String kPauseText = "Paused";
const sf::String kPressStartText = "Press 1 to start";

// ball default settings
const sf::Color kBallDefaultColor = sf::Color::White;
const sf::Vector2f kBallDefaultPosition = sf::Vector2f(kScreenWidth / 2.f, kScreenHeight / 1.25f);
const float kBallDefaultRadius = 5.f;
const float kBallDefaultSpeed = 600.f;
const float kBallDefaultDisplacement = 1.41f;

// ship default settings
const sf::Color kShipDefaultColor = sf::Color::White;
const float kShipDefaultLength = 80.f;
const float kShipDefaultThickness = 15.f;
const sf::Vector2f kShipDefaultSize = sf::Vector2f(kShipDefaultLength, kShipDefaultThickness);
const sf::Vector2f kShipDefaultPosition = sf::Vector2f((kScreenWidth - kShipDefaultSize.x) / 2.f, kScreenHeight * 0.85f);
const float kShipDefaultSpeed = 400.f;

// utils
enum Borders {Top, Bottom, Left, Right};

#endif  // KETE_ARKA_CONFIG_H_
