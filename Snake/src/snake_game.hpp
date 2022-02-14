#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

namespace snk {
class Apple : public sf::CircleShape {
 public:
  Apple(sf::Vector2u window_size);
  void spawn(sf::Vector2u window_size);
};

class SnakePart : public sf::CircleShape {
 private:
  sf::Vector2f direction;
  sf::Vector2f previous_position;
  float speed;

 public:
  SnakePart(sf::Vector2f position, sf::Color color, sf::Vector2f direction);
  void move();
  void rotate();
  bool isIntersected(sf::Vector2u window_size);
  sf::Vector2f getDirection();
  void setDirection(sf::Vector2f direction);
  sf::Vector2f getPrevPos();
  void setPrevPos(sf::Vector2f previous_position);
};

class Snake {
 private:
  std::vector<SnakePart> snake_parts;

 public:
  Snake(sf::Vector2f position, sf::Color color, sf::Vector2f direction);
  std::vector<SnakePart> getVector();
  int move(sf::Vector2u window_size);
  void addPart();
};
}  // namespace snk