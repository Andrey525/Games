#include "bird.hpp"

#include <iostream>

sf::Event event;

namespace brd {
Bird::Bird(std::string path_to_img, sf::Vector2f sprite_position,
           int count_of_img, float delay) {
  texture.loadFromFile(path_to_img);
  sprite.setTexture(texture);
  an::Animation animation((sf::Vector2i)texture.getSize(), count_of_img, delay);
  this->animation = animation;
  changeSpriteText();
  sprite.setOrigin(sprite.getLocalBounds().width / 2,
                   sprite.getLocalBounds().height / 2);
  sprite.setPosition(sprite_position);
}

void Bird::changeSpriteText() {
  sprite.setTextureRect(sf::IntRect(animation.getOffset(), 0,
                                    animation.getImgSize().x,
                                    animation.getImgSize().y));
}

void Bird::animate() {
  if (animation.isUpdate() == true) {
    changeSpriteText();
  }
}

int Bird::fall_down() {
  if (sprite.getPosition().y < previous_position.y) {
    falling_speed += 0.03;
    animate();
  } else if ((sprite.getPosition().y >= previous_position.y) &&
             ((sprite.getRotation() >= 345.0 &&
               sprite.getRotation() <= 360.0) ||
              (sprite.getRotation() >= 0.0 && sprite.getRotation() < 90.0))) {
    falling_speed += 0.1;
    sprite.rotate(6.0);
    animate();

  } else {
    sprite.setRotation(90.0);
    if (animation.getCurrentNumber() != 0) {
      animation.load_specified_frame(0);
      changeSpriteText();
    }
  }
  sprite.move(0.0, falling_speed);
  if (sprite.getPosition().y >= 520.0) {
    return 0;
  }
  return 1;
}

void Bird::fly_up() {
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Space) {
    previous_position = sprite.getPosition();
    sprite.setRotation(345.0);
    sprite.move(0.0, -100.0);
    falling_speed = 2;
  }
}

}  // namespace brd