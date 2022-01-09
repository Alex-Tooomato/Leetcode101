//
// Created by skyyw on 2022/1/9.
//

#include <vector>
using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count=0;
    int m=flowerbed.size();
    if (m<n){
        return false;
    }
    int prev=-1;
    for(int i=0;i<m;i++){
        if(flowerbed[i]==1){
            if(prev==-1){
                count+=i/2;
            } else{
                count+=(i-prev-2)/2;
            }
            prev=i;
        }
    }
    if(prev==-1){
        count+=(m+1)/2;
    }else{
        count+=(m-1-prev)/2;
    }
        return count>=n;
    }
};