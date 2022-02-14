#include <SFML/Graphics.hpp>
#pragma once

namespace an {
class Animation {
 private:
  int count_of_img;
  int current_number_of_img = 0;
  sf::Vector2i img_size;
  int offset;
  sf::Clock clock;
  float timer = 0;
  float delay;

 public:
  Animation();
  Animation(sf::Vector2i img_size, int count_of_img, float delay);
  sf::Vector2i getImgSize();
  int getOffset();
  bool isUpdate();
  int getCurrentNumber();
  void load_specified_frame(int number);
};
}  // namespace an