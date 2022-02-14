#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "snake_game.hpp"

bool isIntersected(sf::CircleShape head, sf::CircleShape apple,
                   float offset = 0) {
  float distance;
  float leg_x, leg_y;
  leg_x = fabs(head.getPosition().x - apple.getPosition().x);
  leg_y = fabs(head.getPosition().y - apple.getPosition().y);
  distance = sqrt(pow(leg_x, 2) + pow(leg_y, 2));
  if (distance <= (head.getRadius() + apple.getRadius() - offset)) {
    return true;
  }
  return false;
}

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;  // чтобы границы фигур были смазаны
  sf::RenderWindow window(sf::VideoMode(800, 600), "Snake-game",
                          sf::Style::Titlebar | sf::Style::Close, settings);
  window.setPosition(sf::Vector2i((1366 - window.getSize().x) / 2,
                                  (768 - window.getSize().y) / 2));
  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(true);  // видно ли курсор в окне?
  window.setMouseCursorGrabbed(false);  // курсор только в окне?

tryAgain:
  snk::Snake snake(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2),
                   sf::Color(250, 100, 50), sf::Vector2f(0, -1));

  snk::Apple apple(window.getSize());

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    if (snake.move(window.getSize()) == 1) {
      goto tryAgain;
    }
    if (isIntersected(snake.getVector().front(), apple) == true) {
      snake.addPart();
      apple.spawn(window.getSize());
    }

    for (auto iter = snake.getVector().begin() + 1;
         iter != snake.getVector().end(); iter++) {
      if (isIntersected(snake.getVector().front(), (*iter), 10) == true) {
        goto tryAgain;
      }
    }

    window.clear(sf::Color::Black);
    for (snk::SnakePart part : snake.getVector()) {
      window.draw(part);
    }
    window.draw(apple);
    window.display();
  }
  return 0;
}