#include "gameobject.h"
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Game{
  public:
  Game();
  Game(const Game& other);
  virtual Game& operator =(const Game& other);
  void update(std::chrono::time_point<std::chrono::system_clock> current,sf::RenderWindow* window);
  void follow_target(float dt,const struct game_object_t* target, struct game_object_t* follower);
  void print();

  private:
  std::chrono::time_point<std::chrono::system_clock> prevTime;
  float t;
  float printT;
  game_object_t a;
  game_object_t b;
  float maxVel=100;
  const float DIST_UNIT = 2.0f;
  const float RADIUS = 16.0f;
  const float width = 1920.0f;
  const float height = 1080.0f;
  float accelx=0;
  float accely=0;
  float accelspeed = 500.0f;
  float maxAccel=10;
  const float FPS = 1.0f/60.0f;
  const float PRINT_FPS = 0.5f;
  const float MILLI_TO_SEC = 1.0f/1000.0f;
  sf::Texture targetTexture;
  sf::Texture followerTexture;
  sf::Sprite targetSprite;
  sf::Sprite followerSprite;
};


