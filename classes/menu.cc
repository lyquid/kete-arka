#include "menu.h"

/////////////////////////////////////////////////
/// @brief Draws the game's main title and "press start" text.
///
/// @param window The renderWindow to render the texts on.
///
/// Draws the game's main title and "press start" on the given RenderWindow.
/////////////////////////////////////////////////
void Menu::drawMenu(sf::RenderWindow* window) {
  window->draw(title_text_);
  window->draw(press_start_text_);
}

/////////////////////////////////////////////////
/// @brief Draws the pause text.
///
/// @param window The renderWindow to render the "pause" text on.
///
/// Draws the pause text on the given RenderWindow.
/////////////////////////////////////////////////
void Menu::drawPause(sf::RenderWindow* window) {
  window->draw(pause_text_);
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
  initText(&title_text_, kGameTitle, font, 60);
  title_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.25f);
  // press start text
  initText(&press_start_text_, kPressStartText, font, 20);
  press_start_text_.setPosition(kScreenWidth / 2.f, kScreenHeight * 0.75f);
  // pause text
  initText(&pause_text_, kPauseText, font, 20);
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
