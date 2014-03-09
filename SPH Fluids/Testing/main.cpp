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

int main(int argc, const char * argv[])
{
  
  
  vector <particle *> parts;
  parts.push_back(new particle(3,2,1));
  parts.push_back(new particle(1,2,3));
  parts.pop_back();
  
  vector <particle *> copy;
  copy.push_back(parts.back());
  
  int e = 10;
  vector<int *> s;
  
  s.push_back(&e);
  
  // insert code here...
  std::cout << "Hello, World!\n";
    return 0;
}

