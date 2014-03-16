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
  for(i=.00;i<0.2;i+=.03){
    for (j=.00; j<0.3; j+=.03){
      for (k=.00;k<.05; k+=.01){
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
  
  particle p = particle(0.00, 0.03, 0.03);
  particle p2 = particle(0.00, 0.03, 0.03);
  p2.getNeighbors(particles);
  
  //pList.printStruct();
  pList.findNeighbors(p);
  std::cout<< "Number of neighbors: " << p.neighbors.size() << std::endl;
  for (std::vector<particle *>::iterator it = p.neighbors.begin() ; it != p.neighbors.end(); ++it){
    std::cout << (**it).p[0] << " " << (**it).p[1] << " " << (**it).p[2] << std::endl;
  }
  std::cout<< "neighbors for clone other method: " << p2.neighbors.size() << std::endl;
  
  for (std::vector<particle *>::iterator it = p2.neighbors.begin() ; it != p2.neighbors.end(); ++it){
    std::cout << (**it).p[0] << " " << (**it).p[1] << " " << (**it).p[2] << std::endl;
  }
  return 0;
}

