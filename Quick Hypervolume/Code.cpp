//  Quick Hypervolume With Projection.cpp
//  Hypervolume
//  Created by Harsh Mishra on 26/10/25.

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

//Global Variable
int m; //Dimensions


//To Convert The Hyperocatant Number From Decimal To Binary
vector<int> toBinary(int num)
{
    if (num < 0 || num >= (1 << m))
    {
        cout << "ERROR: INVALID HYPEROCTANT NUMBER " << num << endl;
        return vector<int>(m, 0);
    }
    vector<int> binary(m);
    for (int i = 0; i < m; i++)
    {
        binary[m - 1 - i] = (num >> i) & 1;
    }

    return binary;
}

//To Convert The Hyperocatant Number From Binary To Decimal
int toDecimal(const vector<int>& binary)
{
    int num = 0;
    for (int i = 0; i < m; i++)
    {
        num = (num << 1) | binary[i];
    }
    return num;
}

//To Obtain The Hyperoctant To Which A Particular Point Belongs
vector<int> obtainHyperoctant(const vector<int>& point,const vector<int>& pivot)
{
    vector<int>hyperoctant(m);
    
    //Determine The Corresponding Hyperoctant
    for (int i=0; i<m; i++)
    {
        hyperoctant[i] = (point[i] > pivot[i]) ? 1 : 0;
    }
    
    return hyperoctant;
}


