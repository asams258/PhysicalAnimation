//
//  Force.h
//  SPH Fluids
//
//  Created by Arthur Sams on 2/27/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#ifndef __SPH_Fluids__Force__
#define __SPH_Fluids__Force__

#include <iostream>
#include "Particle.h"
#include <vector>
#include <math.h>

using Constants::h_sq;
using Constants::h;
namespace forces{
  // 315/(64*pi)
  
  const double poly6Weight = 1.5666814710608448/pow(h,9);
  const double spikyWeight = 4.7746482927568605/pow(h,6);
  const double viscWeight = 2.3873241463784303/pow(h,3);
  void accumlateExtForces(particle &i);
  void boundayConstraint(particle &i);
  void computeDensity(particle &i);
  void computeLambda(particle &i);
  void computeDeltaP(particle &i);
}

#endif /* defined(__SPH_Fluids__Force__) */
