#pragma once
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
    normV.x = fastInv(sqrMag())*x;
    normV.y = fastInv(sqrMag())*y;
    return normV;
  }
  float sqrMag(){
    return (x*x)+(y*y);
  }

  //fast inverse squareroot from quake III
  float fastInv(float number){
    long i;
    float x2,y;
    const float threehalfs = 1.5f;
    x2 = number*0.5f;
    y=number;
    i = *(long *)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));
    return y;
  }
};

struct game_object_t
{
  struct vec2_t position;
  struct vec2_t accel;
  struct vec2_t velocity;
};
