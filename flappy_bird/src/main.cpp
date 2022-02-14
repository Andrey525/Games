#include "main_header.hpp"

sf::RenderWindow window;

int main() {
  window.create(sf::VideoMode(448, 640), "Flappy B",
                sf::Style::Titlebar | sf::Style::Close);
  window.setPosition(sf::Vector2i((1366 - window.getSize().x) / 2,
                                  (768 - window.getSize().y)));
  window.setMouseCursorVisible(true);
  window.setMouseCursorGrabbed(false);
  window.setKeyRepeatEnabled(false);
  window.setFramerateLimit(60);
  // window.setVerticalSyncEnabled(true);
  while (1) {
    if (menu() == 0) {
      break;
    }
    if (game() == 0) {
      break;
    }
  }
  return 0;
}