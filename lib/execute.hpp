//
//  execute.hpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/8.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#ifndef execute_hpp
#define execute_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include "AC.hpp"

using namespace std;

void execute(const int Algo,const int runs,const int iterations,const string filename,const int population,const double alpha,const double beta, const double rho, const int two_opt);

#endif /* execute_hpp */
