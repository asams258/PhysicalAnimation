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

vector<particle *> particles;

int num_parts = 0;
//They space it .03 apart
//Radius of each .015
void initParticles(){
  double i,j,k;
  for(i=4;i<4.4;i+=.03){
    for (j=.2; j<0.4; j+=.03){
      for (k=4;k<4.4; k+=.03){
        particles.push_back(new particle(i,j,k));
        ++num_parts;
      }//end k
    }//end j
  }//end i
  std::cout<<"Particles in Sim: " << num_parts <<std::endl;
}

//Clean up memory allocation
void deleteParticles(){
  for (int x = 0; x < particles.size();++x){
    delete particles.back();
    particles.pop_back();
  }
}

int main () {
  int iter;
  initParticles();
  
  for (int f = 0; f<Constants::FRAMES; ++f){
    util::writeParticle(particles,f);
    //Write after Reps iterations of logic, so each frame is made of Reps iterations
    for (int r = 0; r < Constants::Reps; ++r){
      
      for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
        //Speed this up from O(n^2) to better / oct tree?
        (*it)->getNeighbors(particles);
        forces::accumlateExtForces(*(*it));
        (*it)->applyExtForces();
        (*it)->predictPosition();
      }//end init particle advection
      
      iter = 0;
      while (iter < Constants::SolverIterations){
        for (std::vector<particle*>::iterator it = particles.begin() ; it != particles.end(); ++it){
          forces::computeDensity(*(*it));
          forces::computeLambda(*(*it));
        }
        
        for (std::vector<particle*>::iterator it = particles.begin() ; it != particles.end(); ++it){
          forces::computeDeltaP(*(*it));
          forces::boundayConstraint(*(*it));
        }
        
        for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
          (*it)->updatePosition();
          //Restart d_p_col and d_p, as methods dont do that
          (*it)->cleard_P();
        }
        
        ++iter;
      }//end while
      //Update P0, V0, and set all values to 0
      for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
        (*it)->restartParticle();
      }
      
    }//end reps
    std::cout<<"Finished Frame: " << f << std::endl;
  }//end frame loop
  
  deleteParticles();
  return 0;
}//end main

