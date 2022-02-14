#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "snake_game.hpp"
namespace snk {
Snake::Snake(sf::Vector2f position, sf::Color color, sf::Vector2f direction) {
  SnakePart head(position, color, direction);
  snake_parts.push_back(head);
}

std::vector<SnakePart> Snake::getVector() { return snake_parts; }

int Snake::move(sf::Vector2u window_size) {
  std::vector<SnakePart>::iterator iter = snake_parts.begin();

  for (iter = snake_parts.begin(); iter != snake_parts.end(); iter++) {
    if (iter != snake_parts.begin() &&
        (*iter).getDirection() != (*(iter - 1)).getDirection()) {
      if ((*iter).getPosition().x == (*(iter - 1)).getPrevPos().x &&
          (*iter).getPosition().y == (*(iter - 1)).getPrevPos().y) {
        (*iter).setDirection((*(iter - 1)).getDirection());
        (*iter).setPrevPos((*iter).getPosition());
      }
    } else if (iter == snake_parts.begin()) {
      if (fabs((*iter).getPosition().x - (*iter).getPrevPos().x) >=
              (3 * (*iter).getRadius()) ||
          fabs((*iter).getPosition().y - (*iter).getPrevPos().y) >=
              (3 * (*iter).getRadius())) {
        (*iter).rotate();
      }
    }

    (*iter).move();
    if ((*iter).isIntersected(window_size) == true) {
      return 1;
    }
  }
  return 0;
}

void Snake::addPart() {
  SnakePart last = snake_parts.back();
  sf::Vector2f direction_last = last.getDirection();
  sf::Vector2f position_last = last.getPosition();
  float radius = last.getRadius();
  sf::Vector2f position_new = position_last - 2 * radius * direction_last;

  SnakePart new_part(position_new, sf::Color(100, 250, 50), direction_last);
  snake_parts.push_back(new_part);
}

}  // namespace snk
