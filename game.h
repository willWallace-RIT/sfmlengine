#include "gameobject.h"
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

enum class GameState{
  mainMenu,
  chaseGame,
  follower,
  gameOver
};

class Game{
  public:
  
  #define P2SDraw(text,x,y,size,color) drawText(pS2Pfont,window,text,size,color,x,y);
  Game();
  Game(const Game& other);
  virtual Game& operator =(const Game& other);
  ~Game();
  void update(std::chrono::time_point<std::chrono::system_clock> current,sf::RenderWindow* window);
  void follow_target(float dt,const struct game_object_t* target, struct game_object_t* follower);
  void print();
  void drawText(sf::Font* font,sf::RenderWindow* window,std::string text, int size,sf::Color color,float x, float y);
  void reset(); 
  private:
  GameState gS; //state of game
  std::chrono::time_point<std::chrono::system_clock> prevTime;// time of last frame
  float t; //value to count and throttle time between frames
  float printT; // value to count and throttle time between prints
  game_object_t a; 
  game_object_t b;
  float maxVel=100;
  const float DIST_UNIT = 2.0f; //Distance of a single unit of movement
  const float RADIUS = 16.0f; // circle collider radius
  const float FOLLOWRADIUS = 40.0f; //follow circle collider radius
  const float width = 1920.0f; // width of screen
  const float height = 1080.0f; // height of screen
  float accelx=0; //input float to cue addition to acceleration vector
  float accely=0; //input float to cue addition to acceleration vector
  float accelspeed = 500.0f; //acceleration modifier for faster reaction in terms of acceleration
  float maxAccel=10; //maximum acceleration in follower demo
  float totalTime=0.0; //total time played
  float accelMux =1.0f; // acceleration modifier to max acceleration ramp of up difficulty in chase
                        // game
  float accelAdd = 2.0f; //represents how much to add to accelMux each time muxTime is reached
  const int muxTime = 10; //increment by which follower accelMax is increased in chase game
  int floorVal = 0; //value to detirmine when a int value is reached
  const float FPS = 1.0f/60.0f; //frames per second to display and run calculations.
  const float PRINT_FPS = 0.5f; //frames per second to print gameobject info
  const float MILLI_TO_SEC = 1.0f/1000.0f; // conversion factor
  
  sf::Texture targetTexture; //texture of target
  sf::Texture followerTexture; // texture of follower
  sf::Sprite targetSprite; 
  sf::Sprite followerSprite; 
  sf::Font* pS2Pfont; //PlayerStart2P font object
  
};


