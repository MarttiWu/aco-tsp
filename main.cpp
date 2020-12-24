//
//  main.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/19.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include "execute.hpp"

using namespace std;

void prompt(const int Algo,const int runs,const int iterations);

int main(int argc, const char * argv[]) {
    const string algo = argv[1];
    const int runs = stoi(argv[2]);
    const int iterations = stoi(argv[3]);
    //const int bits = stoi(argv[4]);
    
    string filename= argv[4];
    cout<<"filename: "<<filename<<endl;
    
    const int population = stoi(argv[5]);
    const double alpha = stoi(argv[6]);
    const double beta = stoi(argv[7]);
    const double rho = stoi(argv[8]);
    
    if (algo=="ac"){
        prompt(1, runs, iterations);
        execute(1, runs, iterations, filename, population, alpha, beta, rho);
    }
    else{
        cerr<<"No such algorithm!"<<endl;
    }
    return 0;
}


void prompt(const int Algo,const int runs,const int iterations){
    cout<<"Problem: TSP51"<<endl;
    cout<<"----------------------------------------"<<endl;
    switch (Algo) {
        case 1:
            cout<<"Ant Colony Optimization:"<<endl;
            break;
        default:
            break;
    }
    cout<<"runs: "<<runs<<endl;
    cout<<"iterations: "<<iterations<<endl;
    cout<<"----------------------------------------"<<endl;
}
