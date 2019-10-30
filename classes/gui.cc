#include "gui.h"

/////////////////////////////////////////////////
/// @brief Draws the GUI to the specified RenderWindow.
///
/// @param window The RenderWindow to draw the GUI on.
///
/// Draws the GUI to the specified RenderWindow.
/////////////////////////////////////////////////
void GUI::draw(sf::RenderWindow &window) {
  // window.draw(left_);
  // window.draw(middle_);
  // window.draw(right_);
  window.draw(lives_text_);
  window.draw(score_text_);
  window.draw(level_text_);
}

/////////////////////////////////////////////////
/// @brief Initializes the GUI.
///
/// Sets everything that needs to be set calling the methods
/// that need to be called.
/////////////////////////////////////////////////
void GUI::init(const sf::Font &font) {
  // initLayout();
  // lives
  initText(lives_text_, kLivesText, font, kGUITextFontSize, kGUIDefaultFontColor, false);
  lives_text_.setPosition(10.f, 6.f);
  // score
  initText(score_text_, kScoreText, font, kGUITextFontSize, kGUIDefaultFontColor, false);
  score_text_.setOrigin(score_text_.getGlobalBounds().left + (score_text_.getGlobalBounds().width / 2.f),
                        score_text_.getGlobalBounds().top);
  score_text_.setPosition(kScreenWidth / 2.f, 6.f);
  // level
  initText(level_text_, kLevelText, font, kGUITextFontSize, kGUIDefaultFontColor, false);
  level_text_.setOrigin(level_text_.getGlobalBounds().left + level_text_.getGlobalBounds().width, 
                        level_text_.getGlobalBounds().top);
  level_text_.setPosition(kScreenWidth - 10.f, 6.f);
}

/////////////////////////////////////////////////
/// @brief Initializes the layout of the GUI.
///
/// Sets everything that needs to be set.
/////////////////////////////////////////////////
void GUI::initLayout() {
  left_.setSize(kGUIDefaultSize);
  left_.setPosition(0.f, 0.f);
  left_.setOutlineThickness(kGUIDefaultOutlineThickness);
  left_.setFillColor(kGUIDefaultFillColor); 
  left_.setOutlineColor(kGUIDefaultOutlineColor);
  middle_.setSize(sf::Vector2f(kGUIDefaultSize.x + 2.f, kGUIDefaultSize.y));
  middle_.setPosition(kGUIDefaultSize.x - 1.f, 0.f);
  middle_.setOutlineThickness(kGUIDefaultOutlineThickness);
  middle_.setFillColor(kGUIDefaultFillColor); 
  middle_.setOutlineColor(kGUIDefaultOutlineColor);
  right_.setSize(kGUIDefaultSize);
  right_.setPosition(kGUIDefaultSize.x * 2.f, 0.f);
  right_.setOutlineThickness(kGUIDefaultOutlineThickness);
  right_.setFillColor(kGUIDefaultFillColor); 
  right_.setOutlineColor(kGUIDefaultOutlineColor);
}

/////////////////////////////////////////////////
/// @brief Initializes a given text.
///
/// @param text The address of the sf::Text to be initialized.
/// @param string_text The literal sf::String of characters to be rendered.
/// @param font The sf::Font to be used.
/// @param size The desired size (integer) of the rendered text.
/// @param color The desired sf::Color for the text.
/// @param centered True if you want the origin of the text centered in both axis.
///
/// Sets the font, the size, the fill color and the string to be
/// rendered for the text. Thereafter sets the origin of the text
/// to be at the half of both height and width (the "center").
/////////////////////////////////////////////////
void GUI::initText( sf::Text          &text, 
                    const sf::String  string_text, 
                    const sf::Font    &font, 
                    const int         size,
                    const sf::Color   color, 
                    const bool        centered ) {
  text.setFont(font);
  text.setCharacterSize(size);
  text.setFillColor(color);
  text.setString(string_text);
  if (centered) {
    text.setOrigin( text.getGlobalBounds().left + (text.getGlobalBounds().width / 2.f),
                    text.getGlobalBounds().top + (text.getGlobalBounds().height / 2.f) ); 
  }
}
