#ifndef KETE_ARKA_CONFIG_H_
#define KETE_ARKA_CONFIG_H_

#include <SFML/Graphics.hpp>

// app utils
enum Collisions {
  Top, Bottom, Left, Right,
  TopShip, BottomShip, LeftShip, RightShip,
  TopBrick, BottomBrick, LeftBrick, RightBrick };
enum ExecutionModes { Normal, Debug, LogFile };

// app default settings
const std::string kLogFileName = "kete-arka.log";
const ExecutionModes kExecutionMode = Debug;
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
const sf::Vector2f kBallDefaultPosition = sf::Vector2f((float) kScreenWidth / 2.f, (float) kScreenHeight / 1.25f);
const float kBallDefaultRadius = 5.f;
const float kBallDefaultSpeed = 400.f;
const float kBallDefaultDisplacement = 1.41f;

// brick default settings
const int kBrickDefaultColumns = 12;
const int kBrickDefaultRows = 4;
const float kBrickDefaultLength = 56.f;
const float kBrickDefaultThickness = 16.f; 
const sf::Vector2f kBrickDefaultSize = sf::Vector2f(kBrickDefaultLength, kBrickDefaultThickness);
const sf::Color kBrickDefaultOutlineColor = sf::Color::Black;

// GUI default settings
const sf::Color kGUIDefaultFillColor = sf::Color::Black;
const sf::Color kGUIDefaultOutlineColor = sf::Color::White;
const float kGUIDefaultHeight = (float) kScreenHeight * 0.03f;
const float kGUIDefaultWidth = (float) kScreenWidth * (1.f / 3.f);
const sf::Vector2f kGUIDefaultSize = sf::Vector2f(kGUIDefaultWidth, kGUIDefaultHeight);
const float kGUIDefaultOutlineThickness = -1.f;  

// player default setting
const int kPlayerDefaultLives = 3;

// ship default settings
const sf::Color kShipDefaultColor = sf::Color::White;
const float kShipDefaultLength = 80.f;
const float kShipDefaultThickness = 15.f;
const sf::Vector2f kShipDefaultSize = sf::Vector2f(kShipDefaultLength, kShipDefaultThickness);
const sf::Vector2f kShipDefaultPosition = sf::Vector2f(((float) kScreenWidth - kShipDefaultSize.x) / 2.f, (float) kScreenHeight * 0.85f);
const float kShipDefaultSpeed = 500.f;

#endif  // KETE_ARKA_CONFIG_H_
