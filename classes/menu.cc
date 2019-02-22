#include "menu.h"

void Menu::draw(sf::RenderWindow* window) {
  window->draw(title_);
  // window->draw(subtitle_);
}

void Menu::init(sf::Font* font) {
  initText(&title_, font, 30);
  title_.setString(kGameTitle);
  // initText(&subtitle_, font, 10);
  // title_.setString(kGameTitleJ); 
}

void Menu::initText(sf::Text* text, sf::Font* font, int size) {
  text->setFont(*font);
  text->setCharacterSize(size);
  text->setFillColor(sf::Color::White);
}