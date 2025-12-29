/*
//  2D Hypervolume.cpp
//  Hypervolume
//  Created by Harshvijay Mishra

#include <iostream>
using namespace std;

int Hypervolume(int *point)
{
        return point[0]*point[1];
}

int ExHyp(int *first=0,int *second=0,int *third=0)
{
    if(first)
    {
        int val_first=Hypervolume(first);
        int *second_projected=0;
        int *third_projected=0;
        
        if(second)
        {
            second_projected=new int[2];
            second_projected[0]=(second[0]>first[0])?first[0]:second[0];
            second_projected[1]=(second[1]>first[1])?first[1]:second[1];
        }
        
        if(third)
        {
            third_projected=new int[2];
            third_projected[0]=(third[0]>first[0])?first[0]:third[0];
            third_projected[1]=(third[1]>first[1])?first[1]:third[1];
        }
        
        int val_second=ExHyp(second_projected, third_projected)+ExHyp(third_projected);
        
        return val_first-val_second;
    }
    return 0;
}

int main()
{
    int a[]={1,10};
    int b[]={2,8};
    int c[]={3,6};
    
    int Total= ExHyp(a,b,c)+ExHyp(b,c)+ExHyp(c);
    cout<<Total<<endl;
}
*/
