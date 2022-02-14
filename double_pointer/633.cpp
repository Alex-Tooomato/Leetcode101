//
// Created by skyyw on 2022/1/25.
//
#include <math.h>
using namespace std;
class Solution {
public:
    bool judgeSquareSum(int c) {
    if(c<=0){
        return false;
    }
    long n= long(sqrt(c));
    long l=0,r=n;
    while(l<=r){
        if((pow(l,2)+pow(r,2))==c){
            return true;
        } else if((pow(l,2)+pow(r,2))>c){
            --r;
        } else{
            ++l;
        }
    }
        return false;
    }
};