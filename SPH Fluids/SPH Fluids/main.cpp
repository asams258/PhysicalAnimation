//
//  main.cpp
//  SPH Fluids
//
//  Created by Arthur Sams on 2/12/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Particle.h"
#include "Constants.h"
#include "Util.h"
#include "Particle.h"
#include "Force.h"

//consider deque
//using std::vector;

vector<particle> particles;

int num_parts = 0;
//They space it .05 apart
//Radius of each .015
void initParticles(){
  double i,j,k;
  for(i=4;i<4.2;i+=.05){
    for (j=1; j<1.2; j+=.05){
      for (k=4;k<4.2; k+=.05){
        particles.push_back(particle(i,j,k));
        ++num_parts;
      }//end k
    }//end j
  }//end i
  std::cout<<"Particles in Sim: " << num_parts <<std::endl;
}

int main () {
  int iter;
  initParticles();
  //double * force;
  for (int f = 0; f<Constants::FRAMES; ++f){
    iter = 0;
    //run logic
    util::writeParticle(particles,f);
    for (std::vector<particle>::iterator it = particles.begin() ; it != particles.end(); ++it){
      //Speed this up for realz from O(n^2) to better
      it->getNeighbors(particles);
      forces::accumlateExtForces(*it);
      it->applyExtForces();
      it->predictPosition();
    }//end init particle advection
    while (iter < Constants::SolverIterations){
      for (std::vector<particle>::iterator it = particles.begin() ; it != particles.end(); ++it){
        forces::computeDensity(*it);
        forces::computeLambda(*it);
      }
      for (std::vector<particle>::iterator it = particles.begin() ; it != particles.end(); ++it){
        forces::computeDeltaP(*it);
        forces::boundayConstraint(*it);
      }
      for (std::vector<particle>::iterator it = particles.begin() ; it != particles.end(); ++it){
        it->updatePosition();
      }
    }//end while
    for (std::vector<particle>::iterator it = particles.begin() ; it != particles.end(); ++it){
      it->restartParticle();
    }
    std::cout<<"On Frame: " << f << std::endl;
  }//end frame loop
  
  return 0;
}//end main
