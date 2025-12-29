/*
//  3D Hypervolume.cpp
//  Hypervolume
//  Created by Harshvijay Mishra

#include <iostream>
using namespace std;

int Hypervolume(int *point)
{
        return point[0]*point[1]*point[2];
}

int ExHyp(int *first=0,int *second=0,int *third=0,int *fourth=0)
{
    if(first)
    {
        int val_first=Hypervolume(first);
        int *second_projected=0;
        int *third_projected=0;
        int *fourth_projected=0;
        
        if(second)
        {
            second_projected=new int[3];
            second_projected[0]=(second[0]>first[0])?first[0]:second[0];
            second_projected[1]=(second[1]>first[1])?first[1]:second[1];
            second_projected[2]=(second[2]>first[2])?first[2]:second[2];
        }
        
        if(third)
        {
            third_projected=new int[3];
            third_projected[0]=(third[0]>first[0])?first[0]:third[0];
            third_projected[1]=(third[1]>first[1])?first[1]:third[1];
            third_projected[2]=(third[2]>first[2])?first[2]:third[2];
        }
        
        if(fourth)
        {
            fourth_projected=new int[3];
            fourth_projected[0]=(fourth[0]>first[0])?first[0]:fourth[0];
            fourth_projected[1]=(fourth[1]>first[1])?first[1]:fourth[1];
            fourth_projected[2]=(fourth[2]>first[2])?first[2]:fourth[2];
        }
        
        int val_second=ExHyp(second_projected, third_projected, fourth_projected)+ExHyp(third_projected, fourth_projected)+ExHyp(fourth_projected);
        
        return val_first-val_second;
    }
    return 0;
}

int main()
{
    int a[]={11,4,4};
    int b[]={9,2,5};
    int c[]={5,6,7};
    int d[]={3,3,10};
    
    int Total= ExHyp(a,b,c,d)+ExHyp(b,c,d)+ExHyp(c,d)+ExHyp(d);
    cout<<Total<<endl;
}
*/
