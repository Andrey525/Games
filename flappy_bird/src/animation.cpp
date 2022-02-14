#include "animation.hpp"

namespace an {
Animation::Animation() {}

Animation::Animation(sf::Vector2i img_size, int count_of_img, float delay)
    : count_of_img(count_of_img), delay(delay) {
  this->img_size.x = img_size.x / count_of_img;
  this->img_size.y = img_size.y;
  offset = current_number_of_img * img_size.x;
  clock.restart();
}

sf::Vector2i Animation::getImgSize() { return img_size; }

int Animation::getOffset() { return offset; }

bool Animation::isUpdate() {
  float time = clock.getElapsedTime().asSeconds();
  clock.restart();
  timer += time;
  if (timer >= delay) {
    current_number_of_img++;
    if (current_number_of_img == count_of_img) {
      current_number_of_img = 0;
    }
    offset = current_number_of_img * img_size.x;
    timer = 0;
    return true;
  }
  return false;
}

void Animation::load_specified_frame(int number) {
  current_number_of_img = number;
  offset = current_number_of_img * img_size.x;
}

int Animation::getCurrentNumber() { return current_number_of_img; }

}  // namespace an