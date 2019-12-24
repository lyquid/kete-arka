#ifndef KETE_ARKA_CLASSES_GUI_H_
#define KETE_ARKA_CLASSES_GUI_H_

#include <sstream> // std::ostringstream

#include "../config.h"

class GUI {
 public:
  GUI() {
    render_flashing_text_flag_ = true;
  }
  ~GUI() {}
  void drawGameOverScreen(sf::RenderWindow &window);
  void drawInGameGUI(sf::RenderWindow &window);
  void drawLevelSelection(sf::RenderWindow &window);
  void drawMenu(sf::RenderWindow &window);
  void drawPauseScreen(sf::RenderWindow &window);
  void drawTitleScreen(sf::RenderWindow &window);
  void init(const sf::Font &font);
  void initLevelsList(const sf::Font &font);
  void reset();
  void selectNextLevel();
  void selectPreviousLevel();
  void setFinalScoreText();
  void setLevelStrings(const int lvl_position, const sf::String lvl_info_string);
  void setLivesText(const int lives);
  void setScoreText(const unsigned long long int score);
  void setRenderFlashingTextFlag(const bool status);
  static void initText( sf::Text              &text, 
                        const sf::String      string_text, 
                        const sf::Font        &font, 
                        const int             size, 
                        const sf::Color       color, 
                        const TextCenterModes mode = Current);
  template <typename T> static void setOrigin(T &shape, const TextCenterModes mode);
  template <typename T> static std::string toString(const T &t);

 private:
  void updateFlashingTextFlag();
  void updateLevelSelectionShape(unsigned int previous_level = 0);
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
  sf::String level_info_strings_[kTotalLevels];
  sf::Text level_info_[kTotalLevels];
  sf::Text level_select_keys_;
  unsigned int level_selected_;
  sf::RectangleShape level_selected_shape_;
};

#endif  // KETE_ARKA_CLASSES_GUI_H_