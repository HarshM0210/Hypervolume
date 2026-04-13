//  WFG.cpp
//  Created by Harshvijay Mishra on 11/04/26.

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std::chrono;
using namespace std;

//Global Variable
int m; //Dimensions

//To Count The Total Number hypervolume() Is Called
long long Count;

//To Count The Total Number Of Points With Which hypervolume() Is Called
long long Total=0;

long long hypervolume(vector<vector<int>>&);


//To Generate A Non-Dominated Population Of n Points And m Dimensions
void generatePopulation(int n, vector<vector<int>>& population_initial)
{
    static std::mt19937 gen(std::random_device{}());

    population_initial.clear();
    population_initial.reserve(n);

    vector<int> p(m);

    for(int i = n, j = 1; i >= 1; i--, j++)
    {
        p[0] = i;
        p[1] = j;

        // Random Values Between Min(i,j) And Max(i,j)
        int low = min(i, j);
        int high = max(i, j);
        std::uniform_int_distribution<> dist(low, high);

        for(int k = 2; k < m; k++)
            p[k] = dist(gen);

        // Shuffle The Vector
        if(m > 2)
            std::shuffle(p.begin(), p.end(), gen);

        population_initial.push_back(p);
    }
}


//To Shuffle The Population Randomly
void randomShuffle(vector<vector<int>>& population)
{
    static std::mt19937 g(std::random_device{}());
    std::shuffle(population.begin(), population.end(), g);
}


//To Sort The Population Based On Variance
void varianceShuffle(vector<vector<int>>& population)
{
    //To Store Standard Deviations Of Each Objective
    vector<long double>standard_deviation;
    standard_deviation.reserve(m);
    int size=population.size();
    
    //Calculation Of Standard Deviation Across Each Objective
    for(int i=0;i<m;i++)
    {
        //Calculating Mean
        long double mean=0;
        for(int j=0;j<size;j++)
            mean+=population[j][i];
        mean/=size;
        
        //Calculating Variance
        long double variance=0;
        for(int j=0;j<size;j++)
            variance+=(population[j][i]-mean)*(population[j][i]-mean);
        variance/=size;
        
        //Calculating Standard Deviation
        long double sd=sqrt(variance);
        standard_deviation.push_back(sd);
    }
    
    //Dimension With Maximum Standard Deviation
    int objective=max_element(standard_deviation.begin(), standard_deviation.end()) - standard_deviation.begin();
    
    //Sorting Based On The Obtained Dimension With Maximum Standard Deviation
    sort(population.begin(), population.end(),
             [&](const vector<int>& a, const vector<int>& b)
             {
                 return a[objective] < b[objective];
             });
}


//To Obtain The Set Of Non-Dominated Points From The Population
vector<vector<int>> nonDominatedPopulation(const vector<vector<int>>& population)
{
    vector<vector<int>> unique_pop = population;
    sort(unique_pop.begin(), unique_pop.end());
    unique_pop.erase(unique(unique_pop.begin(), unique_pop.end()), unique_pop.end());

    int size = unique_pop.size();
    vector<bool> dominated(size, false);

    for (int i = 0; i < size; i++)
    {
        if (dominated[i]) continue;

        for (int j = i + 1; j < size; j++)
        {
            if (dominated[j]) continue;

            bool iBetter = false;
            bool jBetter = false;

            for (int k = 0; k < m; k++)
            {
                if (unique_pop[i][k] > unique_pop[j][k]) iBetter = true;
                else if (unique_pop[i][k] < unique_pop[j][k]) jBetter = true;

                if (iBetter && jBetter)
                    break;
            }

            if (!jBetter && iBetter)
                dominated[j] = true;
            else if (!iBetter && jBetter)
            {
                dominated[i] = true;
                break;
            }
        }
    }

    vector<vector<int>> result;
    result.reserve(size);

    for (int i = 0; i < size; i++)
        if (!dominated[i])
            result.push_back(unique_pop[i]);

    return result;
}


//To Calculate The Exclusive-Hypervolume Of A Point With Respect To A Population
int exclusive_hypervolume(const vector<int>& point,const vector<vector<int>>& population)
{
    int size=population.size();
    
    //To Store The Point Whose Exclusive Hypervolume Needs To Calculated With Respect To The Population
    vector<vector<int>> pivot;
    pivot.push_back(point);
    
    //To Store The Projected Population
    vector<vector<int>> p;
    p.reserve(size);
    
    if(size==0)
        return hypervolume(pivot);
    
    //Calculating The Projected Population
    for(int i=0;i<size;i++)
    {
        vector<int> projected_point(m);
        
        for(int j = 0; j < m; j++)
            projected_point[j] = min(population[i][j], point[j]);
        
        p.push_back(std::move(projected_point));
    }
    
    //Filter Out The Non-Dominated Points From The Projected Population Calculated Above
    vector<vector<int>>non_dominated_p=nonDominatedPopulation(p);
    
    return hypervolume(pivot)-hypervolume(non_dominated_p);
}


