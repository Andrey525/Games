#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "snake_game.hpp"

namespace snk {

Apple::Apple(sf::Vector2u window_size) {
  setRadius(10.f);
  setFillColor(sf::Color(100, 250, 50));
  setOrigin(getRadius() / 2, getRadius() / 2);
  spawn(window_size);
}

void Apple::spawn(sf::Vector2u window_size) {
  int pos_x, pos_y;
  int offset = 20;
  srand(time(NULL));
  pos_x = rand() % (window_size.x - offset * 2 + 1) + offset;
  pos_y = rand() % (window_size.y - offset * 2 + 1) + offset;
  setPosition(pos_x, pos_y);
}

SnakePart::SnakePart(sf::Vector2f position, sf::Color color,
                     sf::Vector2f direction) {
  setRadius(10.f);
  setFillColor(color);
  setPosition(position);
  setOrigin(getRadius() / 2, getRadius() / 2);
  setDirection(direction);
  setPrevPos(position);
  speed = 2;
}

void SnakePart::move() { sf::CircleShape::move(direction * speed); }

void SnakePart::rotate() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    if (fabs(direction.y) == 1) {
      setDirection(sf::Vector2f(-1, 0));
      setPrevPos(getPosition());
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    if (fabs(direction.y) == 1) {
      setDirection(sf::Vector2f(1, 0));
      setPrevPos(getPosition());
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    if (fabs(direction.x) == 1) {
      setDirection(sf::Vector2f(0, -1));
      setPrevPos(getPosition());
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    if (fabs(direction.x) == 1) {
      setDirection(sf::Vector2f(0, 1));
      setPrevPos(getPosition());
    }
  }
}

bool SnakePart::isIntersected(sf::Vector2u window_size) {
  /*  пересечения:
  с верхней границей экрана
  с нижней
  с левой
  с правой
   */
  if ((getPosition().y - getRadius() <= 0) ||
      (getPosition().y + getRadius() >= window_size.y) ||
      (getPosition().x - getRadius() <= 0) ||
      (getPosition().x + getRadius() >= window_size.x)) {
    return true;
  }
  return false;
}

sf::Vector2f SnakePart::getDirection() { return direction; }

void SnakePart::setDirection(sf::Vector2f direction) {
  this->direction = direction;
}

sf::Vector2f SnakePart::getPrevPos() { return previous_position; }

void SnakePart::setPrevPos(sf::Vector2f previous_position) {
  this->previous_position = previous_position;
}

}  // namespace snk
