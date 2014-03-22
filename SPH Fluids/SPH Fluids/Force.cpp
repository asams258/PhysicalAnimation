//
//  Force.cpp
//  SPH Fluids
//
//  Created by Arthur Sams on 2/27/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//


#include "Force.h"
#include "Constants.h"
#include <stdio.h>

//Should probably make this a class, since i have private stuffs
namespace forces{
  //keeping r squared to save Flops
  //Make sure R is all positive values?
  void poly6Kernel(double r, double & w){
    if (r<=h_sq && r>=0){
      w = poly6Weight*pow(h_sq-r,3);
    }
    else{
      w = 0;
    }
  }
  
  //how would i not sq root to save efficency
  void spikyKernel(double r, double & w){
    r = sqrt(r);
    if (r<=h){
      w = spikyWeight*pow(h-r,3);
    }
    else{
      w = 0;
    }
  }
  
  //grad i of r = (r_i-r_j)
  //be careful of r = 0! that means we are at max, and grad = 0
  void gradSpikyKernel (double const r[3], double g[3]){
    double r_d = sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
    if (r_d<=h && r_d>0){
      double w = 3*spikyWeight*pow(h-r_d,2)/r_d;
      g[0] = w * r[0];
      g[1] = w * r[1];
      g[2] = w * r[2];
    }
    else {
      g[0] = 0; g[1] = 0; g[2] = 0;
    }
  }
  
  //sets density in particle using poly6 kernel
  void computeDensity(particle &part){
    double r;
    double w = 0.0;
    part.rho = 0;
    for (std::vector<particle *>::const_iterator it = part.neighbors.begin(); it != part.neighbors.end(); ++it){
      //Reset r each time before summing
      r = 0;
      for (int i=0;i<3;++i){
        r += (part.p[i]-((*it)->p[i]))*(part.p[i]-((*it)->p[i]));
      }
      //passing r which is ||pi - pj||^2)
      poly6Kernel(r,w);
      part.rho += w;
    }//iterating all particles
    if (part.rho<0)
      std::cout <<"Density less than 0 on : " << part.ID << std::endl;
  }
  
  void computeLambda(particle &i){
    double c = (i.rho / Constants::rho_0) -1;
    //For case where k=i
    double k_i_sum [3] = {0,0,0};
    double k_j_sum = 0;
    double r [3];
    double g [3];

    //for every k
    for (std::vector<particle *>::const_iterator it = i.neighbors.begin() ; it != i.neighbors.end(); ++it){
      //reset g and set r as the differnce in positions
      for (int j =0; j <3; ++j){
        r[j] = i.p[j]-((*it)->p[j]);
        g[j] = 0;
      }
      gradSpikyKernel(r,g);
      //Accumlate for the k=i case
      for (int m =0; m<3; ++m){
        k_i_sum[m] += g[m];
      }
      //for each i j pair there will be one k=j case
      k_j_sum += ((pow(g[0],2) + pow(g[1],2) + pow(g[2],2))/pow(Constants::rho_0,2));
    }
    //Summing up the k=i
    double k_i;
    k_i = (pow(k_i_sum[0],2)+pow(k_i_sum[1],2)+pow(k_i_sum[2],2))/pow(Constants::rho_0,2);
    i.lambda = -c/(k_i+k_j_sum+Constants::epsilon);
  }
  
  void computeDeltaP(particle &i){
    double r [3];
    double g [3];
    double w;
    //For Tensile Correction
    double s_corr;
    double s_pw;
    
    for (std::vector<particle *>::const_iterator it = i.neighbors.begin(); it != i.neighbors.end(); ++it){
      for (int j =0; j<3 ;++j){
        r[j] = i.p[j]-((*it)->p[j]);
        g[j] = 0;
      }
      gradSpikyKernel(r, g);
      
      //S_Corr stuff
      poly6Kernel(r[0]*r[0]+r[1]*r[1]+r[2]*r[2], s_corr);
      //use .1h.....3h but squared as input to my poly6 must be squared
      poly6Kernel(Constants::h_sq*pow(Constants::d_q,2), s_pw);
      s_corr = -Constants::k*pow((s_corr/s_pw),Constants::n);
      
      //TODO: add s_corr here
      w = i.lambda + ((*it)->lambda);// + s_corr;
      //sum the corrections
      for (int j=0; j<3; ++j){
        i.d_p[j] += g[j]*w;
      }
    }//end all particle loop
    //multiply by 1/density_0
    for (int j=0; j<3; ++j){
      i.d_p[j] *= 1/Constants::rho_0;
    }
  }
  
  //Only Gravity Considered So far in Y direction (verticle).
  void accumlateExtForces(particle &i){
    i.f[1] += Constants::GRAVITY;
  }
  
  //Check This: may need to consider d_p in calculation
  void boundayConstraint(particle &i){
    for (int j = 0; j<3;++j){
      //if outside, clamp to boundary
      if (i.p[j] + Constants::bubbleRad +i.d_p[j]> Constants::grid_dim[j]){
        // want to head in downwards position to boundary
        //want P-X where X = P+R-B
        i.d_p_col[j] = Constants::grid_dim[j]-i.p[j]-Constants::bubbleRad-i.d_p[j];
      }
      //want to bounce that upwards to boundary
      else if (i.p[j] + i.d_p[j] < 0 + Constants::bubbleRad){
        i.d_p_col[j] = -i.p[j] - i.d_p[j] + Constants::bubbleRad;
      }
    }
  }
  
}//end namespace


