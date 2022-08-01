#include<iostream>
#include<algorithm>
#include "InitialSpeed.h"

InitialSpeed::InitialSpeed()
{
   std::cout<<"select the initial speed either slow or fast"<<std::endl;
   std::cout<<"slow => score increases by 1"<<std::endl;
   std::cout<<"fast => score increases by 2"<<std::endl;
   getspeed:
   std::getline(std::cin, speed);
   if(speed=="slow")
   {
       InitialSpeedVal=0.1f;
   }
   else if(speed=="fast")
   {
       InitialSpeedVal=0.4f;
   }
   else
   {
       std::cout<<"Invalid, Enter either slow or fast"<<std::endl;
       goto getspeed;
   }
   
}


