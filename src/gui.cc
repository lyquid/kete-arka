#include "gui.h"

const sf::Color GUI::kGUIDefaultFontColor_         = sf::Color::White;
const sf::Color GUI::kGUIDefaultSelectedFontColor_ = sf::Color::Black;
const sf::Color GUI::kGUIDefaultFontOutlineColor_  = sf::Color::Black;

///
void GUI::drawGameCompleted(sf::RenderWindow& window) {
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
void GUI::drawGameOverScreen(sf::RenderWindow& window) {
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
void GUI::drawInGameGUI(sf::RenderWindow& window) {
  window.draw(gui_lives_text_);
  window.draw(gui_score_text_);
  window.draw(gui_level_text_);
}

///
void GUI::drawLevelCompletedScreen(sf::RenderWindow& window) {
  window.draw(level_completed_title_);
  window.draw(level_completed_name_);
  window.draw(total_score_text_);
  if (current_level_ < k::kMaxLevels) {
    window.draw(level_completed_next_);
    window.draw(level_completed_next_name_);
  }
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
void GUI::drawLevelSelection(sf::RenderWindow& window) {
  window.draw(level_select_title_text_);
  window.draw(level_selected_shape_);
  for (const auto& level_info: level_info_texts_)
    window.draw(level_info);
  window.draw(level_select_keys_);
}

/////////////////////////////////////////////////
/// @brief Draws the menu to the specified sf::RenderWindow.
///
/// @param window - The sf::RenderWindow to draw the menu on.
///
/// Draws the menu to the specified sf::RenderWindow.
/////////////////////////////////////////////////
void GUI::drawMenu(sf::RenderWindow& window) {
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
void GUI::drawPauseScreen(sf::RenderWindow& window) {
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
void GUI::drawTitleScreen(sf::RenderWindow& window) {
  window.draw(title_text_);
  updateFlashingTextFlag();
  if (render_flashing_text_flag_) {
    window.draw(press_start_text_);
  }
}

GUI::GUI(): current_level_(0u),
            render_flashing_text_flag_(true) {
  level_info_.resize(k::kMaxLevels);
  level_info_texts_.resize(k::kMaxLevels);
  assert(level_info_.size() == level_info_texts_.size());
}

/////////////////////////////////////////////////
/// @brief Initializes the GUI.
///
/// Initializes the game title, the "press start" text and
/// the "pause" text calling the initText function with
/// the required/desired parameters (strings, sizes, ...).
/// Sets everything that needs to be set calling the methods
/// that need to be called.
/////////////////////////////////////////////////
void GUI::init() {
  if (!font_.loadFromFile("assets/PressStart2P.ttf")) {
    exit(EXIT_FAILURE);
  }
  constexpr auto halfScreenW = k::kScreenWidth / 2u;
  // main title
  initText(title_text_, k::kGameTitle, font_, kGUIGameTitleFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  title_text_.setPosition(halfScreenW, k::kScreenHeight * 0.25f);
  // press start
  initText(press_start_text_, kPressStartText_, font_, kGUIPressStartTextFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  press_start_text_.setPosition(halfScreenW, k::kScreenHeight * 0.75f);
  // pause
  initText(pause_text_, kPauseText_, font_, kGUIPauseTextFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  pause_text_.setPosition(halfScreenW, k::kScreenHeight / 2.f);
  // game over
  initText(game_over_text_, kGameOverText_, font_, kGUIGameOverFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  game_over_text_.setPosition(halfScreenW, k::kScreenHeight * 0.33f);
  // press any key
  initText(press_any_key_text_, kContinueText_, font_, kGUITextFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  press_any_key_text_.setPosition(halfScreenW, k::kScreenHeight * 0.75f);
  // MENU - level selection
  initText(menu_level_text_, kMenuLevelText_, font_, kGUIMenuItemFontSize_, kGUIDefaultFontColor_, TextCenter::Horizontal);
  menu_level_text_.setPosition(halfScreenW, k::kScreenHeight * 0.66f + kGUIMenuItemFontSize_ * 2.f);
  // MENU - start
  initText(menu_start_text_, kMenuStartText_, font_, kGUIMenuItemFontSize_, kGUIDefaultFontColor_);
  menu_start_text_.setPosition(menu_level_text_.getGlobalBounds().left - 4.f, k::kScreenHeight * 0.66f);
  // MENU - exit
  initText(menu_quit_text_, kMenuQuitText_, font_, kGUIMenuItemFontSize_, kGUIDefaultFontColor_);
  menu_quit_text_.setPosition(menu_level_text_.getGlobalBounds().left - 4.f, k::kScreenHeight * 0.66f + kGUIMenuItemFontSize_ * 4.f);
  // GUI - lives
  initText(gui_lives_text_, kGUILivesText_ + std::string(""), font_, kGUITextFontSize_, kGUIDefaultFontColor_, TextCenter::TopLeft);
  gui_lives_text_.setPosition(kGUIDefaultMargin_ + k::kGUIBorderThickness, k::kScreenHeight - kGUIDefaultMargin_ - kGUITextFontSize_);
  // GUI - score
  initText(gui_score_text_, kGUIScoreText_ + std::to_string(0), font_, kGUITextFontSize_, kGUIDefaultFontColor_, TextCenter::Horizontal);
  gui_score_text_.setPosition(halfScreenW, k::kScreenHeight - kGUIDefaultMargin_ - kGUITextFontSize_);
  // GUI - level
  initText(gui_level_text_, kGUILevelText_, font_, kGUITextFontSize_, kGUIDefaultFontColor_, TextCenter::TopRight);
  gui_level_text_.setPosition(k::kScreenWidth - kGUIDefaultMargin_ - k::kGUIBorderThickness, k::kScreenHeight - kGUIDefaultMargin_ - kGUITextFontSize_);
  // LEVEL SELECTION - levels list
  initLevelsList();
  // LEVEL SELECTION - key guide
  initText(level_select_keys_, kLevelSelectKeys_, font_, kGUILevelSelectKeys_, kGUIDefaultFontColor_, TextCenter::Horizontal);
  level_select_keys_.setPosition(halfScreenW, k::kScreenHeight - kGUILevelSelectKeys_);
  // LEVEL COMPLETED - Title
  initText(level_completed_title_, kLevelCompletedText_, font_, kGUILevelCompletedFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  level_completed_title_.setPosition(halfScreenW, k::kScreenHeight * 0.25f);
  // LEVEL COMPLETED - Level name
  initText(level_completed_name_, "", font_, kGUILevelCompletedFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  // LEVEL COMPLETED - Total score
  initText(total_score_text_, kTotalScoreText_, font_, kGUILevelCompletedFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  total_score_text_.setPosition(halfScreenW, k::kScreenHeight * 0.40f);
  // LEVEL COMPLETED - Next
  initText(level_completed_next_, kLevelCompletedNext_, font_, kGUIPressStartTextFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  level_completed_next_.setPosition(halfScreenW, k::kScreenHeight * 0.70f);
  // LEVEL COMPLETED - Next name
  initText(level_completed_next_name_, "", font_, kGUIPressStartTextFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  // LEVEL COMPLETED - Continue
  initText(level_completed_continue_, kPressSpaceText_, font_, kGUITextFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  level_completed_continue_.setPosition(halfScreenW, k::kScreenHeight * 0.85f);
  // GAME COMPLETED
  initText(game_completed_, kGameCompletedText_, font_,  kGUIGameOverFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  game_completed_.setPosition(halfScreenW, k::kScreenHeight / 2.f);
}

/////////////////////////////////////////////////
/// @brief Initializes the level selection list.
///
/// Initializes and sets the position of the texts for 
/// the level selection screen.
///
/// @todo: Fix the bug with the position of the texts.
/////////////////////////////////////////////////
void GUI::initLevelsList() {
  constexpr auto x = k::kScreenWidth / 2u;
  auto y = kGUIDefaultMargin_ + kGUILevelSelectFontSize_ / 2u;
  initText(level_select_title_text_, kLevelSelectText_, font_, kGUILevelSelectFontSize_, kGUIDefaultFontColor_, TextCenter::BothAxis);
  level_select_title_text_.setPosition(x, y);
  for (auto i = 0u; i < level_info_.size(); ++i) {
    initText(level_info_texts_.at(i), level_info_.at(i).select_text, font_, kGUILevelSelectKeys_, kGUIDefaultFontColor_, TextCenter::BothAxis);
    y = (kGUIDefaultMargin_ + kGUILevelSelectKeys_ * 2u) + (kGUILevelSelectKeys_ * (i + 1u)) + (8u * i);
    level_info_texts_.at(i).setPosition(x, y);
  }
  level_selected_ = 0u;
  level_selected_shape_.setFillColor(kGUIDefaultFontColor_);
  updateLevelSelectionShape();
}

/////////////////////////////////////////////////
/// @brief Initializes a given text.
///
/// @param text - The address of the sf::Text to be initialized.
/// @param string_text - The literal std::string of characters to be rendered.
/// @param font - The sf::Font to be used.
/// @param size - The desired size (integer) of the rendered text.
/// @param color - The desired sf::Color for the text.
/// @param mode - TextCenterMode to be applied. Default is current (none).
///
/// Sets the font, the size, the fill color and the string to be
/// rendered for the text. Thereafter sets the origin of the text if needed.
/////////////////////////////////////////////////
void GUI::initText(sf::Text&          text, 
                   const std::string& string_text, 
                   const sf::Font&    font, 
                   unsigned int       size,
                   const sf::Color&   color, 
                   const TextCenter&  mode ) {
  text.setFont(font);
  text.setCharacterSize(size);
  text.setFillColor(color);
  text.setString(string_text);
  text.setOutlineColor(kGUIDefaultFontOutlineColor_);
  text.setOutlineThickness(kGUIDefaultFontOutline_);
  setOrigin(text, mode);
}

/////////////////////////////////////////////////
/// @brief Resets the GUI elements.
///
/// Resets the GUI elements to their initial states.
/////////////////////////////////////////////////
void GUI::reset() {
  // setLivesText(kPlayerDefaultLives);
  // setLivesText(0);
  gui_score_text_.setCharacterSize(kGUITextFontSize_);
  setScoreText(0u);
  gui_score_text_.setPosition(k::kScreenWidth / 2.f, k::kScreenHeight - kGUIDefaultMargin_ - kGUITextFontSize_);
}

/////////////////////////////////////////////////
/// @brief Changes selected level to the next.
///
/// Changes selected level to the next. I there's no next level, 
/// level selected becomes the first (0). 
/// Also updates the selection shape by calling updateLevelSelectionShape().
/////////////////////////////////////////////////
void GUI::selectNextLevel() {
  if (level_selected_ >= k::kMaxLevels - 1u) {
    level_selected_ = 0u;
    updateLevelSelectionShape(k::kMaxLevels - 1u);
  } else {
    ++level_selected_;
    updateLevelSelectionShape(level_selected_ - 1u);
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
  if (level_selected_ <= 0u) {
    level_selected_ = k::kMaxLevels - 1u;
    updateLevelSelectionShape(0u);
  } else {
    --level_selected_;
    updateLevelSelectionShape(level_selected_ + 1u);
  }
}

/////////////////////////////////////////////////
/// @brief Sets the score text to be displayed in the "Game Over" screen.
///
/// Sets the score text origin to the center of both axis 
/// and the text position to the middle of the screen.
/////////////////////////////////////////////////
void GUI::setFinalScoreText(unsigned long long int score) {
  total_score_text_.setString(kTotalScoreText_ + std::to_string(score));
  setOrigin(total_score_text_, TextCenter::BothAxis);
}

/////////////////////////////////////////////////
/// @brief Sets level info strings into local array level_info_strings_.
///
/// @param lvl_position - The position (int) of the level in the array.
/// @param lvl_num - An int containing the level number.
/// @param lvl_name - The sf::String containing the level name.
///
/////////////////////////////////////////////////
void GUI::setLevelInfo(unsigned int lvl_position, unsigned int lvl_num, const std::string& lvl_name) {
  level_info_.at(lvl_position).number = lvl_num;
  level_info_.at(lvl_position).name = lvl_name;
  if (lvl_num < 10u) {
    level_info_.at(lvl_position).select_text = "0" + std::to_string(lvl_num) + " - " + lvl_name;
  } else {
    level_info_.at(lvl_position).select_text = std::to_string(lvl_num) + " - " + lvl_name;
  }
}

/////////////////////////////////////////////////
/// @brief Sets the lives text.
///
/// @param lives - The lives (int) to be set.
///
/// Sets the lives text with the lives provided.
/// Also re-centers the origin of the new lives text.
/////////////////////////////////////////////////
void GUI::setLivesText(unsigned int lives) {
  gui_lives_text_.setString(kGUILivesText_ + std::to_string(lives));
  setOrigin(gui_lives_text_, TextCenter::Default);
}

/////////////////////////////////////////////////
/// @brief Sets the score text.
///
/// @param score - The score (big int) to be set.
///
/// Sets the score text with the score provided.
/// Also re-centers the origin of the new score text.
/////////////////////////////////////////////////
void GUI::setScoreText(unsigned long long score) {
  gui_score_text_.setString(kGUIScoreText_ + std::to_string(score));
  setOrigin(gui_score_text_, TextCenter::Horizontal);
}

/////////////////////////////////////////////////
/// @brief Sets the render_flashing_text_flag_ to the requested status.
///
/// @param status - The desired status for the render_flashing_text_flag_.
///
/// Sets the render_flashing_text_flag_ to the requested status.
/// Resets the clock so the new status will be rendered full time.
/////////////////////////////////////////////////
void GUI::setRenderFlashingTextFlag(bool status) {
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
template<typename T> void GUI::setOrigin(T& shape, TextCenter mode) {
  const auto shape_rect = shape.getLocalBounds();
  switch (mode) {
    case TextCenter::Horizontal:
      shape.setOrigin(shape_rect.left + (shape_rect.width / 2.f), shape_rect.top);
      break;
    case TextCenter::Vertical:
      shape.setOrigin(shape_rect.left, shape_rect.top + (shape_rect.height / 2.f));
      break;
    case TextCenter::BothAxis:
      shape.setOrigin(shape_rect.left + (shape_rect.width / 2.f), shape_rect.top + (shape_rect.height / 2.f));
      break;
    case TextCenter::TopRight:
      shape.setOrigin(shape_rect.left + shape_rect.width, shape_rect.top);
      break;
    case TextCenter::TopLeft:
    case TextCenter::Default:
      shape.setOrigin(0.f, 0.f);
      break;
    default:
      break;
  }
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

void GUI::update(unsigned int lvl_num, const std::string& lvl_name) {
  current_level_ = lvl_num;
  
  level_completed_name_.setString("\"" + lvl_name + "\"");
  setOrigin(level_completed_name_, TextCenter::BothAxis);
  level_completed_name_.setPosition(k::kScreenWidth * 0.5f, k::kScreenHeight * 0.30f);

  lvl_num > 9u ?
    gui_level_text_.setString(kGUILevelText_ + std::to_string(lvl_num))
    : gui_level_text_.setString(kGUILevelText_ + std::string("0") + std::to_string(lvl_num));
  setOrigin(gui_level_text_, TextCenter::TopRight);
}

void GUI::update(unsigned int lvl_num, const std::string& lvl_name, const std::string& next_lvl_name) {
  current_level_ = lvl_num;

  level_completed_name_.setString("\"" + lvl_name + "\"");
  setOrigin(level_completed_name_, TextCenter::BothAxis);
  level_completed_name_.setPosition(k::kScreenWidth * 0.5f, k::kScreenHeight * 0.30f);

  level_completed_next_name_.setString("\"" + next_lvl_name + "\"");
  setOrigin(level_completed_next_name_, TextCenter::BothAxis);
  level_completed_next_name_.setPosition(k::kScreenWidth * 0.5f, k::kScreenHeight * 0.75f);

  lvl_num > 9u ?
    gui_level_text_.setString(kGUILevelText_ + std::to_string(lvl_num))
    : gui_level_text_.setString(kGUILevelText_ + std::string("0") + std::to_string(lvl_num));
  setOrigin(gui_level_text_, TextCenter::TopRight);
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
void GUI::updateLevelSelectionShape(unsigned int previous_level) {
  level_info_texts_.at(previous_level).setFillColor(kGUIDefaultFontColor_);
  level_info_texts_.at(previous_level).setOutlineThickness(kGUIDefaultFontOutline_);
  level_info_texts_.at(level_selected_).setFillColor(kGUIDefaultSelectedFontColor_);
  level_info_texts_.at(level_selected_).setOutlineThickness(0.f);
  level_selected_shape_.setSize(sf::Vector2f(level_info_texts_.at(level_selected_).getGlobalBounds().width, level_info_texts_.at(level_selected_).getGlobalBounds().height));
  setOrigin(level_selected_shape_, TextCenter::BothAxis);
  level_selected_shape_.setPosition(level_info_texts_.at(level_selected_).getPosition());
}

