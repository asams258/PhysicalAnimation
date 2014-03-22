//
//  Util.h
//  SPH Fluids
//
//  Created by Arthur Sams on 2/27/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#ifndef __SPH_Fluids__Util__
#define __SPH_Fluids__Util__
#include <vector>
#include "Particle.h"
namespace util {
  void writeParticle (const vector<particle *> &, const int & frame);
  void writeDebug (const vector<particle *> &, const int & frame, const int & rep);
}


#endif /* defined(__SPH_Fluids__Util__) */
