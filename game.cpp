#define SFML_STATIC
#include "game.h"
#include<chrono>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <bit>
#include <math.h>
#include "randomGen.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
Game::Game(){
  prevTime = std::chrono::system_clock::now();  
  t=0;
  a ={};
  printT =0.0f;
  b = {};
  a.position.x = randFloat().randRange(0.0f,width);
  a.position.y = randFloat().randRange(0.0f,height);
  b.position.x = randFloat().randRange(0.0f,width);
  b.position.y = randFloat().randRange(0.0f,height);
  a.velocity.x=0.0f;
  a.velocity.y=0.0f;
  b.velocity.x=0.0f;
  b.velocity.y=0.0f;
  a.accel.x=0.0f;
  b.accel.x=0.0f;
  b.accel.y=0.0f;

  totalTime=0.0;
  accelMux =1.0f;
  floorVal = 0;
  followerTexture.loadFromFile("assets/follower.png",sf::IntRect(0,0,16,16));
  targetTexture.loadFromFile("assets/target.png",sf::IntRect(0,0,16,16));
  gS = GameState::mainMenu; 
  targetTexture.setSmooth(false);
  followerTexture.setSmooth(false);
  targetSprite.setTexture(targetTexture);
  followerSprite.setTexture(followerTexture);
  targetSprite.setOrigin(16,16);
  followerSprite.setOrigin(16,16);
  targetSprite.setPosition(sf::Vector2f(a.position.x,a.position.y));
  followerSprite.setPosition(sf::Vector2f(b.position.x,b.position.y));
  followerSprite.setScale(2.0f,2.0f);
  targetSprite.setScale(2.0f,2.0f);
  pS2Pfont = new sf::Font();
  std::ofstream file("sfml-log.txt");
  std::streambuf* prev = sf::err().rdbuf(file.rdbuf()); 
  pS2Pfont->loadFromFile("assets/PressStart2PRegular.ttf");


}

