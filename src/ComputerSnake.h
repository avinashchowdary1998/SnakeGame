#ifndef COMPUTERSNAKE_H
#define COMPUTERSNAKE_H

#include<iostream>
#include<cmath>
#include<vector>
#include "SDL2/SDL.h"

class ComputerSnake {
  public:

  enum class Direction { kUp, kDown, kLeft, kRight};

  ComputerSnake(int grid_width, int grid_height, float initialSpeed)
      : grid_width(grid_width),
        grid_height(grid_height),
        ComputerSnakeSpeed(initialSpeed),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction ComputerSnakeDirection = Direction::kUp;

  float ComputerSnakeSpeed;
  int ComputerSnakeSize{1};
  bool ComputerSnakeAlive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> ComputerSnakeBody;
  int TypesOfFood=0;
  int grid_width;
  int grid_height;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool ComputerSnakeGrowing{false};

};

#endif







