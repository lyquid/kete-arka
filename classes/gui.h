#ifndef KETE_ARKA_CLASSES_GUI_H_
#define KETE_ARKA_CLASSES_GUI_H_

#include <sstream>

#include "../config.h"

template <typename T> std::string toString(const T &t);

class GUI {
 public:
  GUI() {}
  ~GUI() {}
  void draw(sf::RenderWindow &window);
  void init(const sf::Font &font);
  void reset();
  void setLivesText(int lives);
  void setScoreText(unsigned long long int score);
  static void initText( sf::Text              &text, 
                        const sf::String      string_text, 
                        const sf::Font        &font, 
                        const int             size, 
                        const sf::Color       color, 
                        const TextCenterModes mode = Current);
  static void setTextOrigin(sf::Text &text, const TextCenterModes mode);
 private:
  sf::Text level_text_;
  sf::Text lives_text_;
  sf::Text score_text_;
};

#endif  // KETE_ARKA_CLASSES_GUI_H_