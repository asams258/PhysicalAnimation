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
#include "ParticleList.h"

vector<particle *> particles;
ParticleList pList;
int num_parts = 0;
//They space it .05 apart
//Radius of each .015
void initParticles(){
  double i,j,k;
  for(i=.016;i<0.1;i+=.01){
    for (j=.05; j<0.15; j+=.01){
      for (k=.016;k<.1; k+=.01){
        particles.push_back(new particle(i,j,k));
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
    std::cout<< "On Frame: " << f << std::endl;
    //write every Reps iteration for FRAMES
    util::writeParticle(particles,f);
    
    for (int rr = 0; rr < Constants::Reps; ++rr){
      for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
        forces::accumlateExtForces(*(*it));
        (*it)->applyExtForces();
        (*it)->predictPosition();
      }//end init particle advection
      pList.insertAll(particles);
      for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
        (*it)->getNeighbors(particles);
      }
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
          (*it)->cleard_P();
        }
        ++iter;
      }//end while
      
      for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
        (*it)->updateVelocity();
        (*it)->setInitialPos();
        (*it)->resetCorr_Density();
      }
      pList.clear();
    }//end rr loop
  }//end frame loop
  
  return 0;
}//end main

