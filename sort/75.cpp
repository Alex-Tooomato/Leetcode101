//
// Created by pc on 2022/2/25.
//
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n=nums.size();
        int ptr=0;
        for(int i=0;i<n;++i){
            if(nums[i]==0){
                swap(nums[ptr],nums[i]);
                ++ptr;
            }
        }
        for(int i=ptr;i<n;++i){
            if(nums[i]==1){
                swap(nums[ptr],nums[i]);
                ++ptr;
            }
        }

    }
    void sortColors2(vector<int>& nums) {
        int n=nums.size();
        int p0=0;
        int p1=0;
        for (int i=0;i<n;++i){
            if(nums[i]==1){
                swap(nums[p1],nums[i]);
                ++p1;
            }else  if(nums[i]==0){
                swap(nums[p0],nums[i]);
                if(p0<p1){
                    swap(nums[i],nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};