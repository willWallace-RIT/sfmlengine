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
         glViewport(0,0,event.size.width, event.size.height);
      }
        
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        running = false;
      }

    }
      
      
      auto current = std::chrono::system_clock::now();
      game.update(current,&window);

    }

  
}
