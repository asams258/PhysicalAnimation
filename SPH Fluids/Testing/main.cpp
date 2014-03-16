//
//  main.cpp
//  Testing
//
//  Created by Arthur Sams on 3/8/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Particle.h"
#include "ParticleList.h"

vector<particle *> particles;

int num_parts = 0;
//They space it .05 apart
//Radius of each .015
void initParticles(){
  double i,j,k;
  for(i=.05;i<0.2;i+=.05){
    for (j=.05; j<0.2; j+=.05){
      for (k=.05;k<.055; k+=.001){
        particles.push_back(new particle(i,j,k));
        ++num_parts;
      }//end k
    }//end j
  }//end i
  std::cout<<"Particles in Sim: " << num_parts <<std::endl;
}

int main(int argc, const char * argv[])
{
  initParticles();
  ParticleList pList;
  pList.insertAll(particles);
  int v;
  
  pList.getKey(*particles[0], v);
  std::cout << "Particle 0: " << v << std::endl;
  particle p = *particles[2];
  std::cout << p.p[0] << " " << p.p[1] << " " << p.p[2] << std::endl;
  particle r = *particles[3];
  std::cout << r.p[0] << " " << r.p[1] << " " << r.p[2] << std::endl;
  double t =0;
  p.distanceSq(r,t);
  std::cout << "Dist value " << t << " tolerance " << Constants::h_sq << std::endl;
  
  pList.findNeighbors(p);
  std::cout<< "Number of neighbors: " << p.neighbors.size() << std::endl;
  for (std::vector<particle *>::iterator it = p.neighbors.begin() ; it != p.neighbors.end(); ++it){
    std::cout << (**it).p[0] << " " << (**it).p[1] << " " << (**it).p[2] << std::endl;
  }
  return 0;
}

