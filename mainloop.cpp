#include "gameobject.h"
#include "game.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <csignal>
//time code
//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c

bool flagLoop=true;
void raiseFlag(int param){
  flagLoop = false;
}

int main()
{
  Game game = Game();
  signal(SIGINT,raiseFlag);
  while(flagLoop=true){

    auto current = std::chrono::system_clock::now();
    game.update(current);
    std::cout<<"use ctrlC to quit." << std::endl;
    
  }
}
