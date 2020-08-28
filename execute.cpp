//
//  execute.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/1.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include "execute.hpp"

void execute(const int Algo,const int runs,const int generations,const string filename,const int population,const double alpha,const double beta,const double rho){
    ofstream fout,file;
    fout.open("RESULT.txt");
    file.open("data.txt");
    vector<double> avg(generations/block);
    if (filename==""){
        for (int i=0;i<runs;i++){
            fout<<"----------------------------------------"<<endl;
            fout<<"run: "<<i+1<<endl;
            time_t start=0, end=0;
            if (Algo==1){
                AC *r = new AC(bits,generations,alpha,beta,rho);
                start = time(NULL);
                r->run();
                for (int j=0;j<=generations/block;j++){
                    avg[j] += r->get_record_value(j*block);
                }
                fout<<"Best: "<<r->get_record_value(generations-1)<<endl;
                end = time(NULL);
            }
            double diff = difftime(end, start);
            fout<<"Run time: "<<diff<<"s"<<endl;
        }
        fout<<"----------------------------------------"<<endl;
        for (int i=0;i<avg.size();i++){
            avg[i] /= runs;
            fout<<"Iter "<<i*block<<" : "<<avg[i]<<endl;
            file<<i*block<<" "<<avg[i]<<endl;
        }
    }
    else{
        cout<<"random number file"<<endl;
        //left blank
        //complete when needed
    }
}

