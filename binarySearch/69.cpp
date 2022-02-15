//
// Created by pc on 2022/2/15.
//
#include <stdio.h>
using namespace std;
class Solution {
public:
    int mySqrt(int x) {
        if(x==0)return 0;
        int l=1,r=x,mid,sqrt;
        while(l<=r){
            mid=l+(r-l)/2;
            sqrt=x/mid;
            if(mid==sqrt){
                return mid;
            } else if(mid<sqrt){
                l=mid+1;
            } else{
                r=mid-1;
            }
        }
        return r;
    }
    int mySqrt2(int x) {
    long a=x;
    while(a*a>x){
        a=(a+x/a)/2;
    }
        return a;
    }
};