void Game::reset(){

  prevTime = std::chrono::system_clock::now();  
  t=0;
  a ={};
  printT =0.0f;
  b = {};
  a.position.x = randFloat().randRange(0.0f,width);
  a.position.y = randFloat().randRange(0.0f,height);
  b.position.x = randFloat().randRange(0.0f,width);
  b.position.y = randFloat().randRange(0.0f,height);
  a.velocity.x=0.0f;
  a.velocity.y=0.0f;
  b.velocity.x=0.0f;
  b.velocity.y=0.0f;
  a.accel.x=0.0f;
  b.accel.x=0.0f;
  b.accel.y=0.0f;

  totalTime=0.0;
  accelMux =1.0f;
  floorVal = 0;

  targetSprite.setPosition(sf::Vector2f(a.position.x,a.position.y));
  followerSprite.setPosition(sf::Vector2f(b.position.x,b.position.y));
}
void Game::drawText(sf::Font* font,sf::RenderWindow* window,std::string text, int size,sf::Color color,float x, float y){
  sf::Text txt;
  txt.setFont(*font);
  txt.setString(text);
  txt.setCharacterSize(size);
  //txt.setColor(color);
  txt.setFillColor(color);
  txt.setOutlineColor(color);
  txt.setPosition(x,y);
  window->draw(txt);
}
void Game::update(std::chrono::time_point<std::chrono::system_clock> current,sf::RenderWindow* window){
  std::chrono::duration<float> elapsed = (current-prevTime);
  if(gS == GameState::mainMenu){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawText(pS2Pfont,window,"followerDemo",32,sf::Color::Red,300,100);
    drawText(pS2Pfont,window,"Press Z for chase game",12,sf::Color::Red,200,500);

    drawText(pS2Pfont,window,"Press X for follower demo",12,sf::Color::Red,200,600);

    drawText(pS2Pfont,window,"Press Q for Quit",12,sf::Color::Red,200,700);


    drawText(pS2Pfont,window,"(In Game press Press M for menu)",12,sf::Color::Red,200,800);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
      gS = GameState::chaseGame;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
      gS = GameState::follower;
    }

    window->display();
  }

  if(gS == GameState::gameOver){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawText(pS2Pfont,window,"GAMEOVER",32,sf::Color::Red,300,100);


    std::stringstream sstr;
    sstr<<std::fixed<<std::setprecision(2)<<totalTime; 
    drawText(pS2Pfont,window,"Time Survived: "+sstr.str(),32,sf::Color::Red,100,300);
    drawText(pS2Pfont,window,"Press Z for chase game",12,sf::Color::Red,200,500);

    drawText(pS2Pfont,window,"Press X for follower demo",12,sf::Color::Red,200,600);

    drawText(pS2Pfont,window,"Press Q for Quit",12,sf::Color::Red,200,700);

    drawText(pS2Pfont,window,"(In Game press Press M for menu)",12,sf::Color::Red,200,800);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
      gS = GameState::chaseGame;
      reset();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
      gS = GameState::follower;
      reset();
    }

    window->display();
  }
  if(gS == GameState::chaseGame||gS == GameState::follower){ 
    //cout<<t<<endl;
    t += elapsed.count();
    printT += elapsed.count();
    totalTime+=elapsed.count();
    if(gS == GameState::chaseGame){
      if(((int)floorf(totalTime)!=floorVal)){
        floorVal=(int)floorf(totalTime);
        if(((int)floorf(totalTime))%muxTime==0){ 
          accelMux += accelAdd;
        }
      }
    }

    if(t>=FPS){

      vec2_t acc = {};
      acc.x = accelx*t;
      acc.y = accely*t;
      accelx =0.0f;
      accely =0.0f;
      vec2_t desiredAccel = a.accel.addX(acc.muxX(accelspeed));
      if(desiredAccel.sqrMag() > maxAccel*maxAccel){
        desiredAccel = desiredAccel.norm().muxX(maxAccel);
      }
      a.accel = desiredAccel;
      vec2_t desiredVelocity=a.velocity.addX(a.accel.muxX(t));

      if(desiredVelocity.sqrMag() > maxVel*maxVel){
        desiredVelocity = desiredVelocity.norm().muxX(maxVel);
      }
      a.velocity = desiredVelocity;

      a.position = a.position.addX(a.velocity.muxX(t));

      a.position.x = min(width-32.0f,max(32.0f,a.position.x));

      a.position.y = min(height-32.0f,max(32.0f,a.position.y));
      if(a.position.y == height-32.0f|| a.position.y == 32.0f){
        //a.accel.y=0;
        a.velocity.y=0;
      }

      if(a.position.x == width-32.0f|| a.position.x == 32.0f){
        //a.accel.x=0;
        a.velocity.x=0;
      }

      follow_target(t,&a,&b);




      t-=FPS;
      vec2_t dist = a.position.addX(b.position.muxX(-1.0f));
      //std::cout<<"dist"<<dist.sqrMag()<<std::endl;
      if(gS == GameState::chaseGame){
        if(dist.sqrMag()<(RADIUS)*(RADIUS)){
          //a.position.x = randFloat().randRange(0.0f,width);
          //a.position.y = randFloat().randRange(0.0f,height);

          //b.velocity.x=0.0f;
          //b.velocity.y=0.0f;

          //b.accel.x=0.0f;
          //b.accel.y=0.0f;
          gS = GameState::gameOver;
        }
      }else{
        if(dist.sqrMag()<(FOLLOWRADIUS)*(FOLLOWRADIUS)){

          b.velocity.x=0.0f;
          b.velocity.y=0.0f;

          b.accel.x=0.0f;
          b.accel.y=0.0f;
        }
      }

      targetSprite.setPosition(sf::Vector2f(a.position.x,a.position.y));
      followerSprite.setPosition(sf::Vector2f(b.position.x,b.position.y));


      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      std::stringstream sstr;
      sstr<<std::fixed<<std::setprecision(2)<<totalTime; 
      drawText(pS2Pfont,window,"time survived: "+sstr.str(),32,sf::Color::Red,100,100);
      //window->clear();
      window->draw(targetSprite);
      window->draw(followerSprite);
      window->display();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      accely=-1.0f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
      accely=1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      accelx=-1.0;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      accelx=1.0;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
      gS= GameState::mainMenu;
      reset();
      return;
    }
    if(printT >=PRINT_FPS){
      printT-=PRINT_FPS;
      print();

      //char a;
      //cin>>a;
    }
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
Game::~Game(){
  delete pS2Pfont;
}

void Game::follow_target(float dt,const struct game_object_t* target, struct game_object_t* follower){
  vec2_t accelVec = target->position.addX(follower->position.muxX(-1.0f));
  float maxTime = (dt>1.0f)?1.0f:dt;
  vec2_t desiredAccel = follower->accel.addX(accelVec.norm().muxX(maxTime*accelspeed));
  //print(); 
  //cout<<"dt:"<<dt<<endl; 
  if(desiredAccel.sqrMag() > (accelMux*maxAccel)*(accelMux*maxAccel))
    desiredAccel = desiredAccel.norm().muxX(accelMux*maxAccel);
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

    follower->position.x = min(width-32.0f,max(32.0f,follower->position.x));

    follower->position.y = min(height-32.0f,max(32.0f,follower->position.y));

    if(follower->position.y == height-32.0f|| follower->position.y == 32.0f){
      //follower->accel.y=0;
      follower->velocity.y=0;
    }

    if(follower->position.x == width-32.0f|| follower->position.x == 32.0f){
      //follower->accel.x=0;
      follower->velocity.x=0;
    }
    if(gS == GameState::chaseGame){
      if(follower->position.addX(target->position.muxX(-1.0)).sqrMag()<RADIUS*RADIUS){
        return;
      }

    }

    else if(gS == GameState::follower){
      if(follower->position.addX(target->position.muxX(-1.0)).sqrMag()<FOLLOWRADIUS*FOLLOWRADIUS){
        return;
      }

    }

  }
}

