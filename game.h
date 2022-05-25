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
  GameState gS;
  std::chrono::time_point<std::chrono::system_clock> prevTime;
  float t;
  float printT;
  game_object_t a;
  game_object_t b;
  float maxVel=100;
  const float DIST_UNIT = 2.0f;
  const float RADIUS = 16.0f;
  const float FOLLOWRADIUS = 40.0f;
  const float width = 1920.0f;
  const float height = 1080.0f;
  float accelx=0;
  float accely=0;
  float accelspeed = 500.0f;
  float maxAccel=10;
  float totalTime=0.0;
  float accelMux =1.0f;
  float accelAdd = 0.5f;
  const int muxTime = 10;
  int floorVal = 0;
  const float FPS = 1.0f/60.0f;
  const float PRINT_FPS = 0.5f;
  const float MILLI_TO_SEC = 1.0f/1000.0f;
  
  sf::Texture targetTexture;
  sf::Texture followerTexture;
  sf::Sprite targetSprite;
  sf::Sprite followerSprite;
  sf::Font* pS2Pfont;
  
};


