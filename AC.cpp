//
//  AC.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/25.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include "AC.hpp"

AC::AC(){
    iter = 0;
    pop = 20;
    Alpha = 1;
    Beta = 2;
    Rho = 0.5;
    best = 10000.0;
}

AC::AC(int iterations,int population,double alpha,double beta,double rho){
    iter = iterations;
    pop = population;
    Alpha = alpha;
    Beta = beta;
    Rho = rho;
    best = 10000.0;
}


void AC::TSPprob(){
    ifstream file;
    file.open("TSP51.txt");
    vector<vector<double> > data;
    while(!file.eof()){
        vector<double> t(3);
        file>>t[0]>>t[1]>>t[2];
        data.push_back(t);
    }
    
    Data = data;
    ncitys = data.size();
    Initialization(ncitys);
    //
    vector<double> test(52);
    double a[52] = {1,22,8,26,31,28,3,36,35,20,2,29,21,16,50,34,30,9,49,10,39,33,45,15,44,42,40,19,41,13,25,14,24,43,7,23,48,6,27,51,46,12,47,18,4,17,37,5,38,11,32,1};
    for (int i=0;i<52;i++){
        test[i] = a[i]-1;
    }
    cout<<"preference answer: "<<total_distance(test)<<endl;
    cout<<"route: ";
    for (int i=0;i<52;i++){
        cout<<a[i]<<", ";
    }
    cout<<endl;
    //

    int it = 0;
    while (it<iter){
        vector<ANT> ant;
        for (int i=0;i<pop;i++){
            ANT temp(ncitys, Distance, pheromone, Alpha, Beta);
            ant.push_back(temp);
        }
        vector<vector<double> > v = construct_sol(ant);
        if (it<500&&it!=iter-1){
            for (int i=0;i<v.size();i++){
                double f = v[i].back();
                vector<double> v1(v[i].begin(),v[i].begin()+v[i].size()-1);
                auto [x,y] = two_opt(f,v1);
                v[i].clear();
                v[i] = y;
                v[i].push_back(x);
            }
        }
        
        update_pher(v);
        for (int i=0;i<v.size();i++){
            if (v[i].back()<best){
                best = v[i].back();
                best_route = v[i];
                best_route.pop_back();
                //correct bias
                //for (int j=0;j<best_route.size();j++)
                //   best_route[j]++;
            }
        }
        if (it==iter-1){
            auto [b,b_route] = two_opt(best,best_route);
            best = b;
            best_route = b_route;
        }
        
        it++;
    }
    //correct bias
    for (int j=0;j<best_route.size();j++)
        best_route[j]++;
    file.close();
}

tuple<double,vector<double>> two_opt(double b,vector<double> b_route,int count_max){
    vector<double> v = b_route;

    int count=0;
    while(count<count_max){
        vector<double> v = b_route;
        int p1 = rand()%(b_route.size()-2)+1;
        int p2;
        do{p2 = rand()%(b_route.size()-2)+1;}while(p2<=p1+2 && p2>=p1-2);
        //int p1 = rand()%(b_route.size()-2-6)+1;
        //int p2 = p1+6;
                
        reverse(v.begin()+p1,v.begin()+p2+1);

        double newdist = total_distance(v);
        count++;
        if (newdist<b){
            b_route = v;
            b = newdist;
            count=0;
        }
    }
    return make_tuple(b,b_route);
}

double total_distance(vector<double> route){
    double sol = 0.0;
    for (int i=0;i<route.size()-1;i++){
        sol+=Distance[route[i]][route[i+1]];
    }
    return sol;
}



void AC::Initialization(int Ncitys){
    Distance = distance_mat(Ncitys);

    //++++++++++++++++++++++++
    
    //1. nearest neighbor
    pheromone = greedy_algo(Ncitys);
    
    //2. set initial value
    //pheromone = const_init(Ncitys);
}

vector<vector<double> > AC::distance_mat(int Ncitys){
    vector<vector<double> > dis;
    for (int i=0;i<Ncitys;i++){
        vector<double> temp;
        for (int j=0;j<Ncitys;j++){
            vector<double> p1(2),p2(2);
            for (int k=1;k<=2;k++){
                p1[k-1] = Data[i][k];
                p2[k-1] = Data[j][k];
            }
            temp.push_back(cal_distance(p1,p2));
        }
        dis.push_back(temp);
    }
    return dis;
}

double AC::cal_distance(vector<double> p1,vector<double> p2){
    return sqrt( pow((p1[0]-p2[0]),2)+pow((p1[1]-p2[1]),2) );
}

vector<vector<double> > AC::const_init(int Ncitys){
    vector<vector<double> > pher;
    for (int i=0;i<Ncitys;i++){
        vector<double> temp;
        for (int j=0;j<Ncitys;j++){
            if (i==j)
                temp.push_back(0);
            else
                temp.push_back(0.1);
        }
        pher.push_back(temp);
    }
    return pher;
}

