#include "gui.h"

/////////////////////////////////////////////////
/// @brief Draws the GUI to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the GUI on.
///
/// Draws the GUI to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void GUI::draw(sf::RenderWindow &window) {
  window.draw(lives_text_);
  window.draw(score_text_);
  window.draw(level_text_);
}

/////////////////////////////////////////////////
/// @brief Initializes the GUI.
///
/// @param font - The sf::Font to be used.
/// @param ptp - A pointer to the Player.
///
/// Sets everything that needs to be set calling the methods
/// that need to be called.
/////////////////////////////////////////////////
void GUI::init(const sf::Font &font, Player *ptp) {
  player_ = ptp;
  // lives
  initText(lives_text_, kLivesText, font, kGUITextFontSize, kGUIDefaultFontColor);
  setTextOrigin(lives_text_, TopLeft); // useless but the method looks weird without it
  lives_text_.setPosition(kGUIDefaultMargin, kGUIDefaultMargin);
  // score
  initText(score_text_, kScoreText + toString(player_->getScore()), font, kGUITextFontSize, kGUIDefaultFontColor);
  setTextOrigin(score_text_, Horizontal);
  score_text_.setPosition(kScreenWidth / 2.f, kGUIDefaultMargin);
  // level
  initText(level_text_, kLevelText, font, kGUITextFontSize, kGUIDefaultFontColor);
  setTextOrigin(level_text_, TopRight);
  level_text_.setPosition(kScreenWidth - kGUIDefaultMargin, kGUIDefaultMargin);
}

/////////////////////////////////////////////////
/// @brief Initializes a given text.
///
/// @param text - The address of the sf::Text to be initialized.
/// @param string_text - The literal sf::String of characters to be rendered.
/// @param font - The sf::Font to be used.
/// @param size - The desired size (integer) of the rendered text.
/// @param color - The desired sf::Color for the text.
/// @param mode - TextCenterMode to be applied. Default is current (none).
///
/// Sets the font, the size, the fill color and the string to be
/// rendered for the text. Thereafter sets the origin of the text if needed.
/////////////////////////////////////////////////
void GUI::initText( sf::Text              &text, 
                    const sf::String      string_text, 
                    const sf::Font        &font, 
                    const int             size,
                    const sf::Color       color, 
                    const TextCenterModes mode ) {
  text.setFont(font);
  text.setCharacterSize(size);
  text.setFillColor(color);
  text.setString(string_text);
  if (mode != Current) {
    setTextOrigin(text, mode);
  }
}

/////////////////////////////////////////////////
/// @brief Resets the GUI elements.
///
/// Resets the GUI elements to their initial states.
/////////////////////////////////////////////////
void GUI::reset() {
  level_text_.setString(kLevelText);
  lives_text_.setString(kLivesText);
  updateScoreText();
}

/////////////////////////////////////////////////
/// @brief Sets the origin of a sf::Text as requested.
///
/// @param text - The sf::Text to be changed.
/// @param mode - The TextCenterModes to be used.
///
/// Sets the origin of a sf::Text as requested. Options are:
/// Horizontal, Vertical, BothAxis, TopRight, TopLeft, Default and Current.
/////////////////////////////////////////////////
void GUI::setTextOrigin(sf::Text &text, const TextCenterModes mode) {
  sf::FloatRect text_rect = text.getLocalBounds();
  switch (mode) {
    case Horizontal:
      text.setOrigin(text_rect.left + (text_rect.width / 2.f), text_rect.top);
      break;
    case Vertical:
      text.setOrigin(text_rect.left, text_rect.top + (text_rect.height / 2.f));
      break;
    case BothAxis:
      text.setOrigin(text_rect.left + (text_rect.width / 2.f), text_rect.top + (text_rect.height / 2.f));
      break;
    case TopRight:
      text.setOrigin(text_rect.left + text_rect.width, text_rect.top);
      break;
    case TopLeft:
    case Default:
      text.setOrigin(0, 0);
      break;
    case Current:
    default:
      // do nothing
      break;
  }
}

/////////////////////////////////////////////////
/// @brief Updates the score text.
///
/// Updates the score text by reading the current score of the player.
/// Also re-centers the origin of the new score text.
/////////////////////////////////////////////////
void GUI::updateScoreText() {
  score_text_.setString(kScoreText + toString(player_->getScore()));
  setTextOrigin(score_text_, Horizontal);
}

/////////////////////////////////////////////////
/// @brief "Stringifyes" the parameter.
///
/// @param t - The thing to be converted into a std::string.
///
/// @return - A std::string (hopefully) closely related to the parameter.
///
/// Converts the parameter t into a std::string and returns it.
/////////////////////////////////////////////////
template <typename T> std::string toString(const T &t) { 
  std::ostringstream oss;
  oss << t; 
  return oss.str();
}