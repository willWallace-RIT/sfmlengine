#include "gameobject.h"
#include "game.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <csignal>
//time code
//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c


int main()
{
  Game game = Game();
  while(1){

    auto current = std::chrono::system_clock::now();
    game.update(current);
    
  }
}
