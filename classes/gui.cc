#include "gui.h"

/////////////////////////////////////////////////
/// @brief Checks if the render_flashing_text_flag_ needs to be updated.
///
/// Checks how much time has passed since last render.
/// If it's more than 0.7 seconds, inverts the flag for the
/// flashing text and resets the clock.
/////////////////////////////////////////////////
void GUI::checkFlashingTextFlag(){
  if (flashing_text_clock_.getElapsedTime().asSeconds() > 0.7f) {
    render_flashing_text_flag_ = !render_flashing_text_flag_;
    flashing_text_clock_.restart();
  }
}

/////////////////////////////////////////////////
/// @brief Draws the game over screen to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the game over screen on.
///
/// Draws the game over screen to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void GUI::drawGameOverScreen(sf::RenderWindow &window) {
  checkFlashingTextFlag();
  window.draw(game_over_text_);
  window.draw(score_text_);
  if (render_flashing_text_flag_) {
    window.draw(press_any_key_text_);
  }
}

/////////////////////////////////////////////////
/// @brief Draws the GUI to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the GUI on.
///
/// Draws the GUI to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void GUI::drawInGameGUI(sf::RenderWindow &window) {
  window.draw(lives_text_);
  window.draw(score_text_);
  window.draw(level_text_);
}

/////////////////////////////////////////////////
/// @brief Draws the pause text.
///
/// @param window - The sf::RenderWindow to render the "pause" text on.
///
/// Draws the pause text on the given RenderWindow.
/////////////////////////////////////////////////
void GUI::drawPauseScreen(sf::RenderWindow &window) {
  checkFlashingTextFlag();
  if (render_flashing_text_flag_) {
    window.draw(pause_text_);
  }
}

/////////////////////////////////////////////////
/// @brief Draws the game's main title and "press start" text.
///
/// @param window - The sf::RenderWindow to render the texts on.
///
/// Calls checkFlashingTextFlag before drawing
/// the game's main title and, if needed, the "press start"
/// text on the given RenderWindow.
/////////////////////////////////////////////////
void GUI::drawTitleScreen(sf::RenderWindow &window) {
  checkFlashingTextFlag();
  window.draw(title_text_);
  if (render_flashing_text_flag_) {
    window.draw(press_start_text_);
  }
}

/////////////////////////////////////////////////
/// @brief Initializes the GUI.
///
/// @param font - The sf::Font to be used.
///
/// Initializes the game title, the "press start" text and
/// the "pause" text calling the initText function with
/// the required/desired parameters (strings, sizes, ...).
/// Sets everything that needs to be set calling the methods
/// that need to be called.
/////////////////////////////////////////////////
void GUI::init(const sf::Font &font) {
  // main title
  initText(title_text_, kGameTitle, font, kGUIGameTitleFontSize, kGUIDefaultFontColor, BothAxis);
  title_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.25f);
  // press start
  initText(press_start_text_, kPressStartText, font, kGUIPressStartTextFontSize, kGUIDefaultFontColor, BothAxis);
  press_start_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.75f);
  // pause
  initText(pause_text_, kPauseText, font, kGUIPauseTextFontSize, kGUIDefaultFontColor, BothAxis);
  pause_text_.setPosition(kScreenWidth / 2.f, kScreenHeight / 2.f);
  // lives
  initText(lives_text_, kLivesText + toString(kPlayerDefaultLives), font, kGUITextFontSize, kGUIDefaultFontColor, TopLeft);
  lives_text_.setPosition(kGUIDefaultMargin, kGUIDefaultMargin);
  // score
  initText(score_text_, kScoreText + toString(0), font, kGUITextFontSize, kGUIDefaultFontColor, Horizontal);
  score_text_.setPosition(kScreenWidth / 2.f, kGUIDefaultMargin);
  // level
  initText(level_text_, kLevelText, font, kGUITextFontSize, kGUIDefaultFontColor, TopRight);
  level_text_.setPosition(kScreenWidth - kGUIDefaultMargin, kGUIDefaultMargin);
  // game over
  initText(game_over_text_, kGameOverText, font, kGUIGameOverFontSize, kGUIDefaultFontColor, BothAxis);
  game_over_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.33f);
  // press any key
  initText(press_any_key_text_, kPressAnyKeyText, font, kGUITextFontSize, kGUIDefaultFontColor, BothAxis);
  press_any_key_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.75f);
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
  setLivesText(kPlayerDefaultLives);
  score_text_.setCharacterSize(kGUITextFontSize);
  setScoreText(0);
  score_text_.setPosition(kScreenWidth / 2.f, kGUIDefaultMargin);
}

/////////////////////////////////////////////////
/// @brief Sets the score text to be displayed in the "Game Over" screen.
///
/// Sets the score text origin to the center of both axis 
/// and the text position to the middle of the screen.
/////////////////////////////////////////////////
void GUI::setFinalScoreText() {
  score_text_.setCharacterSize(kGUIPressStartTextFontSize);
  setTextOrigin(score_text_, BothAxis);
  score_text_.setPosition(kScreenWidth / 2.f, kScreenHeight / 2.f);
}

/////////////////////////////////////////////////
/// @brief Sets the lives text.
///
/// @param lives - The lives to be set.
///
/// Sets the score text with the lives provided.
/// Also re-centers the origin of the new lives text.
/////////////////////////////////////////////////
void GUI::setLivesText(const int lives) {
  lives_text_.setString(kLivesText + toString(lives));
  setTextOrigin(lives_text_, Default);
}

/////////////////////////////////////////////////
/// @brief Sets the score text.
///
/// @param score - The score to be set.
///
/// Sets the score text with the score provided.
/// Also re-centers the origin of the new score text.
/////////////////////////////////////////////////
void GUI::setScoreText(const unsigned long long int score) {
  score_text_.setString(kScoreText + toString(score));
  setTextOrigin(score_text_, Horizontal);
}

/////////////////////////////////////////////////
/// @brief Sets the render_flashing_text_flag_ to the requested status.
///
/// @param status - The desired status for the render_flashing_text_flag_.
///
/// Sets the render_flashing_text_flag_ to the requested status.
/// Resets the clock so the new status will be rendered full time.
/////////////////////////////////////////////////
void GUI::setRenderFlashingTextFlag(const bool status) {
  render_flashing_text_flag_ = status;
  flashing_text_clock_.restart();
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
      text.setOrigin(0.f, 0.f);
      break;
    case Current:
    default:
      // do nothing
      break;
  }
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