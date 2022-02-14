#include <SFML/Graphics.hpp>
#include <iostream>

#include "animation.hpp"
#include "bird.hpp"
#include "main_header.hpp"

int game() {
  sf::Texture texture_background;
  sf::Sprite sprite_background;

  texture_background.loadFromFile("../img/background_flappy.png");

  an::Animation animation_background((sf::Vector2i)texture_background.getSize(),
                                     4, 0.05);

  sprite_background.setTexture(texture_background);

  sprite_background.setTextureRect(sf::IntRect(
      animation_background.getOffset(), 0, animation_background.getImgSize().x,
      animation_background.getImgSize().y));

  brd::Bird bird("../img/bird.png", sf::Vector2f(180, 180), 4, 0.1);

  int flag_new_game = 1;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (flag_new_game == 1 && event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Space) {
        flag_new_game = 0;
      }
      bird.fly_up();
    }
    if (animation_background.isUpdate() == true) {
      sprite_background.setTextureRect(
          sf::IntRect(animation_background.getOffset(), 0,
                      animation_background.getImgSize().x,
                      animation_background.getImgSize().y));
    }
    if (flag_new_game == 0) {
      if (bird.fall_down() == 0) {
        return 1;
      }
    }

    window.clear(sf::Color::Black);
    window.draw(sprite_background);
    window.draw(bird.sprite);
    window.display();
  }
  return 0;
}