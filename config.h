#ifndef KETE_ARKA_CONFIG_H_
#define KETE_ARKA_CONFIG_H_

#include "./lib/assets_path.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace k {

  enum BrickTypes { _, W, O, L, G, R, B, P, Y, S, A };
  enum class Background { Blue, Green, BlueCircuit, RedCircuit, Moai };
  enum class ExecutionModes { Normal, Debug, LogFile };
  enum class GameStates {
    Title, Menu, LevelSelection,
    Playing, Paused, LevelCompleted,
    GameCompleted, GameOver, Quit
  };
  enum class PowerUpTypes {
    Nil, Break, Catch, Disruption,
    Enlarge, Laser, Player, Slow,
    count
  };
  struct Brick {
    bool               active;
    BrickTypes         type;
    unsigned int       resistance;
    unsigned int       points;
    sf::RectangleShape shape;
    bool               beveled;
    sf::VertexArray    bevel;
  };
  struct PowerUp {
    bool               active;
    sf::RectangleShape shape;
    PowerUpTypes       type;
  };
  struct Vaus {
    sf::RectangleShape       shape;
    sf::RectangleShape       collision_rect;
    float                    speed;
    std::vector<sf::Texture> laser_textures;
    std::vector<sf::Texture> textures;
  };
  /* App settings */
  constexpr auto kAppName    = "kete-arka";
  constexpr auto kGameTitle  = kAppName;
  constexpr auto kGameTitleJ = "ケテアルカ";
  constexpr auto kAppVersion = "0.1";
  constexpr unsigned int kScreenHeight = 768u;
  constexpr unsigned int kScreenWidth  = 672u;
  constexpr ExecutionModes kExecutionMode = ExecutionModes::Debug;
  /* Image stuff */
  constexpr auto kImageExt  = ".png";
  const auto kImagePath = ktp::Assets::getAssetsPath("img");
  /* Levels stuff */
  constexpr unsigned int kMaxLevels       = 36u;
  constexpr unsigned int kLevelMaxColumns = 11u;
  constexpr unsigned int kLevelMaxRows    = 18u;
  /* GUI stuff */
  constexpr float kGUIBorderThickness = 28.f;
}

#endif  // KETE_ARKA_CONFIG_H_
