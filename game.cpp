#include "game.h"
#include<chrono>
#include <string>
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
  t += elapsed.count()*MILLI_TO_SEC;
  printT += elapsed.count()*MILLI_TO_SEC;
  //std::cout<<"elapsed:"<<elapsed.count()*MILLI_TO_SEC<<std::endl; 
   
  if(t>=FPS){
    t=0;
    follow_target(elapsed.count()*MILLI_TO_SEC,&a,&b);
  
    vec2_t dist = a.position.addX(b.position.muxX(-1.0f));
    //std::cout<<"dist"<<dist.sqrMag()<<std::endl;
    if(dist.sqrMag()<1.0f){
      a.position.x = randFloat().randRange(-25.0,25.0);
      a.position.y = randFloat().randRange(-25.0,25.0);
    }

  }
  if(printT >=PRINT_FPS){
    printT=0;
    print();
  
    //char a;
    //cin>>a;
  }
  current = prevTime;
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
  
  cout<<"b velocity.:("<<b.velocity.x<<","<<b.velocity.y<<")"<<endl;
  cout<<"b accel.:("<<b.accel.x<<","<<b.accel.y<<")"<<endl;
}

void Game::follow_target(float dt,const struct game_object_t* target, struct game_object_t* follower){
  vec2_t accelVec = target->position.addX(follower->position.muxX(-1.0f));
  vec2_t desiredAccel = follower->accel.addX(accelVec.muxX(dt));
  if(desiredAccel.sqrMag() > maxAccel*maxAccel)
    desiredAccel = desiredAccel.norm().muxX(maxAccel);
  follower->accel=desiredAccel;
  vec2_t desiredVelocity = follower->velocity.addX(follower->accel.muxX(dt));
  if(desiredVelocity.sqrMag() > maxVel*maxVel){
    desiredVelocity = desiredVelocity.norm().muxX(maxVel);}
  follower->velocity = desiredVelocity;
  
  vec2_t desiredPosition = follower->position.addX(follower->velocity.muxX(dt));
  vec2_t displacement = desiredPosition.addX(follower->position.muxX(-1.0f));
  if(displacement.sqrMag() >accelVec.sqrMag() ){
    follower->position = target->position.muxX(1.0f);
  }
  else{
    follower->position = desiredPosition;
  }
   
}

