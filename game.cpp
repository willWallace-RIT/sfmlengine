#include "game.h"
#include<chrono>
#include "randomGen.h"
using namespace std;
Game::Game(){
  prevTime = std::chrono::system_clock::now();  t=0;
  a ={};
  printT =0.0f;
  b = {};
  a.position.x = randFloat().randRange(-25.0,25.0);
  a.position.y = randFloat().randRange(-25.0,25.0);
  b.position.x = randFloat().randRange(-25.0,25.0);
  b.position.y = randFloat().randRange(-25.0,25.0);
  a.velocity.x=0.0f;
  a.velocity.y=0.0f;
  b.velocity.x=0.0f;
  b.velocity.y=0.0f;
  a.accel.x=0.0f;
  a.accel.y=0.0f;
  b.accel.x=0.0f;
  b.accel.y=0.0f;
}
void Game::update(std::chrono::time_point<std::chrono::system_clock> current){
  std::chrono::duration<float> elapsed = current-prevTime;
  t += elapsed.count();
  printT += elapsed.count();
  
  
  if(t>=fps){
    t-=fps;
    follow_target(&a,&b);
  

  }
  if(printT >=printfps){
    print();
  }
  
}
Game::Game(const Game& other){
  prevTime = other.prevTime;
  a=other.a;
  b=other.b;
  t=other.t;  

}
Game& Game::operator=(const Game& other){
  prevTime = other.prevTime;
  a=other.a;
  b=other.b;
  t=other.t;
  return *this;
}

void Game::print(){
  cout<<"a position:("<<a.position.x<<","<<a.position.y<<")"<<endl;

  cout<<"b position:("<<b.position.x<<","<<b.position.y<<")"<<endl;
  
  cout<<"b velocity.:("<<a.position.x<<","<<a.position.y<<")"<<endl;
}

void Game::follow_target(const struct game_object_t* target, struct game_object_t* follower){
  vec2_t accelVec = target->position.addX(follower->position.muxX(-1.0f));
  vec2_t desiredAccel = follower->accel.addX(follower->accel)
}

