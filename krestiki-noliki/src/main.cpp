#include <unistd.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define N 3

enum Values { NOTHING, KREST, NOLIK };

int field[N][N];  // крестик - 1, нолик - 2
int who;          // кто ходит
int count_filled_cells;
int flag;

void restart() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      field[i][j] = 0;
    }
  }
  count_filled_cells = 0;
  who = KREST;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(256, 256), "Krest-Nolik",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setPosition(sf::Vector2i((1366 - window.getSize().x) / 2,
                                  (768 - window.getSize().y)));
  window.setMouseCursorVisible(true);
  window.setMouseCursorGrabbed(false);

  // выравнивание изображений
  const float offset_field = 8.5;
  const float offset_krest = 12.5;
  const float offset_nolik = 13.5;

  sf::Texture texture_field, texture_krest, texture_nolik;
  sf::Sprite sprite_field, sprite_krest, sprite_nolik;
  sf::SoundBuffer sound_buffer;
  sf::Sound sound;
  sf::Font font;
  sf::Text text;

  font.loadFromFile("../fonts/LibreFranklin-ExtraLight.ttf");
  text.setFont(font);
  text.setString("Press enter\nto continue...");
  text.setCharacterSize(32);
  text.setFillColor(sf::Color::Black);
  text.setPosition(40, 90);

  texture_field.loadFromFile("../img/field.png");
  texture_krest.loadFromFile("../img/krest.png");
  texture_nolik.loadFromFile("../img/nolik.png");

  sprite_field.setTexture(texture_field);
  sprite_krest.setTexture(texture_krest);
  sprite_nolik.setTexture(texture_nolik);

  sprite_field.setPosition(sf::Vector2f(offset_field, offset_field));
  restart();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      // обработка мыши
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          int i, j;
          sf::Vector2i mouse_pos;
          mouse_pos = sf::Mouse::getPosition(window);

          if (mouse_pos.x > 10 && mouse_pos.x < 80) {
            j = 0;
          } else if (mouse_pos.x > 100 && mouse_pos.x < 160) {
            j = 1;
          } else if (mouse_pos.x > 180 && mouse_pos.x < 250) {
            j = 2;
          } else {
            j = -1;
          }

          if (mouse_pos.y > 10 && mouse_pos.y < 80) {
            i = 0;
          } else if (mouse_pos.y > 100 && mouse_pos.y < 160) {
            i = 1;
          } else if (mouse_pos.y > 180 && mouse_pos.y < 250) {
            i = 2;
          } else {
            i = -1;
          }

          if (i != -1 && j != -1 && field[i][j] == 0) {
            sound_buffer.loadFromFile("../aud/draw.wav");
            sound.setBuffer(sound_buffer);
            sound.play();
            if (who == KREST) {
              field[i][j] = KREST;
              who = NOLIK;
            } else if (who == NOLIK) {
              field[i][j] = NOLIK;
              who = KREST;
            }
            count_filled_cells++;
          } else {
            sound_buffer.loadFromFile("../aud/click.wav");
            sound.setBuffer(sound_buffer);
            sound.play();
          }
        }
      }
      //!
    }

    // отрисовка
    window.clear(sf::Color::White);
    window.draw(sprite_field);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        switch (field[i][j]) {
          case NOTHING:
            break;
          case KREST:
            sprite_krest.setPosition(
                j * sprite_krest.getTexture()->getSize().x +
                    offset_krest * (j + 1),
                i * sprite_krest.getTexture()->getSize().y +
                    offset_krest * (i + 1));
            window.draw(sprite_krest);
            break;
          case NOLIK:
            sprite_nolik.setPosition(
                j * sprite_nolik.getTexture()->getSize().x +
                    offset_nolik * (j + 1),
                i * sprite_nolik.getTexture()->getSize().y +
                    offset_nolik * (i + 1));
            window.draw(sprite_nolik);
            break;
        }
      }
    }
    window.display();
    //!

    // определяем победителя (если он есть)
    if ((field[0][0] == KREST && field[0][1] == KREST &&
         field[0][2] == KREST) ||
        (field[1][0] == KREST && field[1][1] == KREST &&
         field[1][2] == KREST) ||
        (field[2][0] == KREST && field[2][1] == KREST &&
         field[2][2] == KREST) ||
        (field[0][0] == KREST && field[1][0] == KREST &&
         field[2][0] == KREST) ||
        (field[0][1] == KREST && field[1][1] == KREST &&
         field[2][1] == KREST) ||
        (field[0][2] == KREST && field[1][2] == KREST &&
         field[2][2] == KREST) ||
        (field[0][0] == KREST && field[1][1] == KREST &&
         field[2][2] == KREST) ||
        (field[0][2] == KREST && field[1][1] == KREST &&
         field[2][0] == KREST)) {
      sleep(1);
      sound_buffer.loadFromFile("../aud/krest_win.wav");
      sound.setBuffer(sound_buffer);
      sound.play();
      sleep(1);
      flag = 1;
      window.draw(text);
      window.display();
      while (flag) {
        // сбрасываем события мыши
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();
            flag = 0;
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
          flag = 0;
        }
      }
      restart();
    } else if ((field[0][0] == NOLIK && field[0][1] == NOLIK &&
                field[0][2] == NOLIK) ||
               (field[1][0] == NOLIK && field[1][1] == NOLIK &&
                field[1][2] == NOLIK) ||
               (field[2][0] == NOLIK && field[2][1] == NOLIK &&
                field[2][2] == NOLIK) ||
               (field[0][0] == NOLIK && field[1][0] == NOLIK &&
                field[2][0] == NOLIK) ||
               (field[0][1] == NOLIK && field[1][1] == NOLIK &&
                field[2][1] == NOLIK) ||
               (field[0][2] == NOLIK && field[1][2] == NOLIK &&
                field[2][2] == NOLIK) ||
               (field[0][0] == NOLIK && field[1][1] == NOLIK &&
                field[2][2] == NOLIK) ||
               (field[0][2] == NOLIK && field[1][1] == NOLIK &&
                field[2][0] == NOLIK)) {
      sleep(1);
      sound_buffer.loadFromFile("../aud/nolik_win.wav");
      sound.setBuffer(sound_buffer);
      sound.play();
      sleep(1);
      flag = 1;
      window.draw(text);
      window.display();
      while (flag) {
        // сбрасываем события мыши
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();
            flag = 0;
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
          flag = 0;
        }
      }
      restart();
    }
    //!

    // проверяем заполнено ли полностью поле
    if (count_filled_cells == N * N) {
      sleep(1);
      sound_buffer.loadFromFile("../aud/standoff.wav");
      sound.setBuffer(sound_buffer);
      sound.play();
      sleep(2);
      flag = 1;
      window.draw(text);
      window.display();
      while (flag) {
        // сбрасываем события мыши
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();
            flag = 0;
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
          flag = 0;
        }
      }
      restart();
    }
    //!
  }
  return 0;
}