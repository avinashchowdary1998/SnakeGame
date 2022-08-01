#include<iostream>
#include"obstacle.h"
#include"SDL2/SDL.h"

Obstacle::Obstacle(int x, int y) {
    kCordinate.x=x;
    kCordinate.y=y;

}

bool Obstacle::ObstacleHit(SDL_Point &sp) {
    if((sp.x==kCordinate.x) && (sp.y==kCordinate.y)) {

        return true;
    }

    else
    {
        return false;
    }
    
}

bool Obstacle::ObstacleHit(int x, int y) {
    if((x==kCordinate.x) && (y==kCordinate.y)) {

        return true;
    }

    else
    {
        return false;
    }
    
}

void Obstacle::SetPosition(int x, int y) {
    kCordinate.x=x;
    kCordinate.y=y;
    
}


