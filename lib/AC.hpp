//
//  AC.hpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/25.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#ifndef AC_hpp
#define AC_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>
#include <tuple>
using namespace std;

static vector<vector<double> > Distance;

class ANT;

class AC{
public:
    AC();
    AC(int iterations,int population,double alpha,double beta,double rho, int i2opt, string fname);
    void TSPprob();
    void Initialization(int Ncitys);
    vector<vector<double> > distance_mat(int Ncitys);
    vector<vector<double> > const_init(int Ncitys);
    vector<vector<double> > greedy_algo(int Ncitys);
    double cal_distance(vector<double> p1,vector<double> p2);
    void update_pher(const vector<vector<double> > v);
    vector<vector<double> > construct_sol(vector<ANT> &ant);
    //double total_distance(vector<double> route);
    double get_best(){return best;}
    //friend class ANT;
    //friend double next_city();
    void print_bestroute();
    void to_file();
    
private:
    //vector<vector<double> > Distance;
    vector<vector<double> > pheromone;
    double Alpha;
    double Beta;
    int iter;
    int pop;
    double Rho;
    double best;
    int interval_2opt;
    string filename;
    vector<double> best_route;
    vector<vector<double> > Data;
    int ncitys;
};


class ANT{
public:
    ANT();
    ANT(int ncitys,vector<vector<double> > Distance,vector<vector<double> > pheromone,double Alpha,double Beta);
    void run();
    double next_city();
    vector<double> get_route(){return route;}
    friend class AC;
    int get_Ncitys(){return Ncitys;}
private:
    int Ncitys;
    int *tabu;
    vector<double> route;
    
    vector<vector<double> > Dis;
    vector<vector<double> > pher;
    double A;
    double B;
};
double total_distance(vector<double> route);
tuple<double,vector<double>> two_opt(double b,vector<double> b_route,int count_max=10000);
#endif /* AC_hpp */
