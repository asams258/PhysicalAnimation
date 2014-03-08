//
//  Constants.h
//  SPH Fluids
//
//  Created by Arthur Sams on 2/26/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#ifndef SPH_Fluids_Constants_h
#define SPH_Fluids_Constants_h
#include <string>
namespace Constants {
  //static const double gridSize = 100;
  static const double h = .1;
  static const double h_sq = h*h;
  static const double rho_0 = 300;
  static const double grid_dim [3] = {10,10,10};
  static const std::string path = "/Users/arthur/Desktop/SPHRender/locs.txt";
  static const double GRAVITY = -9.80665;
  static const double d_t = .001;
  static const int FRAMES = 100;
  static const double bubbleRad = .015;
  static const int SolverIterations = 1;
  static const double epsilon = .00001;
}


#endif
