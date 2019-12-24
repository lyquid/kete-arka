#ifndef KETE_ARKA_CONFIG_H_
#define KETE_ARKA_CONFIG_H_

#include <string>
#include <SFML/Graphics.hpp>

// app utils
/// TODO: make this to enum class
enum Collisions {
  Top, Bottom, Left, Right,
  TopShip, BottomShip, LeftShip, RightShip,
  TopBrick, BottomBrick, LeftBrick, RightBrick };
enum ExecutionModes { Normal, Debug, LogFile };
enum GameStates { Title, Menu, LevelSelection, Playing, Paused, GameOver, Quit };
enum TextCenterModes { Horizontal, Vertical, BothAxis, TopLeft, TopRight, Default, Current };

// app default settings
const ExecutionModes  kExecutionMode  = Debug;
const std::string     kLogFileName    = "kete-arka.log";
const int             kScreenHeight   = 768;
const int             kScreenWidth    = 672;

// app default strings
const sf::String  kAppName          = "kete-arka";
const sf::String  kAppVersion       = "0.0";
const sf::String  kGameOverText     = "GAME OVER";
const sf::String  kGameTitle        = kAppName;
const sf::String  kGameTitleJ       = "ケテアルカ";
const sf::String  kPauseText        = "Paused";
const sf::String  kContinueText     = "Press any key to continue";
const sf::String  kPressStartText   = "Press any key to start";
const sf::String  kLevelSelectText  = "Select a level";
const sf::String  kLevelSelectKeys  = "ESC - Back     UP/DOWN - Select level     INTRO - Play";
const sf::String  kGUILevelText     = "LEVEL XX";
const sf::String  kGUILivesText     = "LIVES ";
const sf::String  kGUIScoreText     = "SCORE ";
const sf::String  kMenuStartText    = "(1) Start";
const sf::String  kMenuLevelText    = "(2) Level selection";
const sf::String  kMenuQuitText     = "(Q) Quit";

// ball default settings
const float         kBallDefaultRadius        = 5.f;         
const float         kBallDefaultSpeed         = 400.f;
const float         kBallDefaultDisplacement  = 1.41f;
const sf::Vector2f  kBallDefaultPosition      = sf::Vector2f((float) kScreenWidth / 2.f, (float) kScreenHeight * 0.7f);
const sf::Color     kBallDefaultColor         = sf::Color::White;

// brick default settings
const float         kBrickDefaultStart        = 80.f;
const float         kBrickDefaultWidth        = 56.f;
const float         kBrickDefaultHeight       = 16.f; 
const sf::Vector2f  kBrickDefaultSize         = sf::Vector2f(kBrickDefaultWidth, kBrickDefaultHeight);
const sf::Color     kBrickDefaultOutlineColor = sf::Color::Black;
const int           kBrickDefaultColumns      = 12;
const int           kBrickDefaultRows         = 4;

// GUI/Menu default settings
const int       kGUIGameOverFontSize          = 30;
const int       kGUIGameTitleFontSize         = 60;
const int       kGUILevelSelectFontSize       = 25;
const int       kGUIMenuItemFontSize          = 20;
const int       kGUIPauseTextFontSize         = 20;
const int       kGUIPressStartTextFontSize    = 20;
const int       kGUITextFontSize              = 15;
const int       kGUILevelSelectKeys           = 12;
const sf::Color kGUIDefaultFontColor          = sf::Color::White;
const sf::Color kGUIDefaultSelectedFontColor  = sf::Color::Black;
const float     kGUIDefaultMargin             = 8.f;
const float     kGUIDefaultHeight             = kGUIDefaultMargin + (float) kGUIPauseTextFontSize;

// level default settings
const int kTotalLevels = 20;

// player default setting
const int kPlayerDefaultLives = 3;

// ship default settings
const float         kShipDefaultWidth     = 80.f;
const float         kShipDefaultHeight    = 15.f;
const sf::Vector2f  kShipDefaultSize      = sf::Vector2f(kShipDefaultWidth, kShipDefaultHeight);
const sf::Vector2f  kShipDefaultPosition  = sf::Vector2f(((float) kScreenWidth - kShipDefaultSize.x) / 2.f, (float) kScreenHeight * 0.85f);
const float         kShipDefaultSpeed     = 500.f;
const sf::Color     kShipDefaultColor     = sf::Color::White;

#endif  // KETE_ARKA_CONFIG_H_
