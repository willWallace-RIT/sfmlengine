#include "game.h"
#include<chrono>
#include <string>
#include <bit>
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
  b.accel.x=0.0f;
  b.accel.y=0.0f;
}
void Game::update(std::chrono::time_point<std::chrono::system_clock> current){
  std::chrono::duration<float> elapsed = (current-prevTime);
  
  //cout<<t<<endl;
  t += elapsed.count();
  printT += elapsed.count();
  if(t>=FPS){
    follow_target(t,&a,&b);
  
    t-=FPS;
    vec2_t dist = a.position.addX(b.position.muxX(-1.0f));
    //std::cout<<"dist"<<dist.sqrMag()<<std::endl;
    if(dist.sqrMag()<(RADIUS)*(RADIUS)){
      a.position.x = randFloat().randRange(-100.0f,100.0f);
      a.position.y = randFloat().randRange(-100.0f,100.0f);

      b.velocity.x=0.0f;
      b.velocity.y=0.0f;

      b.accel.x=0.0f;
      b.accel.y=0.0f;
    }

  }
  if(printT >=PRINT_FPS){
    printT-=PRINT_FPS;
    print();
  
    //char a;
    //cin>>a;
  }
  prevTime= current;
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
  float maxTime = (dt>1.0f)?1.0f:dt;
  vec2_t desiredAccel = follower->accel.addX(accelVec.norm().muxX(maxTime));
  //print(); 
  //cout<<"dt:"<<dt<<endl; 
  if(desiredAccel.sqrMag() > maxAccel*maxAccel)
    desiredAccel = desiredAccel.norm().muxX(maxAccel);
  follower->accel=desiredAccel;
  
  //cout<<"des accel.:("<<desiredAccel.x<<","<<desiredAccel.y<<")"<<endl;
  vec2_t desiredVelocity = follower->velocity.addX(follower->accel.muxX(maxTime));
  if(desiredVelocity.sqrMag() > maxVel*maxVel){
    desiredVelocity = desiredVelocity.norm().muxX(maxVel);}
  follower->velocity = desiredVelocity;
  vec2_t currentPos = follower->position.muxX(1.0);
  vec2_t desiredPosition = follower->position.addX(follower->velocity.muxX(maxTime));
  vec2_t displacement = desiredPosition.addX(follower->position.muxX(-1.0f));
  vec2_t normDisplace =  displacement.norm();
  float mag = displacement.mag();
  //cout<<"mag:"<<mag<<endl;
  float divIter = mag/DIST_UNIT;
  int numOfIterations = static_cast<int>(divIter);
  bool isInt = (divIter==static_cast<int>(divIter));
  numOfIterations+=(isInt)?0:1;
  //cout<<"iter:"<<numOfIterations<<endl;
  float cumulativeDist = 0;
  //cout<<"float"<<sizeof(float)<<endl; 
  //cout<<"long"<<sizeof(long)<<endl;
  //string b;
  //cin>>b;
  for(int i = 0; i<numOfIterations;i++){
    
    if(!(isInt)&&i == numOfIterations-1){
      cumulativeDist += (divIter-(static_cast<float>(static_cast<int>(divIter))))*DIST_UNIT;
    }
    else{
      cumulativeDist += DIST_UNIT;
    }
    follower->position = currentPos.addX(normDisplace.muxX(cumulativeDist));
    if(follower->position.addX(target->position.muxX(-1.0)).sqrMag()<RADIUS*RADIUS){
      return;
    }
  }
  
   
}

