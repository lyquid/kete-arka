#include "gui.h"

///
void GUI::drawGameCompleted(sf::RenderWindow &window) {
  window.draw(game_completed_);
  updateFlashingTextFlag();
  if (render_flashing_text_flag_) {
    window.draw(press_any_key_text_);
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
  window.draw(game_over_text_);
  window.draw(total_score_text_);
  updateFlashingTextFlag();
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
  window.draw(gui_lives_text_);
  window.draw(gui_score_text_);
  window.draw(gui_level_text_);
}

///
void GUI::drawLevelCompletedScreen(sf::RenderWindow &window) {
  window.draw(level_completed_title_);
  window.draw(total_score_text_);
  updateFlashingTextFlag();
  if (render_flashing_text_flag_) {
    window.draw(level_completed_continue_);
  }
}

/////////////////////////////////////////////////
/// @brief Draws the level selection menu to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the level selection menu on.
///
/// Draws the level selection menu to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void GUI::drawLevelSelection(sf::RenderWindow &window) {
  window.draw(level_select_title_text_);
  window.draw(level_selected_shape_);
  for (int i = 0; i < kMaxLevels; ++i) {
    window.draw(level_info_[i]);
  }
  window.draw(level_select_keys_);
}

/////////////////////////////////////////////////
/// @brief Draws the menu to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the menu on.
///
/// Draws the menu to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void GUI::drawMenu(sf::RenderWindow &window) {
  window.draw(title_text_);
  window.draw(menu_start_text_);
  window.draw(menu_level_text_);
  window.draw(menu_quit_text_);
}

/////////////////////////////////////////////////
/// @brief Draws the pause text.
///
/// @param window - The sf::RenderWindow to render the "pause" text on.
///
/// Draws the pause text on the given RenderWindow.
/////////////////////////////////////////////////
void GUI::drawPauseScreen(sf::RenderWindow &window) {
  updateFlashingTextFlag();
  if (render_flashing_text_flag_) {
    window.draw(pause_text_);
  }
}

/////////////////////////////////////////////////
/// @brief Draws the game's main title and "press start" text.
///
/// @param window - The sf::RenderWindow to render the texts on.
///
/// Calls updateFlashingTextFlag before drawing
/// the game's main title and, if needed, the "press start"
/// text on the given RenderWindow.
/////////////////////////////////////////////////
void GUI::drawTitleScreen(sf::RenderWindow &window) {
  window.draw(title_text_);
  updateFlashingTextFlag();
  if (render_flashing_text_flag_) {
    window.draw(press_start_text_);
  }
}

