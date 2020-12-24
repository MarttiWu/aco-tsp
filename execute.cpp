//
//  execute.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/1.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include "execute.hpp"

void execute(const int Algo,const int runs,const int iterations,const string filename,const int population,const double alpha,const double beta, const double rho){
    srand((unsigned)time(NULL));

    float avg=0;
    if (filename==""){
        for (int i=0;i<runs;i++){
            cout<<"----------------------------------------"<<endl;
            cout<<"run: "<<i<<endl;
            time_t start=0, end=0;
            if (Algo==1){
                AC *r = new AC(iterations, population, alpha, beta, rho);
                start = time(NULL);
                r->TSPprob();
                avg+=r->get_best();
                cout<<"best: "<<r->get_best()<<endl;
                cout<<"best route: ";
                r->print_bestroute();
                cout<<"to file"<<endl;
                r->to_file();
                cout<<endl;
                end = time(NULL);
            }
            double diff = difftime(end, start);
            cout<<"Run time: "<<diff<<"s"<<endl;
        }
        cout<<"----------------------------------------"<<endl;
        avg/=runs;
        cout<<"average: "<<avg<<endl;
    }
    else{
        cout<<"random number file"<<endl;
        //left blank
        //complete when needed
    }
}
