#include "ComputerSnake.h"
#include <cmath>
#include <iostream>

void ComputerSnake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void ComputerSnake::UpdateHead() {
  switch (ComputerSnakeDirection) {
    case Direction::kUp:
      head_y -= ComputerSnakeSpeed;
      break;

    case Direction::kDown:
      head_y += ComputerSnakeSpeed;
      break;

    case Direction::kLeft:
      head_x -= ComputerSnakeSpeed;
      break;

    case Direction::kRight:
      head_x += ComputerSnakeSpeed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void ComputerSnake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  ComputerSnakeBody.push_back(prev_head_cell);

  if (!ComputerSnakeGrowing) {
    // Remove the tail from the vector.
    ComputerSnakeBody.erase(ComputerSnakeBody.begin());
  } else {
    ComputerSnakeGrowing = false;
    ComputerSnakeSize++;
  }

  // Check if the snake has died.
  //for (auto const &item : body) {
  //  if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
  //    alive = false;
  //  }
  //}
}

void ComputerSnake::GrowBody() { ComputerSnakeGrowing = true; }

// Inefficient method to check if cell is occupied by snake.
bool ComputerSnake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : ComputerSnakeBody) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}