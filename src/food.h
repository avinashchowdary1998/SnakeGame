#ifndef FOOD_H
#define FOOD_H

#include"SDL2/SDL.h"

class Food {
    public:
    //enum class FoodType {FoodTypeRed, FoodTypeGreen};
    Food ();
    //FoodType GetFoodType() const;
    //int GetX1() const;
    //int GetY1() const;
    //int GetX2() const;
    //int GetY2() const;

    //private:
    SDL_Point _point1;
    SDL_Point _point2;
    //FoodType _foodType;
};

#endif
