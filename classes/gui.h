#ifndef KETE_ARKA_CLASSES_GUI_H_
#define KETE_ARKA_CLASSES_GUI_H_

#include <sstream>

#include "../config.h"

template <typename T> std::string toString(const T &t);

class GUI {
 public:
  GUI() {
    render_flashing_text_flag_ = true;
  }
  ~GUI() {}
  void drawGameOverScreen(sf::RenderWindow &window);
  void drawInGameGUI(sf::RenderWindow &window);
  void drawPauseScreen(sf::RenderWindow &window);
  void drawTitleScreen(sf::RenderWindow &window);
  void init(const sf::Font &font);
  void reset();
  void setFinalScoreText();
  void setLivesText(const int lives);
  void setScoreText(const unsigned long long int score);
  void setRenderFlashingTextFlag(const bool status);
  static void initText( sf::Text              &text, 
                        const sf::String      string_text, 
                        const sf::Font        &font, 
                        const int             size, 
                        const sf::Color       color, 
                        const TextCenterModes mode = Current);
  static void setTextOrigin(sf::Text &text, const TextCenterModes mode);

 private:
  void checkFlashingTextFlag();
  sf::Clock flashing_text_clock_;
  sf::Text game_over_text_;
  sf::Text level_text_;
  sf::Text lives_text_;
  sf::Text pause_text_;
  sf::Text press_any_key_text_;
  sf::Text press_start_text_;
  sf::Text title_text_;
  sf::Text score_text_;
  bool render_flashing_text_flag_;
};

#endif  // KETE_ARKA_CLASSES_GUI_H_