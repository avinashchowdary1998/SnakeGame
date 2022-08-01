#ifndef INITIALSPEED_H
#define INITIALSPEED_H

#include <string>

class InitialSpeed 
{
    public:
    InitialSpeed();
    float GetInitialSpeedVal() const
    {
        return InitialSpeedVal;
    }
    std::string GetSpeed() const {
        return speed;

    }

    private:
    std::string speed;
    float InitialSpeedVal;
};
#endif
