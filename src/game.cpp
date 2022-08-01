#include "game.h"
#include <iostream>
#include "SDL2/SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, float initialSpeed)
    : snake(grid_width, grid_height, initialSpeed),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      InitialSpeed(initialSpeed),
      computerSnake(grid_width, grid_height, initialSpeed)     
      {
          PlaceObstacles();
          PlaceFood();
      }

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    futures.emplace_back(std::async(std::launch::async, &Game::Update, this));
    renderer.Render(_obstacles, snake, food, computerSnake);
    futures.emplace_back(std::async(std::launch::async, &Game::UpdateComputerSnake, this));


    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, ComputerScore);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    for(std::future<void> &ftr:futures) {
      ftr.wait();
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x1, y1, x2, y2;
  while (true) {
    x1 = random_w(engine);
    y1 = random_h(engine);
    x2 = random_w(engine);
    y2 = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x1, y1) &&!snake.SnakeCell(x2, y2) && (x1!=x2) && !ObstaclesHit(x1, y1) && !ObstaclesHit(x2, y2) && !computerSnake.SnakeCell(x1, y1) && !computerSnake.SnakeCell(x2, y2)) {
      food._point1.x = x1;
      food._point1.y = y1;
      food._point2.x = x2;
      food._point2.y = y2;

      return;
    }
  }
}



void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  
  // Check if there's food over here
  if (food._point1.x == new_x && food._point1.y == new_y) {
    //score++;
    if(InitialSpeed==0.1f)
        score=score+1;
    else if(InitialSpeed==0.4f)
        score=score+2;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  if (food._point2.x == new_x && food._point2.y == new_y) {
    //score=score+2;
    if(InitialSpeed==0.1f)
        score=score+2;
    else if(InitialSpeed==0.4f)
        score=score+4;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  if(ObstaclesHit(new_x, new_y)) {
    snake.alive=false;
    std::cout<<"Hit an Obstacle"<<std::endl;
    return;
  }

}

void Game::UpdateComputerSnake() {
  computerSnake.Update();
  std::future<void> ftr=std::async(std::launch::async, &Game::AStarSearch, this);
  ftr.wait();
  int new_x=static_cast<int>(computerSnake.head_x);
  int new_y=static_cast<int>(computerSnake.head_y);
  if (food._point2.x == new_x && food._point2.y == new_y) {
    //ComputerScore=ComputerScore+1;
    if(InitialSpeed==0.1f)
        ComputerScore=ComputerScore+1;
    else if(InitialSpeed==0.4f)
        ComputerScore=ComputerScore+2;
        
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  
}

void Game::PlaceObstacles() {
  int NoOfObstacles=6;
  for(int i=0; i<NoOfObstacles; ++i) {
    Obstacle temp(random_w(engine), random_h(engine));
    while(!PointAvailable(temp.kCordinate)) {
      temp.SetPosition(random_w(engine), random_h(engine));
    }
    _obstacles.emplace_back(std::move(temp));
  }
}

bool Game::ObstaclesHit(int x, int y) {
  for(auto i: _obstacles) {
    if(i.ObstacleHit(x,y))
        return true;
  }
  return false;
}

bool Game::ObstaclesHit(SDL_Point p) {
  for(auto i: _obstacles) {
    if(i.ObstacleHit(p))
        return true;
        
  }
  return false;
}

bool Game::PointAvailable(SDL_Point p) {
  if(ObstaclesHit(p))
      return false;
  if((p.x==food._point2.x)&&(p.y==food._point2.y))
      return false;
  if((p.x==food._point2.x)&&(p.y==food._point2.y))
      return false;
  if(snake.SnakeCell(p.x, p.y))
      return false;
  if(computerSnake.SnakeCell(p.x, p.y))
      return false;
  return true;

}

int Game::GetScore() const { return score; }
int Game::GetScoreOfComputer() const {return ComputerScore;}
int Game::GetSize() const { return snake.size; }

void Game::AStarSearch() {
  h_value=CalculateHValue(computerSnake.head_x, computerSnake.head_y, food._point2.x, food._point2.y);
  AddToOpenList(computerSnake.head_x, computerSnake.head_y, g_value, h_value);
  while(open_list.size()>0) {
    CurrentPoint=open_list.back();
    open_list.pop_back();
    DirectionOfComputerSnake(CurrentPoint[0], CurrentPoint[1]);
    int new_x=static_cast<int>(computerSnake.head_x);
    int new_y=static_cast<int>(computerSnake.head_y);
    if(!(food._point2.x == new_x && food._point2.y == new_y)) {
        AddToNeighbours(CurrentPoint);
    }
    else
    {
         break;
    }
  }
  return;
}

void Game::DirectionOfComputerSnake(int x, int y) {
  if(x<food._point2.x && y<food._point2.y)
      computerSnake.ComputerSnakeDirection=ComputerSnake::Direction::kRight;
  else if(x==food._point2.x && y>food._point2.y)
      computerSnake.ComputerSnakeDirection=ComputerSnake::Direction::kUp;
  else if(x==food._point2.x && y<food._point2.y)
      computerSnake.ComputerSnakeDirection=ComputerSnake::Direction::kDown;
  else if(x>food._point2.x && y==food._point2.y)
      computerSnake.ComputerSnakeDirection=ComputerSnake::Direction::kLeft;
  else if(x<food._point2.x && y==food._point2.y)
      computerSnake.ComputerSnakeDirection=ComputerSnake::Direction::kRight;
  else if(x>food._point2.x && y>food._point2.y)
      computerSnake.ComputerSnakeDirection=ComputerSnake::Direction::kLeft;

}

int Game::CalculateHValue(int x1, int y1, int x2, int y2) {
  return (abs(x2-x1)+abs(y2-y1));

}

void Game::AddToOpenList(int x, int y, int g, int h){
  open_list.push_back(std::vector<int> {x, y, g, h});
  SortOpenList();

}

bool Compare(std::vector<int> a, std::vector<int> b) {
  int f1=a[2]+a[3];
  int f2=b[2]+b[3];
  return f1>f2;
}

void Game::SortOpenList() {
  std::sort(open_list.begin(), open_list.end(), Compare);

}



void Game::AddToNeighbours(std::vector<int> CurrentNode) {
  int x=CurrentNode[0];
  int y=CurrentNode[1];
  int g_value=CurrentNode[2];

  for(int i=0; i<4; i++) {
    int x1=x+delta[i][0];
    int y1=y+delta[i][1];
    
    if(CheckIfValidCell(x1, y1)) {
      int g2_value=g_value+1;
      int h2_value=CalculateHValue(x1, y1, food._point2.x, food._point2.y);
      AddToOpenList(x1, y1, g2_value, h2_value);
    }
    
  }

}

bool Game::CheckIfValidCell(int x, int y) {
  bool IsXInRange=(x>=0&&x<computerSnake.grid_width);
  bool IsYInRange=(y>=0&&y<computerSnake.grid_height);
  for(auto obs : _obstacles) {
    if(ObstaclesHit(x, y))
    return false;
  }
  if((!IsXInRange)&&(!IsYInRange))
    return false;
  return true;
}