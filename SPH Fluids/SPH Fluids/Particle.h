//
//  Particle.h
//  SPH Fluids
//
//  Created by Arthur Sams on 2/14/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//
#ifndef __SPH_Fluids__Particle_h
#define __SPH_Fluids__Particle_h
#include "vector"
#include "Constants.h"
#include <iostream>
using std::vector;
static int G_ID = 0;

struct particle{
  const int ID;
  //X Y Z coordinates Y being Vertical
  double p [3];
  double v [3] = {0,0,0};
  double p0 [3];
  double v0 [3] = {0,0,0};
  double d_p_col [3];
  double d_p [3];
  double lambda;
  double rho;
  double f [3]= {0,0,0};
  vector<particle *> neighbors;
  
  particle():ID(G_ID++){}
  
  particle(double x, double y, double z):ID(G_ID++){
    p[0]= x;
    p[1] = y;
    p[2] = z;
    p0[0]= x;
    p0[1] = y;
    p0[2] = z;
  }
  
  particle(double _p [3]):ID(G_ID++){
    for (int i=0; i<3;++i){
      p[i] = _p[i];
      p0[i] = _p[i];
    }
  }
  
  particle(double _p [3], double _v [3], double _f [3]):ID(G_ID++){
    for (int i=0; i<3;++i){
      p[i] = _p[i];
      p0[i] = _p[i];
      v[i] = _v[i];
      v0[i] = _v[i];
    }
  }
  
  //Uses P not p0, as in first iteration we will set P = P0
  void distanceSq (const particle & other, double & t) const{
    t=0;
    for (int i=0; i<3;++i){
      t+= (p[i] - other.p[i])*(p[i] - other.p[i]);
    }
  }
  //first arg is lst of all particles, second is output neighbor list
  void getNeighbors (const vector<particle *> & lst){
    double val = 0;
    for (vector<particle*>::const_iterator it = lst.begin(); it != lst.end(); ++it){
      //std::cout<< "from particle " << it->p[0] << " " << it->p[1] <<" " <<it->p[2] << std::endl;
      distanceSq(*(*it),val);
      if (val < Constants::h_sq){
        neighbors.push_back(*it);
      }
    }//end for
  }
  
  void applyExtForces(){
    //as now only gravity.. save computation
    v[1] = v0[1] + Constants::d_t * f[1];
    /*
    for (int i =0; i<3; ++i){
      v[i] = v0[i] + Constants::d_t * f[i];
    }*/
  }
  
  void predictPosition(){
    for (int i=0; i<3; ++i){
      p[i] = p0[i]+ Constants::d_t * v[i];
    }
  }
  
  void cleard_P(){
    for (int i=0; i<3;++i){
      d_p[i] = 0;
      d_p_col[i] = 0;
    }
  }
  
  void updatePosition(){
    for (int i=0; i<3; ++i){
      p[i] = p[i] + d_p_col[i] + d_p[i];
    }
  }
  void restartParticle(){
    for (int i=0; i<3;++i){
      v0[i]= 1/Constants::d_t * (p[i] - p0[i]);
      p0[i] = p[i];
      f[i] = 0;
      d_p[i] = 0;
      d_p_col[i] = 0;
    }
    neighbors.clear();
    lambda = 0;
    rho = 0;
  }
};



#endif /* defined(__SPH_Fluids__Utils__) */



