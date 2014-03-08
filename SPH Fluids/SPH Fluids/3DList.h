//
//  3DList.h
//  SPH Fluids
//
//  Created by Arthur Sams on 3/7/14.
//  Copyright (c) 2014 Arthur Sams. All rights reserved.
//

#ifndef __SPH_Fluids___DList__
#define __SPH_Fluids___DList__

#include <iostream>

class DList {
  int width, height;
public:
  void set_values (int,int);
  int area() {return width*height;}
};

#endif /* defined(__SPH_Fluids___DList__) */
