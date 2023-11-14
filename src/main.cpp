#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "raycast.h"


const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH = 1280;
const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 16;
int main() {
  cout << "Creating window..." << endl;

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Bleib");
  sf::Image image; //This image is the generated pixels "buffer".
  image.create(WINDOW_WIDTH,WINDOW_HEIGHT, sf::Color::Red);

  sf::Texture texture;
  sf::Sprite gameContent;
  float player_x = 8.0f;
  float player_y = 8.0f;
  float player_a = 0.0f;
  wstring map;
  map += L"################";
  map += L"#              #";
  map += L"#              #";
  map += L"# ######       #";
  map += L"#              #";
  map += L"#              #";
  map += L"#              #";
  map += L"#              #";
  map += L"#      .       #"; //Point is player starting position.
  map += L"#              #";
  map += L"#              #";
  map += L"#     # ##     #";
  map += L"#              #";
  map += L"#              #";
  map += L"#              #";
  map += L"################";

  
  while (window.isOpen()) 
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code  == sf::Keyboard::D)
        {
          player_y += std::sin(player_a) * 0.2;
          player_x += std::cos(player_a) * 0.2;
        }
        if (event.key.code == sf::Keyboard::Q)
        {
          player_y -= std::sin(player_a) * 0.2;
          player_x -= std::cos(player_a) * 0.2;
        }
        if (event.key.code == sf::Keyboard::Z)
        {
          player_y += std::cos(player_a) * 0.2;
          player_x += std::sin(player_a) * 0.2;
        }
        if (event.key.code == sf::Keyboard::S)
        {
          player_y -= std::cos(player_a) * 0.2;
          player_x -= std::sin(player_a) * 0.2;
        }

        if (event.key.code == sf::Keyboard::Left)
        {
          player_a -= 0.1f;
        }
        if (event.key.code == sf::Keyboard::Right)
        {
          player_a += 0.1f;
        }
      }
    }

    //Basic loop to compute raycast for every pixel of the screen.
    for (int gx = 0; gx < WINDOW_WIDTH/GRID_WIDTH; gx ++) 
    {
      for (int gy= 0; gy < WINDOW_HEIGHT/GRID_HEIGHT; gy++)
      {
        
        sf::Color color = compute_pixel(gx*GRID_WIDTH,gy*GRID_HEIGHT, map, player_x, player_y, player_a);
        for (int i = 0; i < GRID_WIDTH; i++) {
          for (int j = 0; j < GRID_HEIGHT; j++) {
              image.setPixel(gx*GRID_WIDTH + i, gy*GRID_HEIGHT+j, color);
            
          }
        }
      }
    }


    texture.loadFromImage(image);
    gameContent.setTexture(texture);
    window.clear(sf::Color::Black);
    window.draw(gameContent);
    window.display();

  }
}
