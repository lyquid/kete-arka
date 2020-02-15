#ifndef KETE_ARKA_CONFIG_H_
#define KETE_ARKA_CONFIG_H_

#include <string> // std::string
#include <SFML/Graphics.hpp>

// app utils
enum BrickTypes { _, W, O, L, G, R, B, P, Y, S, A };
/// TODO: make this to enum class
enum Collisions {
  Top, Bottom, Left, Right,
  TopShip, BottomShip, LeftShip, RightShip,
  TopBrick, BottomBrick, LeftBrick, RightBrick };
enum ExecutionModes { Normal, Debug, LogFile };
enum GameStates { Title, Menu, LevelSelection, Playing, Paused, LevelCompleted, GameCompleted, GameOver, Quit };
// enum TextCenterModes { Horizontal, Vertical, BothAxis, TopLeft, TopRight, Default };

// app default settings
const ExecutionModes  kExecutionMode  = Debug;
const std::string     kLogFileName    = "kete-arka.log";
const int             kScreenHeight   = 768;
const int             kScreenWidth    = 672;

// app default strings
const sf::String  kAppName            = "kete-arka";
const sf::String  kAppVersion         = "0.0";
const sf::String  kLevelCompletedText = "Completed";
const sf::String  kLevelCompletedNext = "Next level is:";
const sf::String  kGameCompletedText  = "GAME COMPLETED!";
const sf::String  kGameOverText       = "Game over";
const sf::String  kTotalScoreText     = "Score ";
const sf::String  kGameTitle          = kAppName;
const sf::String  kGameTitleJ         = "ケテアルカ";
const sf::String  kPauseText          = "Paused";
const sf::String  kContinueText       = "Press any key to continue";
const sf::String  kPressStartText     = "Press any key to start";
const sf::String  kPressSpaceText     = "Press space to continue";
const sf::String  kLevelSelectText    = "Select a level";
const sf::String  kLevelSelectKeys    = "ESC - Back     UP/DOWN - Select level     INTRO - Play";
const sf::String  kGUILevelText       = "LEVEL ";
const sf::String  kGUILivesText       = "LIVES ";
const sf::String  kGUIScoreText       = "SCORE ";
const sf::String  kMenuStartText      = "(1) Start";
const sf::String  kMenuLevelText      = "(2) Level selection";
const sf::String  kMenuQuitText       = "(Q) Quit";

// ball default settings
const float         kBallDefaultRadius        = 5.f;         
const float         kBallDefaultSpeed         = 400.f;
const float         kBallDefaultDisplacement  = 1.41f;
const sf::Vector2f  kBallDefaultPosition      = sf::Vector2f((float) kScreenWidth / 2.f, (float) kScreenHeight * 0.75f);
const sf::Color     kBallDefaultColor         = sf::Color::White;

// brick default settings
const float         kBrickDefaultStart    = 0.f;
const float         kBrickDefaultWidth    = 56.f;
const float         kBrickDefaultHeight   = 28.f;
const float         kBrickDefaultOutline  = -1.5f;
const float         kBrickDefaultBevel    = 5.f; 
const sf::Vector2f  kBrickDefaultSize     = sf::Vector2f(kBrickDefaultWidth, kBrickDefaultHeight);

// brick colors
const sf::Color kBrickDefaultColor        = sf::Color::White;
const sf::Color kBrickDefaultOutlineColor = sf::Color::Black;
const sf::Color kBrickWhite               = sf::Color(252, 252, 252);
const sf::Color kBrickOrange              = sf::Color(252, 116,  96);
const sf::Color kBrickLighBlue            = sf::Color( 60, 188, 252);
const sf::Color kBrickGreen               = sf::Color(128, 208,  16);
const sf::Color kBrickRed                 = sf::Color(216,  40,   0);
const sf::Color kBrickBlue                = sf::Color(  0, 112, 236);
const sf::Color kBrickPink                = sf::Color(252, 116, 180);
const sf::Color kBrickYellow              = sf::Color(252, 152,  56);
const sf::Color kBrickSilver              = sf::Color(188, 188, 188);
const sf::Color kBrickGold                = sf::Color(240, 188,  60);

// GUI/Menu default settings
const int       kGUIGameOverFontSize          = 30;
const int       kGUIGameTitleFontSize         = 60;
const int       kGUILevelSelectFontSize       = 18;
const int       kGUIMenuItemFontSize          = 20;
const int       kGUIPauseTextFontSize         = 20;
const int       kGUIPressStartTextFontSize    = 20;
const int       kGUITextFontSize              = 15;
const int       kGUILevelSelectKeys           = 12;
const int       kGUILevelCompletedFontSize    = 25;
const int       kGUIDefaultFontOutline        = 1;
const sf::Color kGUIDefaultFontColor          = sf::Color::White;
const sf::Color kGUIDefaultSelectedFontColor  = sf::Color::Black;
const sf::Color kGUIDefaultFontOutlineColor   = sf::Color::Black;
const float     kGUIDefaultMargin             = 4.f;
const float     kGUIBorderThickness           = 28.f;

// level default settings
const int kLevelMaxColumns  = 11;
const int kLevelMaxRows     = 18;
const int kMaxLevels        = 36;

#endif  // KETE_ARKA_CONFIG_H_
