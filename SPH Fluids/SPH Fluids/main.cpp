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
  for(i=.3;i<=0.65;i+=.05){
    for (j=.55; j<=0.902; j+=.05){
      for (k=.3;k<=.65; k+=.05){
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
        //MERGE THESE 2 FOR LOOPS only sperated so i can debug
        for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
          (*it)->updatePosition();
          //(*it)->cleard_P();
        }
        util::writeDebug(particles,f,iter);
        for (std::vector<particle *>::iterator it = particles.begin() ; it != particles.end(); ++it){
          //(*it)->updatePosition();
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

