#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <iostream>
using namespace std;

const float FOV = 3.14f/4.0f;
const int WINDOW_WIDTH = 1280;
const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;
sf::Color compute_pixel(int x, int y, wstring map, float f_player_x, float f_player_y, float f_player_a){
  float column = x;

  float column_angle = f_player_a + ((x / (float) WINDOW_WIDTH) * FOV) - FOV/2.0; //between -fov/2 and fov/2
  
  float f_distance = 0.0f;
  bool b_wallFound = false;
  float dirX = std::sin(column_angle);
  float dirY = std::cos(column_angle);
  while (f_distance < 32 && !b_wallFound)
  {
    int i_new_x = f_player_x + (dirX * f_distance);
    int i_new_y = f_player_y + (dirY * f_distance);

    if (i_new_x >= MAP_WIDTH || i_new_x < 0 || i_new_y >= MAP_HEIGHT || i_new_y < 0)
    {
      b_wallFound = true;
      f_distance = 16.0f;
      break;
    }

    if (map[i_new_y * MAP_WIDTH + i_new_x] == '#')
    {
      b_wallFound = true;
    }
    
    f_distance += 0.05f;
  }
  int nCeiling = (float)(720.0f / 2.0f) - 720.0f / f_distance; 
  int nFloor = 720 - nCeiling;

  if (y < nCeiling) {
    return sf::Color::Black;
  }
  if (y > nCeiling && y <= nFloor) {
    float shade = std::max(1.0f - f_distance/16.0, 0.0); // 0 when far away and 1 when close.
    return sf::Color(shade*255, shade*255, shade*255);
  }
  return sf::Color::Black;


  
}
