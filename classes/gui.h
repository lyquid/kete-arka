#ifndef KETE_ARKA_CLASSES_GUI_H_
#define KETE_ARKA_CLASSES_GUI_H_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../config.h"

class GUI {
 public:
  GUI();
  ~GUI() {}
  void drawGameCompleted(sf::RenderWindow& window);
  void drawGameOverScreen(sf::RenderWindow& window);
  void drawInGameGUI(sf::RenderWindow& window);
  void drawLevelCompletedScreen(sf::RenderWindow& window);
  void drawLevelSelection(sf::RenderWindow& window);
  void drawMenu(sf::RenderWindow& window);
  void drawPauseScreen(sf::RenderWindow& window);
  void drawTitleScreen(sf::RenderWindow& window);
  unsigned int getLevelSelectedNumber() { return level_selected_ + 1u; };
  void init();
  void reset();
  void selectNextLevel();
  void selectPreviousLevel();
  void setFinalScoreText(unsigned long long score);
  void setLevelInfo(unsigned int lvl_position, unsigned int lvl_num, const std::string& lvl_name);
  void setLivesText(unsigned int lives);
  void setScoreText(unsigned long long score);
  void setRenderFlashingTextFlag(bool status);
  void update(unsigned int lvl_num, const std::string& lvl_name);
  void update(unsigned int lvl_num, const std::string& lvl_name, const std::string& next_lvl_name);

 private:
  enum class TextCenter { 
    Horizontal, Vertical, BothAxis, 
    TopLeft, TopRight, Default 
  };
  struct LevelInfo {
    unsigned int number;
    std::string  name;
    std::string  select_text;
  };
  void initLevelsList();
  static void initText(sf::Text&          text, 
                       const std::string& string_text, 
                       const sf::Font&    font, 
                       unsigned int       size, 
                       const sf::Color&   color, 
                       const TextCenter&  mode = TextCenter::Default);
  template<typename T> static void setOrigin(T& shape, TextCenter mode);
  void updateFlashingTextFlag();
  void updateLevelSelectionShape(unsigned int previous_level = 0u);
  sf::Font font_;
  unsigned int current_level_;
  bool render_flashing_text_flag_;
  sf::Clock flashing_text_clock_;
  /* Titles and flow */
  sf::Text game_over_text_;
  sf::Text level_select_title_text_;
  sf::Text pause_text_;
  sf::Text press_any_key_text_;
  sf::Text press_start_text_;
  sf::Text title_text_;
  /* Main menu */
  sf::Text menu_start_text_;
  sf::Text menu_level_text_;
  sf::Text menu_quit_text_;
  /* In game GUI */ 
  sf::Text gui_level_text_;
  sf::Text gui_lives_text_;
  sf::Text gui_score_text_;
  /* Level selection */
  std::vector<LevelInfo> level_info_;
  std::vector<sf::Text> level_info_texts_;
  sf::Text level_select_keys_;
  unsigned int level_selected_;
  sf::RectangleShape level_selected_shape_;
  /* Level completed */
  sf::Text level_completed_title_;
  sf::Text level_completed_name_;
  sf::Text level_completed_next_;
  sf::Text level_completed_next_name_;
  sf::Text total_score_text_;
  sf::Text level_completed_continue_;
  /* Game completed */
  sf::Text game_completed_;
  /* GUI & menu default settings */
  static constexpr unsigned int kGUIGameOverFontSize_       = 30u;
  static constexpr unsigned int kGUIGameTitleFontSize_      = 60u;
  static constexpr unsigned int kGUILevelSelectFontSize_    = 18u;
  static constexpr unsigned int kGUIMenuItemFontSize_       = 20u;
  static constexpr unsigned int kGUIPauseTextFontSize_      = 20u;
  static constexpr unsigned int kGUIPressStartTextFontSize_ = 20u;
  static constexpr unsigned int kGUITextFontSize_           = 15u;
  static constexpr unsigned int kGUILevelSelectKeys_        = 12u;
  static constexpr unsigned int kGUILevelCompletedFontSize_ = 25u;
  static constexpr unsigned int kGUIDefaultFontOutline_     = 1u;
  static constexpr float kGUIDefaultMargin_ = 4.f;
  static const sf::Color kGUIDefaultFontColor_;
  static const sf::Color kGUIDefaultSelectedFontColor_;
  static const sf::Color kGUIDefaultFontOutlineColor_;
  /* Strings */
  static constexpr auto kLevelCompletedText_ = "Completed";
  static constexpr auto kLevelCompletedNext_ = "Next level is:";
  static constexpr auto kGameCompletedText_  = "GAME COMPLETED!";
  static constexpr auto kGameOverText_       = "Game over";
  static constexpr auto kTotalScoreText_     = "Score ";
  static constexpr auto kPauseText_          = "Paused";
  static constexpr auto kContinueText_       = "Press any key to continue";
  static constexpr auto kPressStartText_     = "Press any key to start";
  static constexpr auto kPressSpaceText_     = "Press space to continue";
  static constexpr auto kLevelSelectText_    = "Select a level";
  static constexpr auto kLevelSelectKeys_    = "ESC - Back     UP/DOWN - Select level     INTRO - Play";
  static constexpr auto kGUILevelText_       = "LEVEL ";
  static constexpr auto kGUILivesText_       = "LIVES ";
  static constexpr auto kGUIScoreText_       = "SCORE ";
  static constexpr auto kMenuStartText_      = "(1) Start";
  static constexpr auto kMenuLevelText_      = "(2) Level selection";
  static constexpr auto kMenuQuitText_       = "(Q) Quit";
};

#endif  // KETE_ARKA_CLASSES_GUI_H_