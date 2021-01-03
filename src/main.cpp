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

void prompt(const int Algo,const int runs,const int iterations, const string filename);

int main(int argc, const char * argv[]) {
    if (argc<9){
        cerr<<"usage: "<<"./main [algo] [runs] [gen] [filename] [population] [alpha] [beta] [rho] [2opt]"<<endl;
    }
    const string algo = argv[1];
    const int runs = stoi(argv[2]);
    const int iterations = stoi(argv[3]);
    
    string filename= argv[4];
    
    const int population = stoi(argv[5]);
    const double alpha = stod(argv[6]);
    const double beta = stod(argv[7]);
    const double rho = stoi(argv[8]);
    const int two_opt = stoi(argv[9]);
    
    if (algo=="ac"){
        prompt(1, runs, iterations, filename);
        execute(1, runs, iterations, filename, population, alpha, beta, rho, two_opt);
    }
    else{
        cerr<<"No such algorithm!"<<endl;
    }
    return 0;
}


void prompt(const int Algo,const int runs,const int iterations, const string filename){
    cout<<"Dataset: "<<filename<<endl;
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