/////////////////////////////////////////////////
/// @brief Returns the selected level's number.
///
/// @return window - An integer representing the level selected.
///
/// Returns the selected level's number.
/// Caution: level number != level index in levels array.
/////////////////////////////////////////////////
int GUI::getLevelSelectedNumber() {
  return level_selected_ + 1;
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
  const int halfScreenW = kScreenWidth / 2;
  // main title
  initText(title_text_, kGameTitle, font, kGUIGameTitleFontSize, kGUIDefaultFontColor, BothAxis);
  title_text_.setPosition(halfScreenW, (float)kScreenHeight * 0.25f);
  // press start
  initText(press_start_text_, kPressStartText, font, kGUIPressStartTextFontSize, kGUIDefaultFontColor, BothAxis);
  press_start_text_.setPosition(halfScreenW, (float)kScreenHeight * 0.75f);
  // pause
  initText(pause_text_, kPauseText, font, kGUIPauseTextFontSize, kGUIDefaultFontColor, BothAxis);
  pause_text_.setPosition(halfScreenW, (float)kScreenHeight / 2.f);
  // game over
  initText(game_over_text_, kGameOverText, font, kGUIGameOverFontSize, kGUIDefaultFontColor, BothAxis);
  game_over_text_.setPosition(halfScreenW, (float)kScreenHeight * 0.33f);
  // press any key
  initText(press_any_key_text_, kContinueText, font, kGUITextFontSize, kGUIDefaultFontColor, BothAxis);
  press_any_key_text_.setPosition(halfScreenW, (float)kScreenHeight * 0.75f);
  // total score
  initText(total_score_text_, kTotalScoreText, font, kGUIPressStartTextFontSize, kGUIDefaultFontColor, BothAxis);
  total_score_text_.setPosition(halfScreenW, kScreenHeight / 2);
  // MENU - level selection
  initText(menu_level_text_, kMenuLevelText, font, kGUIMenuItemFontSize, kGUIDefaultFontColor, Horizontal);
  menu_level_text_.setPosition(halfScreenW, (float)kScreenHeight * 0.66f + kGUIMenuItemFontSize * 2.f);
  // MENU - start
  initText(menu_start_text_, kMenuStartText, font, kGUIMenuItemFontSize, kGUIDefaultFontColor);
  menu_start_text_.setPosition(menu_level_text_.getGlobalBounds().left - 4.f, (float)kScreenHeight * 0.66f);
  // MENU - exit
  initText(menu_quit_text_, kMenuQuitText, font, kGUIMenuItemFontSize, kGUIDefaultFontColor);
  menu_quit_text_.setPosition(menu_level_text_.getGlobalBounds().left - 4.f, (float)kScreenHeight * 0.66f + kGUIMenuItemFontSize * 4.f);
  // GUI - lives
  initText(gui_lives_text_, kGUILivesText + toString(kPlayerDefaultLives), font, kGUITextFontSize, kGUIDefaultFontColor, TopLeft);
  gui_lives_text_.setPosition(kGUIDefaultMargin + kGUIBorderThickness, kScreenHeight - kGUIDefaultMargin - kGUITextFontSize);
  // GUI - score
  initText(gui_score_text_, kGUIScoreText + toString(0), font, kGUITextFontSize, kGUIDefaultFontColor, Horizontal);
  gui_score_text_.setPosition(halfScreenW, kScreenHeight - kGUIDefaultMargin - kGUITextFontSize);
  // GUI - level
  initText(gui_level_text_, kGUILevelText, font, kGUITextFontSize, kGUIDefaultFontColor, TopRight);
  gui_level_text_.setPosition((float)kScreenWidth - kGUIDefaultMargin - kGUIBorderThickness, kScreenHeight - kGUIDefaultMargin - kGUITextFontSize);
  // LEVEL SELECTION - levels list
  initLevelsList(font);
  // LEVEL SELECTION - key guide
  initText(level_select_keys_, kLevelSelectKeys, font, kGUILevelSelectKeys, kGUIDefaultFontColor, Horizontal);
  level_select_keys_.setPosition(halfScreenW, static_cast<int>(kScreenHeight - kGUILevelSelectKeys));
  // LEVEL COMPLETED
  initText(level_completed_title_, kLevelCompletedText, font, kGUIGameOverFontSize, kGUIDefaultFontColor, BothAxis);
  level_completed_title_.setPosition(halfScreenW, (float)kScreenHeight * 0.25f);
  // LEVEL COMPLETED - CONTINUE
  initText(level_completed_continue_, kPressSpaceText, font, kGUITextFontSize, kGUIDefaultFontColor, BothAxis);
  level_completed_continue_.setPosition(halfScreenW, (float)kScreenHeight * 0.75f);
  // GAME COMPLETED
  initText(game_completed_, kGameCompletedText, font,  kGUIGameOverFontSize, kGUIDefaultFontColor, BothAxis);
  game_completed_.setPosition(halfScreenW, (float)kScreenHeight / 2.f);
}

