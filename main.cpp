//
//  main.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/1.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include "execute.hpp"

using namespace std;

void prompt(const int Algo,const int runs,const int generations,const int bits);

int main(int argc, const char * argv[]) {
    const string algo = argv[1];
    const int runs = stoi(argv[2]);
    const int generations = stoi(argv[3]);
    string filename = argv[4];
    cout<<"filename: "<<filename<<endl;
    const int population = stoi(argv[5]);
    const double alpha = stod(argv[6]);
    const double beta = stod(argv[7]);
    const double rho = stod(argv[8]);
    if (algo=="ac"){
        prompt(1, runs, generations, bits);
        execute(1, runs, generations, bits, filename,temperature, alpha);
    }
    else{
        cerr<<"No such algorithm!"<<endl;
    }
    return 0;
}

void prompt(const int Algo,const int runs,const int generations,const int bits){
    cout<<"----------------------------------------"<<endl;
    switch (Algo) {
        case 1:
            cout<<"Ant Colony Optimization:"<<endl;
            break;
        default:
            break;
    }
    cout<<"runs: "<<runs<<endl;
    cout<<"generations: "<<generations<<endl;
    cout<<"----------------------------------------"<<endl;
}
