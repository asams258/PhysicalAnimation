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
  static const double rho_0 = 8000.;
  static const double grid_dim [3] = {1,1,1};
  static const std::string path = "/Users/arthur/Desktop/SPHRender/locs.txt";
  static const std::string debugpath = "/Users/arthur/Desktop/SPHRender/debug.txt";
  static const double GRAVITY = -9.80665;
  //Time step responsible for going nuts
  static const double d_t = .00000001;
  static const int FRAMES = 100;
  static const double bubbleRad = .015;
  static const int SolverIterations = 3;
  static const double epsilon = .01;
  static const int Reps = 10;
  static const double d_q = 0.2;
  static const double n = 6;
  static const double k = .00001;
  
  
}

#endif