//To Calculate The Hypervolume Of A Population
long long hypervolume(vector<vector<int>>& population)
{
    int size=population.size();
    Count++;
    Total+=size;
    
    //Calculating Hypervolume Of A Single Point With Respect To The Origin
    if(size==1)
    {
        long long product=1;
        for(int i=0;i<m;i++)
            product=product*population[0][i];

        return product;
    }
    
    //Calculating Hypervolume Of The Population Using Exclusive Hypervolume
    long long h=0;
    vector<vector<int>> p;
    p.reserve(size);
    
    for(int i=0;i<size;i++)
    {
        p.clear();
        for(int j=i+1;j<size;j++)
            p.push_back(population[j]);
            
        h=h+exclusive_hypervolume(population[i],p);
    }
    
    return h;
}


//Main()
int main()
{
    int n;
    
    cout<<"ENTER THE NUMBER OF POINTS = ";
    cin>>n;
    cout<<"ENTER THE DIMENSIONS OF POINTS = ";
    cin>>m;
    
    if(n>0)
    {
        vector<vector<int>> population_initial;
        
        //Randomly Generated Population
        generatePopulation(n,population_initial);
        
        //Non-Dominated Population
        vector<vector<int>>population= nonDominatedPopulation(population_initial);
        
        /*
        //Pre-defined Initial Population With/Without Dominated Points
        population_initial = {
            {5,6,7},
            {11,4,4},
            {12,2,4},
            {10,5,2},
            {10,3,5},
            {3,3,10},
            {2,2,11},
            {2,4,8},
            {4,2,8},
            {3,8,2},
            {2,9,2},
            {4,7,1},
            {1,7,3}
        };
        vector<vector<int>>population= nonDominatedPopulation(population_initial);
        */
        
        /*
        //User-defined Initial Population With/Without Dominated Points
        population_initial(n,vector<int>(m));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                cout<<"ENTER THE "<<j<<" CO-ORDINATE OF "<<i<<"  POINT = ";
                cin>>population_initial[i][j];
            }
        }
        vector<vector<int>>population= nonDominatedPopulation(population_initial);
        */
        
        /*
        //Print Non-Dominated Initial Population
        cout<<"Initial Population="<<endl;
        for(auto p: population)
        {
            for(int i=0;i<m;i++)
                cout<<p[i]<<" ";
            
            cout<<endl;
        }
        */

        cout<<endl;
        
        //Originial Population
        Count=0;
        Total=0;
        //Calculating Hypervolume For The Non Dominated Popultaion
        auto start_original = high_resolution_clock::now();
        long long Hypervolume_original=hypervolume(population);
        auto end_original = high_resolution_clock::now();
        
        //Calculating The Time Taken During Execution
        auto duration_original = duration_cast<milliseconds>(end_original - start_original);

        cout<<"HYPERVOLUME USING ORIGINAL POPULATION = "<<Hypervolume_original<<endl;
        cout << "TIME TAKEN USING ORIGINAL POPULATION = " << duration_original.count() << " milliseconds" << endl;
        cout<<"TOTAL CALLS TO hypervolume() = "<<Count<<endl;
        cout<<"TOTAL POINTS USED IN CALLS TO hypervolume() = "<<Total<<endl;
        
        cout<<endl;
        
        
        //Random Shuffling
        randomShuffle(population);
        Count=0;
        Total=0;
        //Calculating Hypervolume For The Non Dominated Popultaion
        auto start_random = high_resolution_clock::now();
        long long Hypervolume_random=hypervolume(population);
        auto end_random = high_resolution_clock::now();
        
        //Calculating The Time Taken During Execution
        auto duration_random = duration_cast<milliseconds>(end_random - start_random);

        cout<<"HYPERVOLUME USING RANDOMLY SHUFFLED POPULATION = "<<Hypervolume_random<<endl;
        cout << "TIME TAKEN USING RANDOMLY SHUFFLED POPULATION = " << duration_random.count() << " milliseconds" << endl;
        cout<<"TOTAL CALLS TO hypervolume() = "<<Count<<endl;
        cout<<"TOTAL POINTS USED IN CALLS TO hypervolume() = "<<Total<<endl;
        
        cout<<endl;
        
        //Standard Deviation Based Shuffling
        varianceShuffle(population);
        Count=0;
        Total=0;
        //Calculating Hypervolume For The Non Dominated Popultaion
        auto start_variance = high_resolution_clock::now();
        long long Hypervolume_variance=hypervolume(population);
        auto end_variance = high_resolution_clock::now();
        
        //Calculating The Time Taken During Execution
        auto duration_variance = duration_cast<milliseconds>(end_variance - start_variance);

        cout<<"HYPERVOLUME USING STANDARD DEVIATION SHUFFLED POPULATION = "<<Hypervolume_variance<<endl;
        cout << "TIME TAKEN USING STANDARD DEVIATION SHUFFLED POPULATION = " << duration_variance.count() << " milliseconds" << endl;
        cout<<"TOTAL CALLS TO hypervolume() = "<<Count<<endl;
        cout<<"TOTAL POINTS USED IN CALLS TO hypervolume() = "<<Total<<endl;
        
        cout<<endl;
        
    }
    else
        cout<<"NO POINTS TO CALCULATE HYPERVOLUME!"<<endl;

    return 0;
}

