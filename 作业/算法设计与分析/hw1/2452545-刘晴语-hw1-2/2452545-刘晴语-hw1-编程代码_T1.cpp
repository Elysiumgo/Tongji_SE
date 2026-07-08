#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double solve(vector<double>& a, double M) {
    int n = a.size();
    sort(a.begin(), a.end()); //排序

    for(int i=1;i<n;i++){
        double diff=a[i]-a[i-1];
        double needed=diff*i; //需要的水量

        if(needed<=M){
            M-=needed; //扣除水量   
        }else{
           return a[i-1]+M/i; //水不够，计算最终水位
        }

    }

    return a[n-1]+M/n; //所有水都用完，计算最终水位
   
}



int main() {
    vector<double> a = {0.2, 0.5, 0.1, 0.8, 1.5, 0.4, 0.9};
    double M = 2;

    double result = solve(a, M);

    cout << "Final water height: " << result << endl;

    return 0;
}