/////////////////////////////////////////////////
/// @brief Initializes the level selection list.
///
/// @param font - The sf::Font to be used.
///
/// Initializes and sets the position of the texts for 
/// the level selection screen.
///
/// @todo: Fix the bug with the position of the texts.
/////////////////////////////////////////////////
void GUI::initLevelsList(const sf::Font &font) {
  const int x = kScreenWidth / 2;
  int y = kGUIDefaultMargin + kGUILevelSelectFontSize / 2;
  initText(level_select_title_text_, kLevelSelectText, font, kGUILevelSelectFontSize, kGUIDefaultFontColor, BothAxis);
  level_select_title_text_.setPosition(x, y);
  for (int i = 0; i < kMaxLevels; ++i) {
    y = (kGUIDefaultMargin + kGUILevelSelectKeys * 2) + (kGUILevelSelectKeys * (i + 1)) + (8 * i);
    initText(level_info_[i], level_info_strings_[i], font, kGUILevelSelectKeys, kGUIDefaultFontColor, BothAxis);
    level_info_[i].setPosition(x, y);
  }
  level_selected_ = 0;
  level_selected_shape_.setFillColor(kGUIDefaultFontColor);
  updateLevelSelectionShape();
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
  text.setOutlineColor(kGUIDefaultFontOutlineColor);
  text.setOutlineThickness(kGUIDefaultFontOutline);
  setOrigin(text, mode);
}

/////////////////////////////////////////////////
/// @brief Resets the GUI elements.
///
/// Resets the GUI elements to their initial states.
/////////////////////////////////////////////////
void GUI::reset() {
  setLivesText(kPlayerDefaultLives);
  gui_score_text_.setCharacterSize(kGUITextFontSize);
  setScoreText(0);
  gui_score_text_.setPosition(kScreenWidth / 2.f, kScreenHeight - kGUIDefaultMargin - kGUITextFontSize);
}

/////////////////////////////////////////////////
/// @brief Changes selected level to the next.
///
/// Changes selected level to the next. I there's no next level, 
/// level selected becomes the first (0). 
/// Also updates the selection shape by calling updateLevelSelectionShape().
/////////////////////////////////////////////////
void GUI::selectNextLevel() {
  if (level_selected_ >= kMaxLevels - 1) {
    level_selected_ = 0;
    updateLevelSelectionShape(kMaxLevels - 1);
  } else {
    level_selected_++;
    updateLevelSelectionShape(level_selected_ - 1);
  }
}

/////////////////////////////////////////////////
/// @brief Changes selected level to the previous.
///
/// Changes selected level to the previous. I there's no previous level, 
/// level selected becomes the last. 
/// Also updates the selection shape by calling updateLevelSelectionShape().
/////////////////////////////////////////////////
void GUI::selectPreviousLevel() {
  if (level_selected_ <= 0) {
    level_selected_ = kMaxLevels - 1;
    updateLevelSelectionShape(0);
  } else {
    level_selected_--;
    updateLevelSelectionShape(level_selected_ + 1);
  }
}

/////////////////////////////////////////////////
/// @brief Sets the score text to be displayed in the "Game Over" screen.
///
/// Sets the score text origin to the center of both axis 
/// and the text position to the middle of the screen.
/////////////////////////////////////////////////
void GUI::setFinalScoreText(unsigned long long int score) {
  total_score_text_.setString(kTotalScoreText + toString(score));
  setOrigin(total_score_text_, BothAxis);
}

/////////////////////////////////////////////////
/// @brief Sets level info strings into local array level_info_strings_.
///
/// @param lvl_position - The position (int) of the level in the array.
/// @param lvl_info_string - The sf::String containing the level info.
///
/// Sets level info strings into local array level_info_strings_, which 
/// is later used for creating the menu selection list.
/// The position is usually the level number minus 1 and the string is 
/// usually the number and name of the level combined (ie. "01 - first_lvl").
/////////////////////////////////////////////////
void GUI::setLevelStrings(const int lvl_position, const sf::String lvl_info_string) {
  level_info_strings_[lvl_position] = lvl_info_string;
}

