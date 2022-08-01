#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL2/SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"
#include <future>
#include "ComputerSnake.h"
#include "food.h"
#include <algorithm>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, float initialSpeed);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetScoreOfComputer() const;
  int GetSize() const;

 private:
  Snake snake;
  //SDL_Point food;
  Food food;
  float InitialSpeed;
  std::vector<Obstacle> _obstacles;
  ComputerSnake computerSnake;

  std::vector<std::future<void>> futures;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int ComputerScore{0};

  std::vector<std::vector<int>> open_list;
  int g_value{0};
  int h_value{0};
  std::vector<int> CurrentPoint;
  const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  void PlaceFood();
  void Update();
  
  //bool FoodCell1(int x1, int y1);
  //bool FoodCell2(int x2, int y2);
  void UpdateComputerSnake();

  void AStarSearch();
  void DirectionOfComputerSnake(int, int);
  int CalculateHValue(int, int, int, int);
  void AddToOpenList(int, int, int, int);
  void SortOpenList();
  void AddToNeighbours(std::vector<int> CurrentNode);
  bool CheckIfValidCell(int x, int y);
  void PlaceObstacles();
  bool ObstaclesHit(SDL_Point p);
  bool ObstaclesHit(int x, int y);
  bool PointAvailable(SDL_Point p);
  
  
  
};

#endif