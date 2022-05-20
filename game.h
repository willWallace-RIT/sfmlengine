#include "gameobject.h"
#include <chrono>
#include <iostream>
class Game{
  public:
  Game();
  Game(const Game& other);
  virtual Game& operator =(const Game& other);
  void update(std::chrono::time_point<std::chrono::system_clock> current);
  void follow_target(const struct game_object_t* target, struct game_object_t* follower);
  void print();
  private:
  std::chrono::time_point<std::chrono::system_clock> prevTime;
  float t;
  float printT;
  game_object_t a;
  game_object_t b;
  const float fps = 1.0/60.0f;
  float printfps = 1.0;
};


