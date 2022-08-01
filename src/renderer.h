#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL2/SDL.h"
#include "snake.h"
#include "obstacle.h"
#include "food.h"
#include "ComputerSnake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::vector<Obstacle> obstacles, Snake const snake, Food const &food, ComputerSnake const compSnake);
  void UpdateWindowTitle(int score, int fps, float compScore);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif