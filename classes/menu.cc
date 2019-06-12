#include "menu.h"

/////////////////////////////////////////////////
/// @brief Draws the pause text.
///
/// @param window The renderWindow to render the "pause" text on.
///
/// Draws the pause text on the given RenderWindow.
/////////////////////////////////////////////////
void Menu::drawPauseScreen(sf::RenderWindow* window) {
  window->draw(pause_text_);
}

/////////////////////////////////////////////////
/// @brief Draws the game's main title and "press start" text.
///
/// @param window The renderWindow to render the texts on.
///
/// Calls setFlashingPressStartText before drawing
/// the game's main title and, if needed, the "press start"
/// text on the given renderWindow.
/////////////////////////////////////////////////
void Menu::drawTitleScreen(sf::RenderWindow* window) {
  setFlashingPressStartText();
  window->draw(title_text_);
  if (render_press_start_text_) {
    window->draw(press_start_text_);
  }
}

/////////////////////////////////////////////////
/// @brief Initializes various texts.
///
/// @param font The font to be used by the texts.
///
/// Initializes the game title, the "press start" text and
/// the "pause" text calling the initText function with
/// the required/desired parameters (strings, sizes, ...).
/////////////////////////////////////////////////
void Menu::init(const sf::Font* font) {
  // main title
  initText(&title_text_, kGameTitle, font, kGameTitleFontSize);
  title_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.25f);
  // press start text
  initText(&press_start_text_, kPressStartText, font, kPressStartTextFontSize);
  press_start_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.75f);
  // pause text
  initText(&pause_text_, kPauseText, font, kPauseTextFontSize);
  pause_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.5f);
}

/////////////////////////////////////////////////
/// @brief Initializes a given text.
///
/// @param text The address of the text to be initialized.
/// @param string_text The literal string of characters to be rendered.
/// @param font The font to be used.
/// @param size The desired size of the rendered text.
///
/// Sets the font, the size, the fill color and the string to be
/// rendered for the text. Thereafter sets the origin of the text
/// to be at the half of both height and width (the "center").
/////////////////////////////////////////////////
void Menu::initText(sf::Text* text, const sf::String string_text, const sf::Font* font, const int size) {
  text->setFont(*font);
  text->setCharacterSize(size);
  text->setFillColor(sf::Color::White);
  text->setString(string_text);
  text->setOrigin(text->getGlobalBounds().left + (text->getGlobalBounds().width / 2.f),
                  text->getGlobalBounds().top + (text->getGlobalBounds().height / 2.f));
}

/////////////////////////////////////////////////
/// @brief Sets the flashing text flag true or false
///
/// Checks how much time has been passed since last render.
/// If it's more than 0.7 seconds, inverts the flag for the
/// flashing text and resets the clock.
/////////////////////////////////////////////////
void Menu::setFlashingPressStartText(){
  if (press_start_flashing_clock_.getElapsedTime().asSeconds() > 0.7f) {
    render_press_start_text_ = !render_press_start_text_;
    press_start_flashing_clock_.restart();
  }
}
