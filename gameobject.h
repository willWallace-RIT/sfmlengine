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
    if(sqrMag()>0.0f){ 
      normV.x = (1.0f/sqrMag())*x;
      normV.y = (1.0f/sqrMag())*y;
    }
    else{
      normV.x = 0.0f;
      normV.y = 0.0f;
    }
    return normV;
  }
  float sqrMag(){
    return (x*x)+(y*y);
  }
};

struct game_object_t
{
  struct vec2_t position;
  struct vec2_t accel;
  struct vec2_t velocity;
};
