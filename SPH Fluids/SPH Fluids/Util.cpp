//
//  Util.cpp
//  SPH Fluids
//
//  Created by Arthur Sams on 2/27/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Util.h"
#include "Constants.h"

namespace util{
  void writeParticle(const vector<particle> & particles, const int & frame){
    std::ofstream myfile;
    if (frame >0)
      myfile.open (Constants::path,std::fstream::app);
    else
      myfile.open(Constants::path);
    
    myfile << "Time = " << (double)frame*Constants::d_t<< std::endl;
    for (vector<particle>::const_iterator it = particles.begin(); it != particles.end(); ++it){
      myfile << std::setprecision(10) << std::fixed << it->p[0] << " " << it->p[1] <<" " <<it->p[2] << std::endl;
    }//end for
    
    myfile.close();
  }
  
}