#include <SFML/Graphics.hpp>
#include <string>

#include "animation.hpp"
#pragma once

namespace brd {
class Bird {
 private:
  sf::Texture texture;
  an::Animation animation;
  sf::Vector2f previous_position;
  float falling_speed = 1.0;

 public:
  sf::Sprite sprite;
  Bird(std::string path_to_img, sf::Vector2f sprite_position, int count_of_img,
       float delay);
  void changeSpriteText();
  void animate();
  int fall_down();
  void fly_up();
};
}  // namespace brd