//To Obtain The Set Of Non-Dominated Points From The Population
vector<vector<int>> nonDominatedPopulation(const vector<vector<int>>& population)
{
    int n = population.size();
    vector<bool> dominated(n, false);

    for (int i = 0; i < n; i++)
    {
        if (dominated[i]) continue;

        for (int j = i + 1; j < n; j++)
        {
            if (dominated[j]) continue;

            bool iBetter = false;
            bool jBetter = false;

            for (int k = 0; k < m; k++)
            {
                if (population[i][k] > population[j][k]) iBetter = true;
                else if (population[i][k] < population[j][k]) jBetter = true;

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
    result.reserve(n);

    for (int i = 0; i < n; i++)
        if (!dominated[i])
            result.push_back(population[i]);

    return result;
}

//To Calculate The Hypervolume Of A Point
int hypervolume(const vector<int>& reference,const vector<int>& point)
{
    int product=1;
    for(int i=0;i<m;i++)
    {
        product=product*(point[i]-reference[i]);
    }
    return product;
}

//To Determine The Pivot From The Population
vector<int> calculatePivot(const vector<vector<int>>& population, const vector<int>& reference)
{
    int greatest=0;
    int index=0;
    int n=population.size();
    
    for(int i=0;i<n;i++)
    {
        int hyp=hypervolume(reference, population[i]);
        if(hyp>greatest)
        {
            greatest=hyp; //The Point With Largest Hypervolume Is The Pivot
            index=i;
        }
    }
    
    return population[index];
}

//To Add A Point To The List Of Points Present In The Particular Hyperoctant
void addPoint(vector<vector<vector<int>>>& population_hyperoctant,int hyperoctant_number,const vector<int>& point)
{
    population_hyperoctant[hyperoctant_number].push_back(point);
}

//To Project A Point To A Particular Hyperoctant
vector<int> pointProjection(const vector<int>& current_hyperoctant,const vector<int>& hypoct,const vector<int>& point,const vector<int>& pivot)
{
    vector<int>projected_point(m);
    for (int i=0; i<m; i++)
    {
        for (int i = 0; i < m; i++)
            projected_point[i] = (hypoct[i] == current_hyperoctant[i]) ? point[i] : pivot[i];
    }
    return projected_point;
}

//To Calculate The Reference Of A Hyperoctant
vector<int> calculateReference(const vector<int>& hyperoctant,const vector<int>& pivot,const vector<int>& reference)
{
    vector<int> temp_hyperoctant(m);
    for (int j = 0; j < m; j++)
    {
        temp_hyperoctant[j] = (hyperoctant[j] == 0) ? reference[j] : pivot[j];
    }
    return temp_hyperoctant;
}

//To Calculate The Quick Hypervolume Of The Population
int quickHypervolume(const vector<vector<int>>& population,const vector<int>& reference)
{
    int n=population.size();
    
    if(n==0)
    {
        return 0;
    }
    
    else if(n==1)
    {
        return hypervolume(reference, population[0]);
    }
    
    else
    {
        //Calculate Pivot For The Given Population
        vector<int>pivot= calculatePivot(population,reference);
        
        //Total Number Of Hyperoctants Corresponding To A Pivot
        int total_hyperoctants = 1 << m;
        
        //3-D Vector To Hold The List Of All The Points Belonging To A Particular Hyperoctant
        vector<vector<vector<int>>> population_hyperoctant(total_hyperoctants);
        
        //2-D Vector To Hold The Reference Points For Each Of The Hypeoctants
        vector<vector<int>>reference_hyperoctant(total_hyperoctants);
        
        //Iterate Through All The Points Of The Given Population
        for (int i=0; i<n; i++)
        {
            if(population[i]!=pivot)
            {
                //Determine The Hyperoctant To Which A Point Belongs
                vector<int>current_hyperoctant=obtainHyperoctant(population[i], pivot);
                
                //Determine The Decimal Representation Of The Hyperoctant Found In The Previous Step
                int hyperoctant_number=toDecimal(current_hyperoctant);
                
                //Calculate The Reference Point For The Hyperoctant To Which The Point Belongs
                if (reference_hyperoctant[hyperoctant_number].empty())
                {
                    reference_hyperoctant[hyperoctant_number] = calculateReference(current_hyperoctant,pivot,reference);
                }
                
                //Add The Point To The List Of Points Present In That Hyperoctant
                addPoint(population_hyperoctant,hyperoctant_number,population[i]);
                
                //Count The Number Of 1s In The Binary Representation Of The Hyperoctant Number
                int count=0;
                for (int j=0; j<m; j++)
                {
                    if(current_hyperoctant[j]==1)
                        count++;
                }
                
                //Meaningfully Project The Point To All Other Required Hyperoctants
                if (count > 1) //Refrain From Projecting Points Of Adjacent Hyperoctants
                {
                    vector<int>I(count);
                    int index_I=0;
                    for (int j=0; j<m; j++)
                    {
                        if(current_hyperoctant[j]==1)
                            I[index_I++] = j;
                    }
                    int total = 1 << count; // If There Are y 1s In The Binary Representation Of The Hyperoctant, Calculate: 2^y.
                    
                    for (int mask=1; mask<total; mask++)
                    {
                        vector<int>hypoct(m,0);
                        
                        for (int j=0; j<count; j++)
                        {
                            if ((mask >> j) & 1)
                                hypoct[I[j]] = 1;
                        }
                        //Project The Point To A Hyperoctant
                        vector<int>projected_point=pointProjection(current_hyperoctant,hypoct,population[i],pivot);
                        
                        //Determine The Decimal Representation Of The Hyperoctant
                        hyperoctant_number=toDecimal(hypoct);
                        
                        //Calculate The Reference Point For The Hyperoctant To Which The Point Is Projected
                        if (reference_hyperoctant[hyperoctant_number].empty())
                        {
                            reference_hyperoctant[hyperoctant_number] = calculateReference(hypoct,pivot,reference);
                        }
                        
                        //Add The Point To The List Of Points Present In The Hyperoctant
                        addPoint(population_hyperoctant,hyperoctant_number,projected_point);
                    }
                }
            }
        }
        
        int Hypervolume = hypervolume(reference, pivot);

        for (int i = 1; i < total_hyperoctants; i++)
        {
            vector<vector<int>>population_nonDominated= nonDominatedPopulation(population_hyperoctant[i]);
            Hypervolume += quickHypervolume(population_nonDominated,reference_hyperoctant[i]);
        }
        
        return Hypervolume;
    }
}

int main()
{
    int n;
    
    cout<<"ENTER THE NUMBER OF POINTS = ";
    cin>>n;
    cout<<"ENTER THE DIMENSIONS OF POINTS = ";
    cin>>m;
    
    if(n>0)
    {
        //Initial Population With/Without Dominated Points
        vector<vector<int>>population_initial(n,vector<int>(m));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                cout<<"ENTER THE "<<j<<" CO-ORDINATE OF "<<i<<"  POINT = ";
                cin>>population_initial[i][j];
            }
        }
        
        //Non-Dominated Population
        vector<vector<int>>population= nonDominatedPopulation(population_initial);
        
        //Initial Reference
        vector<int>reference(m,0);
        
        //Calculating Hypervolume For The Non Dominated Popultaion
        int Hypervolume=quickHypervolume(population, reference);
        cout<<endl;
        cout<<endl;
        cout<<"HYPERVOLUME = "<<Hypervolume<<endl;
        cout<<endl;
        
    }
    else
        cout<<"NO POINTS TO CALCULATE HYPERVOLUME!"<<endl;

    return 0;
}


