#ifndef OBSTACLE_H
#define OBSTACLE_H

#include<random>
#include<vector>
#include"SDL2/SDL.h"
#include"snake.h"

class Obstacle {
    public:
    Obstacle(int x, int y);
    bool ObstacleHit(SDL_Point &sp);
    bool ObstacleHit(int x, int y);
    void SetPosition(int x, int y);
    
    SDL_Point kCordinate;
};

#endif


