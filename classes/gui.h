#ifndef KETE_ARKA_CLASSES_GUI_H_
#define KETE_ARKA_CLASSES_GUI_H_

#include <sstream> // std::ostringstream

#include "../config.h"

struct LevelInfo {
  unsigned int number;
  std::string name;
  std::string select_text;
};

class GUI {
 public:
  GUI() {
    render_flashing_text_flag_ = true;
  }
  ~GUI() {}
  void drawGameCompleted(sf::RenderWindow &window);
  void drawGameOverScreen(sf::RenderWindow &window);
  void drawInGameGUI(sf::RenderWindow &window);
  void drawLevelCompletedScreen(sf::RenderWindow &window);
  void drawLevelSelection(sf::RenderWindow &window);
  void drawMenu(sf::RenderWindow &window);
  void drawPauseScreen(sf::RenderWindow &window);
  void drawTitleScreen(sf::RenderWindow &window);
  int getLevelSelectedNumber();
  void init(const sf::Font &font);
  void initLevelsList(const sf::Font &font);
  void reset();
  void selectNextLevel();
  void selectPreviousLevel();
  void setFinalScoreText(unsigned long long int score);
  void setLevelInfo(int lvl_position, int lvl_num, sf::String lvl_name);
  void setLivesText(const int lives);
  void setScoreText(const unsigned long long int score);
  void setRenderFlashingTextFlag(const bool status);
  static void initText( sf::Text              &text, 
                        const sf::String      string_text, 
                        const sf::Font        &font, 
                        const int             size, 
                        const sf::Color       color, 
                        const TextCenterModes mode = Default);
  template <typename T> static void setOrigin(T &shape, const TextCenterModes mode);
  template <typename T> static std::string toString(const T &t);
  void update(unsigned int lvl_num, std::string lvl_name);
  void update(unsigned int lvl_num, std::string lvl_name, std::string next_lvl_name);

 private:
  void updateFlashingTextFlag();
  void updateLevelSelectionShape(int previous_level = 0);
  unsigned int current_level_;
  bool render_flashing_text_flag_;
  sf::Clock flashing_text_clock_;
  // titles and flow
  sf::Text game_over_text_;
  sf::Text level_select_title_text_;
  sf::Text pause_text_;
  sf::Text press_any_key_text_;
  sf::Text press_start_text_;
  sf::Text title_text_;
  // main menu items
  sf::Text menu_start_text_;
  sf::Text menu_level_text_;
  sf::Text menu_quit_text_;
  // in game gui 
  sf::Text gui_level_text_;
  sf::Text gui_lives_text_;
  sf::Text gui_score_text_;
  // levels array and strings
  LevelInfo level_info_[kMaxLevels];
  sf::Text level_info_texts_[kMaxLevels];
  sf::Text level_select_keys_;
  unsigned int level_selected_;
  sf::RectangleShape level_selected_shape_;
  // level completed
  sf::Text level_completed_title_;
  sf::Text level_completed_name_;
  sf::Text level_completed_next_;
  sf::Text level_completed_next_name_;
  sf::Text total_score_text_;
  sf::Text level_completed_continue_;
  // game completed
  sf::Text game_completed_;
};

#endif  // KETE_ARKA_CLASSES_GUI_H_