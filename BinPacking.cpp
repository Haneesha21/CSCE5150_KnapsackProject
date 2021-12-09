//
//  BinPacking.cpp
//  Algorithms
//
//  Created by Haneesha Damarapati on 11/7/21.
//
#include<iostream>
#define MAX 50
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct item
{
  int item_num;
  int profit;
  int weight;
  float ratio;
  float take_quantity;
};


int bincount( vector<int> weight, int n, int c)
{
    int result = 0;
 
    int rem_bin[n];
 
    // add items one by one
    for (int i = 0; i < n; i++) {
        int j;
        int min = c + 1, bi = 0;
 
        for (j = 0; j < result; j++) {
            if (rem_bin[j] >= weight[i] && rem_bin[j] -
                                     weight[i] < min) {
                bi = j;
                min = rem_bin[j] - weight[i];
                
            }
        }
 
        // create a bin when hits max capacity
        if (min == c + 1) {
            rem_bin[result] = c - weight[i];
            result++;
            
        }
        else
            rem_bin[bi] -= weight[i];
    }
    return result;
} 


int main()
{
  item P[MAX],temp;
  int i,j,total_item,capacity;
  float value=0,time;
  vector<int> li;
  cout<<"ENTER NUMBER OF ITEMS : ";
  cin>>total_item;
  cout<<"ENTER CAPACITY OF BAG : ";
  cin>>capacity;
  cout<<"\n";
  int si=capacity;  
  auto begin = high_resolution_clock::now();
  for(i=0;i<total_item;++i)
  {
    P[i].item_num=i+1;
    cout<<"ENTER PROFIT AND WEIGHT OF item "<<i+1<<" : ";
    cin>>P[i].profit>>P[i].weight;
    //bprod[i]= P[i].weight;
    P[i].ratio=(float)P[i].profit/P[i].weight;
    P[i].take_quantity=0;
  }
  //ratio sorting
  for(i=0;i<total_item;++i)
  {
    for(j=i+1;j<total_item;++j)
    {
      if(P[i].ratio<P[j].ratio)
      {
        temp=P[i];
        P[i]=P[j];
        P[j]=temp;
      }
    }
  }

  for(i=0;i<total_item;++i)
  {
    if(capacity==0)
      break;
    else if(P[i].weight<capacity)
    {
      P[i].take_quantity=1;
      capacity-=P[i].weight;
    }
  }
  
//calculate Knapsack Value
  for(i=0;i<total_item;++i)
  {
    li.push_back(P[i].weight);
    value+=P[i].profit*P[i].take_quantity;
  }
 
  
  cout<<"\nTHE KNAPSACK VALUE IS : "<<value;
  cout << "\nNumber of bins required : " << bincount(li, total_item, si);
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end - begin);
  time=(float)duration.count();
  cout<<"\nTime taken to run: ";
  cout<<time/1000<<" seconds"<<endl;
  return 0;
}