vector<vector<double> > AC::greedy_algo(int Ncitys){
    double total = 0.0;
    vector<double> t;
    int start = rand()%Ncitys;
    int last;
    vector<int> Ta(Ncitys);
    vector<int> r(Ncitys+1);
    r[0] = start;
    for (int i=1;i<Ncitys;i++){
        double min = 100.0;
        int NxtCTY;
        for (int j=0;j<Ncitys;j++){
            if (Ta[j]==0){
                if (Distance[r[i-1]][j]<min){
                    min = Distance[r[i-1]][j];
                    NxtCTY = j;
                }
            }
            
        }
        r[i] = NxtCTY;
        Ta[NxtCTY] = 1;
        total+=min;
        if (i==Ncitys-1)
            last = NxtCTY;
    }
    total+=Distance[last][start];
    
    vector<vector<double> > pher;
    for (int i=0;i<Ncitys;i++){
        vector<double> temp;
        for (int j=0;j<Ncitys;j++){
            if (i==j)
                temp.push_back(0);
            else
                temp.push_back((double)pop/total);
        }
        pher.push_back(temp);
    }
    return pher;
}

void AC::update_pher(const vector<vector<double> > v){
    vector<vector<int> > count(pheromone.size());
    for (int i=0;i<pheromone.size();i++){
        vector<int> temp(pheromone.size(),0);
        count[i] = temp;
    }
    for (int i=0;i<v.size();i++){
        for (int j=0;j<v[0].size()-2;j++){
            if (count[v[i][j]][v[i][j+1]]==0){
                pheromone[v[i][j]][v[i][j+1]] = Rho*pheromone[v[i][j]][v[i][j+1]];
                //for sychronization
                pheromone[v[i][j+1]][v[i][j]] = pheromone[v[i][j]][v[i][j+1]];
                //
                count[v[i][j]][v[i][j+1]] = 1;
                //for sychronization
                count[v[i][j+1]][v[i][j]] = 1;
                //
            }
        }
    }
    for (int i=0;i<v.size();i++){
        for (int j=0;j<v[0].size()-2;j++){
            pheromone[v[i][j]][v[i][j+1]]+= (1.0/v[i][v[0].size()-1]);
            //for sychronization
            pheromone[v[i][j+1]][v[i][j]] += (1.0/v[i][v[0].size()-1]);
            //
        }
    }
}

vector<vector<double> > AC::construct_sol(vector<ANT> &ant){
    vector<vector<double> > v;
    for (int i=0;i<pop;i++){
        vector<double> temp(ncitys);
        ant[i].run();
        temp = ant[i].get_route();
        temp.push_back(total_distance(temp));
        v.push_back(temp);
    }
    return v;
}
                      
//double AC::total_distance(vector<double> route){
//    double sol = 0.0;
//    for (int i=0;i<route.size()-1;i++){
//        sol+=Distance[route[i]][route[i+1]];
//    }
//    return sol;
//}

void AC::print_bestroute(){
    for (int i=0;i<best_route.size();i++){
        cout<<best_route[i]<<", ";
    }
}

void AC::to_file(){
    static int f;
    ofstream fout;
    string file = "ans"+to_string(f)+".txt";
    fout.open(file);
    for (int i=0;i<best_route.size();i++){
        for (int j=0;j<3;j++){
            fout<<Data[best_route[i]-1][j]<<" ";
        }
        fout<<endl;
    }
    f++;
}
                      
//-----------------------------------------------//

ANT::ANT(){
}

ANT::ANT(int ncitys,vector<vector<double> > Distance,vector<vector<double> > pheromone,double Alpha,double Beta){
    Ncitys = ncitys;
    tabu = new int [Ncitys];
    
    memset(tabu, 0, Ncitys);
    for (int i=0;i<Ncitys;i++){
        tabu[i] = 0;
    }
    Dis = Distance;
    pher = pheromone;
    A = Alpha;
    B = Beta;
}

void ANT::run(){
    //int start = rand()%Ncitys;
    int start = 0; //starts from city 1
    route.push_back(start);
    tabu[start] = 1;
    for (int i=1;i<Ncitys;i++){
        int next = next_city();
        route.push_back(next);
        tabu[next] = 1;
    }
    route.push_back(start);
}

double ANT::next_city(){
    long double denominator = 0.0;
    for (int i=0;i<Ncitys;i++){
        if (tabu[i]==0){
            denominator+=(long  double)pow(pher[route.back()][i],A)*pow(1.0/Dis[route.back()][i],B);
        }
    }
    double base = 0.0;
    double r = (double)rand()/(RAND_MAX);
    double city = -1;
    for (int i=0;i<Ncitys;i++){
        if (tabu[i]==0){
            double prob = (pow(pher[route.back()][i],A)*pow(1.0/Dis[route.back()][i],B)) / denominator;
            if ( (r>=base) && (r<=base+prob) ){
                city = i;
                break;
            }
            base+=prob;
        }
    }
    return city;
}
