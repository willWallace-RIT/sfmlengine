#include "gameobject.h"
#include "game.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <csignal>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
//time code
//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c


int main()
{
  //using fullscreen so I don't have to adjust units for now.
  sf::RenderWindow window(sf::VideoMode(1920,1080), "OpenGL", sf::Style::Fullscreen, sf::ContextSettings(32));
  window.setActive(true);
  sf::Event event;
  glEnable(GL_TEXTURE_2D);
  Game game = Game();
  bool running = true;
  while(running){
    while(window.pollEvent(event)){

      if(event.type == sf::Event::Closed)
      {
        running=false;
      }

      else if(event.type == sf::Event::Resized)
      {
         //while resize is an option, an enhancement would be to convert width, height, gameobject
         //position variables, physics to a modifiable units so it can match screen space, time consuming for now so just
         //using fullscreen is the solution for now
         glViewport(0,0,event.size.width, event.size.height);
      }
      //Quit input placed outside of game state so I don't have to pass running bool pointer into
      //game class or update function  
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        running = false;
      }

    }
      
      
      auto current = std::chrono::system_clock::now();
      game.update(current,&window);

    }

  
}
