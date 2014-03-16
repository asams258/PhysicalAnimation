//
//  ParticleList.h
//  SPH Fluids
//
//  Created by Arthur Sams on 3/15/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#ifndef __SPH_Fluids__ParticleList__
#define __SPH_Fluids__ParticleList__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include "Particle.h"
#include "Constants.h"

class ParticleList{
private:
  std::unordered_map<int,vector<particle *>> lst;
  int z_dim = Constants::grid_dim[2]/Constants::h;
  int y_dim = Constants::grid_dim[1]/Constants::h;
  int x_dim = Constants::grid_dim[0]/Constants::h;
  //For loop nested z y x, so y*x in each z line, x in each y
  int z_space = y_dim * x_dim;
  int y_space = x_dim;
  
public:
  ParticleList () {};
  //For Debugging
  void printPrivates (){
    std::cout<< "x,y,z dims " << x_dim << " " << y_dim << " " << z_dim << std::endl;
    std::cout<< "y,z spacing " << y_space << " " << z_space << std::endl;
  }
  //Empties the Particle List
  void clear (){
    lst.clear();
  }
  /*
  void printTree (){
    lst.
  }*/
  void insertAll (vector<particle *> parts){
    for (std::vector<particle *>::iterator it = parts.begin() ; it != parts.end(); ++it){
      insert(*(*it));
    }
  }
  
  void insert (particle & part){
    int key = 0;
    getKey(part,key);
    std::unordered_map<int,vector<particle*>>::iterator got = lst.find (key);
    if (got == lst.end()){
      vector<particle *> tmp;// = * new vector<particle *>;
      tmp.push_back(&part);
      lst[key] = tmp;
    }
    else{
      (got->second).push_back(&part);
    }
  }
  
  //copies values located at key to the output list
  void getIndexed (int const key, vector<particle *> & olst){
    std::unordered_map<int,vector<particle*>>::const_iterator got = lst.find(key);
    if (got != lst.end()){
      olst.insert(olst.end(),(got->second).begin(),(got->second).end());
    }
    
  }
  
  void findNeighbors (particle & part){
    vector<particle *> potentials;
    int key;
    double _x;
    double _y;
    double _z;
    for (double x = -Constants::h; x<=Constants::h; x+=Constants::h){
      for (double y = -Constants::h; y<=Constants::h; y+=Constants::h){
        for (double z = -Constants::h; z<=Constants::h; z+=Constants::h){
          _x = part.p[0]+x;
          _y = part.p[1]+y;
          _z = part.p[2]+z;
          if (_x < 0 || _y < 0 || _z < 0){
            //skip it
            
          }
          else if (_x > Constants::grid_dim[0] || _y > Constants::grid_dim[1] || _z > Constants::grid_dim[2]){
            //skip it
          }
          else{
            //find neighbors
            getKey(_x, _y, _z,key);
            getIndexed(key, potentials);
          }
        }//end z
      }// end y
    }// end x
    part.getNeighbors(potentials);
  }
  
  void getKey(double x, double y, double z, int & key){
    //put overflow saftey on particle so it cant be > than dimension, clamp to end
    key = 0;
    double p [3];
    p[0] = x;
    p[1] = y;
    p[2] = z;
    int v [3];
    for (int i = 0; i<3;++i){
      if (p[i] >= Constants::grid_dim[i]){
        v[i] = int(Constants::grid_dim[i]/Constants::h) - 1;
      }
      else if (p[i] <= 0){
        v[i] = 0;
      }
      else{
        v[i] = int(p[i]/Constants::h);
      }
    }
    key += v[0];
    key += v[1]*y_space;
    key += v[2]*z_space;
  }
  
  void getKey(particle & part, int & key){
    key = 0;
    //put overflow saftey on particle so it cant be > than dimension, clamp to end
    int v [3];
    for (int i = 0; i<3;++i){
      if (part.p[i] >= Constants::grid_dim[i]){
        v[i] = int(Constants::grid_dim[i]/Constants::h) - 1;
      }
      else if (part.p[i] <= 0){
        v[i] = 0;
      }
      else{
        v[i] = int(part.p[i]/Constants::h);
      } 
    }
    key += v[0];
    key += v[1]*y_space;
    key += v[2]*z_space;
  }
  
  void printStruct (){
    vector<particle *> inner;
    vector<int> ct;
    ct.resize(100);
    int q = 0;
    for (std::unordered_map<int,vector<particle *>>::iterator it=lst.begin(); it!=lst.end(); ++it){
      std::cout << it->first << " => "<< '\n';
      q = (it->first);
      ct[q] = 1;
      for (std::vector<particle*>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2){
        std::cout << (**it2).p[0] << " " << (**it2).p[1] << " " << (**it2).p[2] << std::endl;
      }
    }/*
    for (int i = 0; i < ct.size();  ++i){
      if (ct.at(i) == 1)
        std::cout<<i<<std::endl;
    }*/
    
  }
  
};
#endif /* defined(__SPH_Fluids__ParticleList__) */