/////////////////////////////////////////////////
/// @brief Sets the level text.
///
/// @param level_num - The level (int) to be set.
///
/// Sets the level text with the level provided.
/// Also re-centers the origin of the new level text.
/////////////////////////////////////////////////
void GUI::setLevelText(int level_num) {
  level_num > 9 ?
    gui_level_text_.setString(kGUILevelText + toString(level_num))
    : gui_level_text_.setString(kGUILevelText + "0" + toString(level_num));
  setOrigin(gui_level_text_, TopRight);
}

/////////////////////////////////////////////////
/// @brief Sets the lives text.
///
/// @param lives - The lives (int) to be set.
///
/// Sets the lives text with the lives provided.
/// Also re-centers the origin of the new lives text.
/////////////////////////////////////////////////
void GUI::setLivesText(const int lives) {
  gui_lives_text_.setString(kGUILivesText + toString(lives));
  setOrigin(gui_lives_text_, Default);
}

/////////////////////////////////////////////////
/// @brief Sets the score text.
///
/// @param score - The score (big int) to be set.
///
/// Sets the score text with the score provided.
/// Also re-centers the origin of the new score text.
/////////////////////////////////////////////////
void GUI::setScoreText(const unsigned long long int score) {
  gui_score_text_.setString(kGUIScoreText + toString(score));
  setOrigin(gui_score_text_, Horizontal);
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
/// @param shape - The sf::Text to be changed.
/// @param mode - The TextCenterModes to be used.
///
/// Sets the origin of a sf::Text as requested. Options are:
/// Horizontal, Vertical, BothAxis, TopRight, TopLeft, Default and Current.
/////////////////////////////////////////////////
template <typename T> void GUI::setOrigin(T &shape, const TextCenterModes mode) {
  sf::FloatRect shape_rect = shape.getLocalBounds();
  switch (mode) {
    case Horizontal:
      shape.setOrigin(shape_rect.left + (shape_rect.width / 2.f), shape_rect.top);
      break;
    case Vertical:
      shape.setOrigin(shape_rect.left, shape_rect.top + (shape_rect.height / 2.f));
      break;
    case BothAxis:
      shape.setOrigin(shape_rect.left + (shape_rect.width / 2.f), shape_rect.top + (shape_rect.height / 2.f));
      break;
    case TopRight:
      shape.setOrigin(shape_rect.left + shape_rect.width, shape_rect.top);
      break;
    case TopLeft:
    case Default:
      shape.setOrigin(0.f, 0.f);
      break;
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
template <typename T> std::string GUI::toString(const T &t) { 
  std::ostringstream oss;
  oss << t; 
  return oss.str();
}

/////////////////////////////////////////////////
/// @brief Checks if the render_flashing_text_flag_ needs to be updated.
///
/// Checks how much time has passed since last render.
/// If it's more than 0.7 seconds, inverts the flag for the
/// flashing text and resets the clock.
/////////////////////////////////////////////////
void GUI::updateFlashingTextFlag(){
  if (flashing_text_clock_.getElapsedTime().asSeconds() > 0.7f) {
    render_flashing_text_flag_ = !render_flashing_text_flag_;
    flashing_text_clock_.restart();
  }
}

/////////////////////////////////////////////////
/// @brief Updates the selection shape accordingly.
///
/// @param previous_level - The previous selected level.
///
/// Changes the previously selected level to it's original state (color)
/// and the newly selected level to the selected color and adjusts the 
/// selection shape to fit the new selection.
/////////////////////////////////////////////////
void GUI::updateLevelSelectionShape(int previous_level) {
  level_info_[previous_level].setFillColor(kGUIDefaultFontColor);
  level_info_[previous_level].setOutlineThickness(kGUIDefaultFontOutline);
  level_info_[level_selected_].setFillColor(kGUIDefaultSelectedFontColor);
  level_info_[level_selected_].setOutlineThickness(0);
  level_selected_shape_.setSize(sf::Vector2f(level_info_[level_selected_].getGlobalBounds().width, level_info_[level_selected_].getGlobalBounds().height));
  setOrigin(level_selected_shape_, BothAxis);
  level_selected_shape_.setPosition(level_info_[level_selected_].getPosition());
}

