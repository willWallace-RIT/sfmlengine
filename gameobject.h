#pragma once
#include<cstdint>
#include<bit>
#include<limits>
#include<math.h>
struct vec2_t{

  float x,y;
  void add(vec2_t other){
   x+=other.x;
   y+=other.y;
  }
  
  vec2_t addX(vec2_t other) const{
    vec2_t sum = {};
    sum.x=x+other.x;
    sum.y=y+other.y;
    return sum;
  }
  void sub(vec2_t other){
    x-=other.x;
    y-=other.y;
  }
  void mux(float scalar){
    x*=scalar;
    y*=scalar;
    
  }
  vec2_t muxX(float scalar) const{
    vec2_t prod = {};
    prod.x=x*scalar;
    prod.y=y*scalar;
    return prod;
  }
  vec2_t norm(){
    vec2_t normV = {}; 
     
  
    normV.x = (abs(x)>0.000000000000001f)?(1.0f/sqrt(sqrMag()))*x:0.0f;
    
    normV.y = (abs(y)>0.000000000000001f)?(1.0f/sqrt(sqrMag()))*y:0.0f; 
    return normV;
  }
  float sqrMag(){
    return (x*x)+(y*y);
  }
  float mag(){
    return sqrt(sqrMag());
  }
  //fast inverse squareroot from quake III
  float fastInv(float number){
      double y = static_cast<double>(number);
      uint64_t x2 = y * 0.5;

      std::int64_t i = *(std::int64_t *) &y;
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y= *(double *) &i;
    y *= y*(1.5 -  (x2*y*y));

    return static_cast<float>(y);
    
    
  }
};

struct game_object_t
{
  struct vec2_t position;
  struct vec2_t accel;
  struct vec2_t velocity;
};
