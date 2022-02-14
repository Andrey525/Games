#include <SFML/Graphics.hpp>
#include <list>
#include <string>

#include "main_header.hpp"

int menu() {
  sf::Texture texture_background;
  sf::Sprite sprite_background;
  sf::Font font;
  font.loadFromFile("../fonts/LibreFranklin-ExtraLight.ttf");
  std::list<sf::Text> menu_items;
  sf::Text text_start, text_exit;

  text_start.setFont(font);
  text_start.setString("Start");
  text_start.setCharacterSize(32);
  auto bounds = text_start.getLocalBounds();
  text_start.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
  text_start.setFillColor(sf::Color::Black);
  text_start.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 50);

  text_exit.setFont(font);
  text_exit.setString("Exit");
  text_exit.setCharacterSize(32);
  bounds = text_exit.getLocalBounds();
  text_exit.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
  text_exit.setFillColor(sf::Color::Black);
  text_exit.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 50);

  menu_items.push_back(text_start);
  menu_items.push_back(text_exit);

  texture_background.loadFromFile("../img/menu_background.png");
  sprite_background.setTexture(texture_background);

  auto iterator = menu_items.begin();
  (*iterator).setFillColor(sf::Color::White);
  (*iterator).setOutlineColor(sf::Color::Black);
  (*iterator).setOutlineThickness(3);
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Down) {
          (*iterator).setFillColor(sf::Color::Black);
          (*iterator).setOutlineThickness(0);
          if (iterator == --menu_items.end()) {
            iterator = menu_items.begin();
          } else {
            iterator++;
          }
          (*iterator).setFillColor(sf::Color::White);
          (*iterator).setOutlineColor(sf::Color::Black);
          (*iterator).setOutlineThickness(3);
        } else if (event.key.code == sf::Keyboard::Up) {
          (*iterator).setFillColor(sf::Color::Black);
          (*iterator).setOutlineThickness(0);
          if (iterator == menu_items.begin()) {
            iterator = --menu_items.end();
          } else {
            iterator--;
          }
          (*iterator).setFillColor(sf::Color::White);
          (*iterator).setOutlineColor(sf::Color::Black);
          (*iterator).setOutlineThickness(3);
        } else if (event.key.code == sf::Keyboard::Enter) {
          if ((*iterator).getString() == "Start") {
            return 1;
          } else if ((*iterator).getString() == "Exit") {
            return 0;
          }
        }
      }
    }
    window.clear(sf::Color::Black);
    window.draw(sprite_background);
    for (sf::Text element : menu_items) {
      window.draw(element);
    }
    window.display();
  }
  return 0;
}