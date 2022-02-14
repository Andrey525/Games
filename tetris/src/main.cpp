#include <time.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define HEIGHT 20  // высота игрового поля
#define WIDTH 10   // ширина игрового поля
#define COUNT_POINTS_IN_TETRAMINO 4
#define COUNT_TETRAMINOS 7

#define SIZE_OF_SQUARE 18  // px

int field[HEIGHT][WIDTH];  // игровое поле

struct Point_Coords {
  int x;
  int y;
};

struct Figure_Coords {
  Point_Coords array[COUNT_POINTS_IN_TETRAMINO];
};

// логика представления фигурок-тетрамино:
/*
# 0 1
0 x #
1 x #
2 x #
3 x #
*/

/*
# 0 1
0 x x
1 x #
2 # #
3 x #
*/

/*
# 0 1
0 x x
1 x #
2 # #
3 # x
*/

/*
# 0 1
0 x x
1 # #
2 # #
3 x x
*/

// Массив точек фигурок-тетрамино

Figure_Coords own_figure_coords[COUNT_TETRAMINOS] = {
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}},  // I
    {{{0, 1}, {0, 2}, {1, 2}, {1, 3}}},  // S
    {{{1, 1}, {0, 2}, {1, 2}, {0, 3}}},  // Z
    {{{1, 1}, {0, 2}, {1, 2}, {1, 3}}},  // T
    {{{0, 1}, {1, 1}, {1, 2}, {1, 3}}},  // L
    {{{1, 1}, {1, 2}, {0, 3}, {1, 3}}},  // J
    {{{0, 1}, {1, 1}, {0, 2}, {1, 2}}},  // O
};

bool check(Figure_Coords coords) {
  for (Point_Coords v : coords.array)
    if (v.x < 0 || v.x >= WIDTH || v.y >= HEIGHT) {
      return 0;
    } else if (field[v.y][v.x] != -1) {
      return 0;
    }
  return 1;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
  window.setKeyRepeatEnabled(false);
  sf::Music music;
  music.openFromFile("./sound/music.wav");
  music.play();
  music.setLoop(true);

  int colorNum = 0;
  int type = 3;
  int offset_x = rand() % (WIDTH - 1);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      field[i][j] = -1;
    }
  }

  sf::Texture texture, texture_background;
  texture.loadFromFile("./img/tiles.png");
  texture_background.loadFromFile("./img/background.png");
  sf::Sprite sprite(texture);
  sf::Sprite sprite_background(texture_background);
  sprite.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));

  Figure_Coords coords = own_figure_coords[type];
  for (Point_Coords &v : coords.array) {
    v.x += offset_x;
  }

  float timer = 0;
  float delay = 0.3;

  sf::Clock clock;
  srand(time(NULL));

  while (window.isOpen()) {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
          if (check(coords) == 1) {
            Figure_Coords previous = coords;
            for (Point_Coords &v : coords.array) {
              v.x = v.x - 1;
            }
            if (check(coords) == 0) {
              coords = previous;
            }
          }
        } else if (event.key.code == sf::Keyboard::Right) {
          if (check(coords) == 1) {
            Figure_Coords previous = coords;
            for (Point_Coords &v : coords.array) {
              v.x = v.x + 1;
            }
            if (check(coords) == 0) {
              coords = previous;
            }
          }
        } else if (event.key.code == sf::Keyboard::Space) {
          if (check(coords) == 1) {
            Point_Coords center = coords.array[1];
            Figure_Coords previous = coords;
            int dx, dy;
            for (Point_Coords &v : coords.array) {
              dx = v.x - center.x;
              dy = v.y - center.y;
              v.x = center.x - dy;
              v.y = center.y + dx;
            }
            if (check(coords) == 0) {
              coords = previous;
            }
          }
        }
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      delay = 0.1;
    }
    if (timer >= delay) {
      if (check(coords) == 1) {
        for (Point_Coords &v : coords.array) {
          v.y += 1;
        }
      }
      if (check(coords) == 0) {
        for (int i = 0; i < COUNT_POINTS_IN_TETRAMINO; i++) {
          field[coords.array[i].y - 1][coords.array[i].x] = colorNum;
        }
        colorNum = rand() % 7;
        type = rand() % 7;
        coords = own_figure_coords[type];
        offset_x = rand() % (WIDTH - 1);
        for (Point_Coords &v : coords.array) {
          v.x += offset_x;
        }
        sprite.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
      }
      timer = 0;
    }

    //----ПРОВЕРКА ЛИНИИ----//
    int k = HEIGHT - 1;
    for (int i = HEIGHT - 1; i > 0; i--) {
      int count = 0;
      for (int j = 0; j < WIDTH; j++) {
        if (field[i][j] != -1) {
          count++;
        }
        field[k][j] = field[i][j];
      }
      if (count < WIDTH) {
        k--;
      }
    }

    window.clear(sf::Color::White);
    window.draw(sprite_background);
    for (Point_Coords v : coords.array) {
      sprite.setPosition(v.x * SIZE_OF_SQUARE, v.y * SIZE_OF_SQUARE);
      sprite.move(28, 31);  // выравнивание относительно заднего фона
      window.draw(sprite);
    }

    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        if (field[i][j] == -1) {
          continue;
        } else {
          sprite.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
          sprite.setPosition(j * 18, i * 18);
          sprite.move(28, 31);
          window.draw(sprite);
        }
      }
    }
    sprite.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
    window.display();
    delay = 0.3;
  }
  return 0;
}