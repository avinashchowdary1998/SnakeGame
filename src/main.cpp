#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "ScoreFile.h"
#include "InitialSpeed.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  ScoreFile table;
  InitialSpeed speed;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  float initialSpeed = speed.GetInitialSpeedVal();
  Game game(kGridWidth, kGridHeight, initialSpeed);

  
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  table.WriteScoreToFile(game.GetScore());
  table.ShowComputerScore(game.GetScoreOfComputer());
  return 0;
}